#pragma once

#include <storm/mesh.h>
#include <storm/sampler.h>
#include <storm/texture.h>

storm::Texture::Pointer createCheckboardPatternTexture();
storm::Sampler::Pointer createCheckboardPatternSampler();

storm::Mesh::Pointer createTexturedCubeMesh();
