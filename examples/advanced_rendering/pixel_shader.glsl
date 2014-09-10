#version 330 core

uniform sampler2D colorTexture;

in vec4 position;
in vec3 normal;
in vec2 textureCoordinates;

out vec4 color;

const float ambientBrightness = 0.6;
const float lightBrightness = 0.6;
const vec3 lightPosition = vec3( 20, 20, 20 );

const float textureRepetitionsNumber = 3;

void main() {
    vec3 directionToLight = normalize( lightPosition - position.xyz );
    float brightness = ambientBrightness +
        lightBrightness * clamp( dot(normal, directionToLight), 0, 1 );

    color = brightness * texture(
        colorTexture, textureCoordinates * textureRepetitionsNumber );
}
