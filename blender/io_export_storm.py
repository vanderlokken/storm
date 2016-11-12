bl_info = {
    "name": "Export Storm Framework Mesh Format (.storm-mesh)",
    "author": "vanderlokken",
    "version": (1, 3),
    "blender": (2, 65, 0),
    "location": "File > Export > Storm Framework Mesh (.storm-mesh)",
    "description": "Export mesh in Storm Framework format",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export"}

from contextlib import contextmanager
import struct

import bpy
from bpy_extras.io_utils import ExportHelper
from mathutils import Matrix

class StormExportOperator(bpy.types.Operator, ExportHelper):
    """Export Storm Framework Mesh (.storm-mesh)"""

    bl_idname = "export_mesh.storm"
    bl_label = "Export Storm Framework Mesh"

    filename_ext = ".storm-mesh"

    export_normals = bpy.props.BoolProperty(
        name="Export normals", default=True)
    export_tangents = bpy.props.BoolProperty(
        name="Export tangents", default=True)
    export_texture_coordinates = bpy.props.BoolProperty(
        name="Export texture coordinates", default=True)
    export_blending_indices = bpy.props.BoolProperty(
        name="Export blending indices")
    export_blending_weights = bpy.props.BoolProperty(
        name="Export blending weights")

    @classmethod
    def poll(cls, context):
        return context.object and context.object.type == "MESH"

    def draw(self, context):
        layout = self.layout

        layout.prop(self, "export_normals")
        layout.separator()

        uv_dependent_attributes = layout.column()

        if not context.object.data.uv_layers.active:
            uv_dependent_attributes.label(text="No UV", icon="ERROR")
            uv_dependent_attributes.active = False

            self.properties.export_tangents = False
            self.properties.export_texture_coordinates = False

        uv_dependent_attributes.prop(self, "export_tangents")
        uv_dependent_attributes.prop(self, "export_texture_coordinates")

        layout.separator()
        layout.prop(self, "export_blending_indices")
        layout.prop(self, "export_blending_weights")

    def execute(self, context):
        self._context = context

        with open(self.filepath, "wb") as output_file:
            self._file = output_file
            self._export()

        return {"FINISHED"}

    def _export(self):
        with self._duplicated_object():
            self._apply_scaling()
            self._convert_quadrangles_to_triangles()
            self._export_attributes()
            self._export_mesh()

    @contextmanager
    def _duplicated_object(self):
        bpy.ops.object.mode_set(mode="OBJECT")
        bpy.ops.object.select_all(action="DESELECT")

        self._context.object.select = True
        bpy.ops.object.duplicate_move()
        try:
            yield
        finally:
            bpy.ops.object.delete()

    def _apply_scaling(self):
        bpy.ops.object.transform_apply(scale=True)

    def _convert_quadrangles_to_triangles(self):
        bpy.ops.object.mode_set(mode="EDIT")

        bpy.ops.mesh.reveal()
        bpy.ops.mesh.select_all(action="SELECT")
        bpy.ops.mesh.quads_convert_to_tris()

        # This operator is required since we'll mirror object by turning
        # coordinate system from right-handed to left-handed.
        bpy.ops.mesh.flip_normals()

        bpy.ops.object.mode_set(mode="OBJECT")

    @property
    def _vertex_groups_bones_mapping(self):
        mapping = {}

        armature = self._context.object.find_armature()
        bones_names = [
            bone.name for bone in armature.pose.bones] if armature else []

        for vertex_group in self._context.object.vertex_groups:
            mapping[vertex_group.index] = (bones_names.index(vertex_group.name)
                if vertex_group.name in bones_names else None)

        return mapping

    def _export_attributes(self):
        attributes_export = [
            self.export_normals,
            self.export_tangents,
            self.export_texture_coordinates,
            self.export_blending_indices,
            self.export_blending_weights]

        attribute_count = 1 + sum(attributes_export)

        self._file.write( struct.pack("<I", attribute_count) )

        (SemanticsPosition,
            SemanticsNormal,
            SemanticsTangent,
            SemanticsBinormal,
            SemanticsColor,
            SemanticsTextureCoordinates,
            SemanticsBlendingWeights,
            SemanticsBlendingIndices) = range(8)

        (FormatFloat,
            Format2Float,
            Format3Float,
            Format4Float,
            Format4Uint8,
            Format4Uint8Normalized,
            Format2Int16,
            Format2Int16Normalized,
            Format4Int16,
            Format4Int16Normalized,
            Format2Uint16Normalized,
            Format4Uint16Normalized) = range(12)

        def write_attribute(semantics, format):
            self._file.write(struct.pack("<II", semantics, format))

        write_attribute(SemanticsPosition, Format3Float)
        if self.export_normals:
            write_attribute(SemanticsNormal, Format3Float)
        if self.export_tangents:
            write_attribute(SemanticsTangent, Format3Float)
        if self.export_texture_coordinates:
            write_attribute(SemanticsTextureCoordinates, Format2Float)
        if self.export_blending_indices:
            write_attribute(SemanticsBlendingIndices, Format4Uint8)
        if self.export_blending_weights:
            write_attribute(SemanticsBlendingWeights, Format3Float)

    @staticmethod
    def _transform_mesh_coordinate_system(mesh):
        # This transformation swaps Y and Z axes, turning coordinate system from
        # right-handed to left-handed.
        transformation = Matrix()
        transformation.zero()
        transformation[0][0] = 1
        transformation[1][2] = 1
        transformation[2][1] = 1
        transformation[3][3] = 1
        mesh.transform(transformation)

    def _export_mesh(self):
        mesh = self._context.object.to_mesh(
            scene=self._context.scene, apply_modifiers=True, settings="RENDER")

        self._transform_mesh_coordinate_system(mesh)

        if self.export_normals:
            mesh.calc_normals_split()
        if self.export_tangents:
            mesh.calc_tangents(mesh.uv_layers.active.name)

        vertices = []
        indices = []

        for polygon in mesh.polygons:
            for loop_index in polygon.loop_indices:
                vertex = self._pack_vertex_data(mesh, loop_index)

                if vertex in vertices:
                    index = vertices.index(vertex)
                else:
                    index = len(vertices)
                    vertices.append(vertex)

                indices.append(index)

        vertex_data = bytearray()
        for vertex in vertices:
            vertex_data += vertex

        if len(vertices) <= (2 ** 16 - 1):
            index_data = struct.pack(
                "<{0}H".format(len(indices)), *indices)
        else:
            index_data = struct.pack(
                "<{0}I".format(len(indices)), *indices)

        vertex_size = len(vertex_data) // len(vertices)
        index_size = len(index_data) // len(indices)

        self._file.write(struct.pack("<B", vertex_size))
        self._file.write(struct.pack("<I", len(vertex_data)))
        self._file.write(vertex_data)

        self._file.write(struct.pack("<B", index_size))
        self._file.write(struct.pack("<I", len(index_data)))
        self._file.write(index_data)

        bpy.data.meshes.remove(mesh)

    def _pack_vertex_data(self, mesh, loop_index):
        loop = mesh.loops[loop_index]
        vertex = mesh.vertices[loop.vertex_index]

        convert_uv = lambda vector: (vector[0], 1 - vector[1])

        vertex_data = bytearray()
        vertex_data += struct.pack("<fff", *vertex.co)

        if self.export_normals:
            vertex_data += struct.pack("<fff", *loop.normal)
        if self.export_tangents:
            vertex_data += struct.pack("<fff", *loop.tangent)

        if self.export_texture_coordinates:
            uv = mesh.uv_layers.active.data[loop.index].uv
            vertex_data += struct.pack("<ff", *convert_uv(uv))

        if self.export_blending_indices:
            indices = [self._vertex_groups_bones_mapping[group.group] for
                group in vertex.groups]
            indices = filter(lambda index: index is not None, indices)
            vertex_data += struct.pack("<BBBB", *(indices + [0, 0, 0, 0])[0:4])

        if self.export_blending_weights:
            weights = [group.weight for group in vertex.groups if
                self._vertex_groups_bones_mapping[group.group] is not None]
            if sum(weights) != 0:
                weights = [weight / sum(weights) for weight in weights]
            vertex_data += struct.pack("<fff", *(weights + [0, 0, 0])[0:3])

        return vertex_data


def menu_function(self, context):
    self.layout.operator(
        StormExportOperator.bl_idname,
        text="Storm Framework Mesh (.storm-mesh)")


def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_function)


def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_function)


if __name__ == "__main__":
    register()
