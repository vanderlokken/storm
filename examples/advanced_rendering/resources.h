#pragma once

#include <storm/mesh.h>
#include <storm/sampler.h>
#include <storm/texture.h>

storm::Texture::Pointer createCheckboardPatternTexture(
    storm::GpuContext::Pointer gpuContext );
storm::Sampler::Pointer createCheckboardPatternSampler(
    storm::GpuContext::Pointer gpuContext );

storm::Mesh::Pointer createTexturedCubeMesh(
    storm::GpuContext::Pointer gpuContext );
