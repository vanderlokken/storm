bl_info = {
    "name": "Storm (.selement)",
    "author": "vanderlokken@gmail.com",
    "version": (1, 1),
    "blender": (2, 65, 0),
    "location": "File > Export > Storm (.selement)",
    "description": "Export Storm (.selement)",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export" }

import struct

import bpy
from bpy_extras.io_utils import ExportHelper


class StormExportOperator(bpy.types.Operator, ExportHelper):
    """Export Storm (.selement)"""

    bl_idname = "export.storm"
    bl_label = "Export Storm"

    filename_ext = ".selement"

    export_normals = bpy.props.BoolProperty(
        name="Export Normals")
    export_blending_indices = bpy.props.BoolProperty(
        name="Export Blending Indices")
    export_blending_weights = bpy.props.BoolProperty(
        name="Export Blending Weights")

    @classmethod
    def poll(self, context):
        return context.object and context.object.type == "MESH"

    def execute(self, context):

        self._context = context

        with open(self.filepath, "wb") as output_file:
            self._file = output_file
            self._export()

        return {"FINISHED"}

    def _export(self):
        self._duplicate_object()
        self._apply_transformations()
        self._convert_quadrangles_to_triangles()
        self._export_attributes()
        self._export_mesh()
        self._delete_duplicate()

    def _duplicate_object(self):
        bpy.ops.object.mode_set(mode="OBJECT")
        bpy.ops.object.select_all(action="DESELECT")

        self._context.object.select = True
        bpy.ops.object.duplicate_move()

    def _delete_duplicate(self):
        bpy.ops.object.delete()

    def _apply_transformations(self):
        bpy.ops.object.transform_apply(
            location=True, rotation=True, scale=True)

    def _convert_quadrangles_to_triangles(self):
        bpy.ops.object.mode_set(mode="EDIT")

        bpy.ops.mesh.select_all(action="SELECT")
        bpy.ops.mesh.quads_convert_to_tris()

        bpy.ops.object.mode_set(mode="OBJECT")

    def _export_attributes(self):

        attributes_export = [
            self.export_normals,
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
        if self.export_blending_indices:
            write_attribute(SemanticsBlendingIndices, Format4Uint8)
        if self.export_blending_weights:
            write_attribute(SemanticsBlendingWeights, Format3Float)

    def _export_mesh(self):

        mesh = self._context.object.to_mesh(
            scene=self._context.scene, apply_modifiers=True, settings="RENDER")

        vertex_data = bytearray()
        index_data = bytearray()

        index_count = 0

        for polygon in mesh.polygons:

            if polygon.hide:
                continue

            for index in polygon.vertices:

                vertex = mesh.vertices[index]

                vertex_data += struct.pack(
                    "<fff", vertex.co[0], vertex.co[2], -vertex.co[1])

                if self.export_normals:
                    normal =\
                        vertex.normal if polygon.use_smooth else polygon.normal
                    vertex_data += struct.pack(
                        "<fff", normal[0], normal[2], -normal[1])

                if self.export_blending_indices:
                    indices = [
                        group_element.group for group_element in vertex.groups]

                    while len(indices) < 4:
                        indices.append(0)

                    vertex_data += struct.pack(
                        "<BBBB", indices[0], indices[1], indices[2], indices[3])

                if self.export_blending_weights:
                    weights = [
                        group_element.weight for group_element in vertex.groups]

                    while len(weights) < 3:
                        weights.append( 0 )

                    vertex_data += struct.pack(
                        "<fff", weights[0], weights[1], weights[2])

                index_data += struct.pack("<H", index_count)
                index_count += 1

        self._file.write(struct.pack("<I", len(vertex_data)))
        self._file.write(vertex_data)
        self._file.write(struct.pack("<I", len(index_data)))
        self._file.write(index_data)

        bpy.data.meshes.remove(mesh)


def menu_function(self, context):
    self.layout.operator(
        StormExportOperator.bl_idname, text="Storm (.selement)")


def register():
    bpy.utils.register_module(__name__)
    bpy.types.INFO_MT_file_export.append(menu_function)


def unregister():
    bpy.utils.unregister_module(__name__)
    bpy.types.INFO_MT_file_export.remove(menu_function)


if __name__ == "__main__":
    register()
