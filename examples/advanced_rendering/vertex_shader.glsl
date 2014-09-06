#version 330 core

layout(row_major) uniform transformations {
    mat4 viewProjection;
    mat4 world;
} Transformations;

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexNormal;
layout(location = 2) in vec2 vertexTextureCoordinates;

out vec4 position;
out vec4 normal;
out vec2 textureCoordinates;

void main() {
    position = vertexPosition * Transformations.world;
    normal = vertexNormal * Transformations.world;
    textureCoordinates = vertexTextureCoordinates;

    gl_Position = position * Transformations.viewProjection;
}
