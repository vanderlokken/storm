bl_info = {
    "name": "Storm (.selement)",
    "author": "Alexander van der Lokken",
    "version": (1, 0),
    "blender": (2, 5, 7),
    "api": 31236,
    "location": "File > Export > Storm (.selement)",
    "description": "Export Storm (.selement)",
    "warning": "",
    "wiki_url": "",
    "tracker_url": "",
    "category": "Import-Export" }

import bpy
import struct

from io_utils import ExportHelper

class ExportSettings:
    def __init__( self, context, file, exportNormals, exportBlendingIndices, exportBlendingWeights ):
        self.context = context
        self.file = file
        self.exportNormals = exportNormals
        self.exportBlendingIndices = exportBlendingIndices
        self.exportBlendingWeights = exportBlendingWeights

def export( exportSettings ):
    createDuplicatedObject( exportSettings )
    applyTransformations( exportSettings )
    convertQuadranglesToTriangles( exportSettings )
    exportAttributes( exportSettings )
    exportMesh( exportSettings )
    deleteDuplicatedObject( exportSettings )

def createDuplicatedObject( exportSettings ):
    bpy.ops.object.mode_set( mode = 'OBJECT' )
    bpy.ops.object.select_all( action = 'DESELECT' )
    
    exportSettings.context.object.select = True
    bpy.ops.object.duplicate_move()

def deleteDuplicatedObject( exportSettings ):
    bpy.ops.object.delete()

def applyTransformations( exportSettings ):
    bpy.ops.object.scale_apply()
    bpy.ops.object.rotation_apply()
    bpy.ops.object.location_apply()

def convertQuadranglesToTriangles( exportSettings ):
    bpy.ops.object.mode_set( mode = 'EDIT' )
    
    bpy.ops.mesh.select_all( action = 'SELECT' )
    bpy.ops.mesh.quads_convert_to_tris()
    
    bpy.ops.object.mode_set( mode = 'OBJECT' )

def exportAttributes( exportSettings ):
    file = exportSettings.file
    
    attributeCount = 1
    
    if exportSettings.exportNormals:
        attributeCount += 1
    
    if exportSettings.exportBlendingIndices:
        attributeCount += 1
    
    if exportSettings.exportBlendingWeights:
        attributeCount += 1
    
    file.write( struct.pack('<I', attributeCount) )
    
    ( SemanticsPosition,
        SemanticsNormal,
        SemanticsTangent,
        SemanticsBinormal,
        SemanticsColor,
        SemanticsTextureCoordinates,
        SemanticsBlendingWeights,
        SemanticsBlendingIndices ) = range( 8 )
    
    ( FormatFloat,
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
        Format4Uint16Normalized ) = range( 12 )
    
    file.write( struct.pack('<II', SemanticsPosition, Format3Float) )
    
    if exportSettings.exportNormals:
        file.write( struct.pack('<II', SemanticsNormal, Format3Float) )
    
    if exportSettings.exportBlendingIndices:
        file.write( struct.pack('<II', SemanticsBlendingIndices, Format4Uint8) )
    
    if exportSettings.exportBlendingWeights:
        file.write( struct.pack('<II', SemanticsBlendingWeights, Format3Float) )
    
def exportMesh( exportSettings ):
    mesh = exportSettings.context.object.to_mesh(
        scene = exportSettings.context.scene, apply_modifiers = True, settings = 'RENDER' )
    
    vertexData = bytearray()
    indexData = bytearray()
    
    indexCount = 0
    
    for face in mesh.faces:
        if face.hide:
            continue
        
        for index in face.vertices:
            vertex = mesh.vertices[index]
            
            vertexData += struct.pack( '<fff', vertex.co[0], vertex.co[2], -vertex.co[1] )
            
            if exportSettings.exportNormals:
                if face.use_smooth:
                    vertexData += struct.pack( '<fff', vertex.normal[0], vertex.normal[2], -vertex.normal[1] )
                else:
                    vertexData += struct.pack( '<fff', face.normal[0], face.normal[2], -face.normal[1] )
            
            if exportSettings.exportBlendingIndices:
                indices = [ groupElement.group for groupElement in vertex.groups ]
                
                while len(indices) < 4:
                    indices.append( 0 )
                
                vertexData += struct.pack( '<BBBB', indices[0], indices[1], indices[2], indices[3] )
            
            if exportSettings.exportBlendingWeights:
                weights = [ groupElement.weight for groupElement in vertex.groups ]
                
                while len(weights) < 3:
                    weights.append( 0 )
                
                vertexData += struct.pack( '<fff', weights[0], weights[1], weights[2] )
            
            indexData += struct.pack( '<H', indexCount )
            
            indexCount += 1
    
    exportSettings.file.write( struct.pack('<I', len(vertexData)) )
    exportSettings.file.write( vertexData )
    exportSettings.file.write( struct.pack('<I', len(indexData)) )
    exportSettings.file.write( indexData )
    
    bpy.data.meshes.remove( mesh )

class StormExportOperator( bpy.types.Operator, ExportHelper ):
    
    '''Export Storm (.selement)'''
    
    bl_idname = "export.storm"
    bl_label = "Export Storm"
    
    filename_ext = ".selement"
    
    exportNormals = bpy.props.BoolProperty( name = 'Export Normals' )
    exportBlendingIndices = bpy.props.BoolProperty( name = 'Export Blending Indices' )
    exportBlendingWeights = bpy.props.BoolProperty( name = 'Export Blending Weights' )
    
    @classmethod
    def poll( self, context ):
        return context.object and context.object.type == 'MESH'
    
    def execute( self, context ):
        
        file = open( self.filepath, 'wb' )
        
        exportSettings = ExportSettings(
            context, file, self.exportNormals, self.exportNormals, self.exportNormals )
        
        export( exportSettings )
        
        file.close()
        
        return {'FINISHED'}
        
def handleMenuActivation( self, context ):
    self.layout.operator( StormExportOperator.bl_idname, text = "Storm (.selement)" )

def register():
    bpy.utils.register_module( __name__ )
    bpy.types.INFO_MT_file_export.append( handleMenuActivation )

def unregister():
    bpy.utils.register_module( __name__ )
    bpy.types.INFO_MT_file_export.append( handleMenuActivation )

if __name__ == "__main__":
    register()