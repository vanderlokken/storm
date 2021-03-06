#pragma once

#include <storm/binary_input_stream.h>
#include <storm/texture.h>

namespace storm {

Texture::Pointer parsePng(
    GpuContext::Pointer gpuContext,
    BinaryInputStream &stream,
    const Texture::LoadingParameters &parameters );

}
