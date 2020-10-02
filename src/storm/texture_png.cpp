#include <storm/texture_png.h>

#include <iterator>
#include <vector>

#include <storm/exception.h>

#define LODEPNG_NO_COMPILE_ENCODER
#define LODEPNG_NO_COMPILE_DISK
#define LODEPNG_NO_COMPILE_ANCILLARY_CHUNKS
#define LODEPNG_NO_COMPILE_CPP

// The following preprocessor directives add the 'storm_' prefix to all public
// lodepng symbols so libstorm can be safely linked to binaries that already
// use lodepng.

#define LODEPNG_VERSION_STRING           STORM_LODEPNG_VERSION_STRING
#define lodepng_default_decompress_settings \
    storm_lodepng_default_decompress_settings
#define lodepng_decode_memory            storm_lodepng_decode_memory
#define lodepng_decode32                 storm_lodepng_decode32
#define lodepng_decode24                 storm_lodepng_decode24
#define lodepng_error_text               storm_lodepng_error_text
#define lodepng_decompress_settings_init storm_lodepng_decompress_settings_init
#define lodepng_color_mode_init          storm_lodepng_color_mode_init
#define lodepng_color_mode_cleanup       storm_lodepng_color_mode_cleanup
#define lodepng_color_mode_copy          storm_lodepng_color_mode_copy
#define lodepng_palette_clear            storm_lodepng_palette_clear
#define lodepng_palette_add              storm_lodepng_palette_add
#define lodepng_get_bpp                  storm_lodepng_get_bpp
#define lodepng_get_channels             storm_lodepng_get_channels
#define lodepng_is_greyscale_type        storm_lodepng_is_greyscale_type
#define lodepng_is_alpha_type            storm_lodepng_is_alpha_type
#define lodepng_is_palette_type          storm_lodepng_is_palette_type
#define lodepng_has_palette_alpha        storm_lodepng_has_palette_alpha
#define lodepng_can_have_alpha           storm_lodepng_can_have_alpha
#define lodepng_get_raw_size             storm_lodepng_get_raw_size
#define lodepng_get_raw_size_lct         storm_lodepng_get_raw_size_lct
#define lodepng_info_init                storm_lodepng_info_init
#define lodepng_info_cleanup             storm_lodepng_info_cleanup
#define lodepng_info_copy                storm_lodepng_info_copy
#define lodepng_info_swap                storm_lodepng_info_swap
#define lodepng_convert                  storm_lodepng_convert
#define lodepng_decoder_settings_init    storm_lodepng_decoder_settings_init
#define lodepng_state_init               storm_lodepng_state_init
#define lodepng_state_cleanup            storm_lodepng_state_cleanup
#define lodepng_state_copy               storm_lodepng_state_copy
#define lodepng_decode                   storm_lodepng_decode
#define lodepng_inspect                  storm_lodepng_inspect
#define lodepng_chunk_length             storm_lodepng_chunk_length
#define lodepng_chunk_type               storm_lodepng_chunk_type
#define lodepng_chunk_type_equals        storm_lodepng_chunk_type_equals
#define lodepng_chunk_ancillary          storm_lodepng_chunk_ancillary
#define lodepng_chunk_private            storm_lodepng_chunk_private
#define lodepng_chunk_safetocopy         storm_lodepng_chunk_safetocopy
#define lodepng_chunk_data               storm_lodepng_chunk_data
#define lodepng_chunk_data_const         storm_lodepng_chunk_data_const
#define lodepng_chunk_check_crc          storm_lodepng_chunk_check_crc
#define lodepng_chunk_generate_crc       storm_lodepng_chunk_generate_crc
#define lodepng_chunk_next               storm_lodepng_chunk_next
#define lodepng_chunk_next_const         storm_lodepng_chunk_next_const
#define lodepng_chunk_append             storm_lodepng_chunk_append
#define lodepng_chunk_create             storm_lodepng_chunk_create
#define lodepng_crc32                    storm_lodepng_crc32
#define lodepng_inflate                  storm_lodepng_inflate
#define lodepng_zlib_decompress          storm_lodepng_zlib_decompress
#define lodepng_zlib_compress            storm_lodepng_zlib_compress
#define lodepng_huffman_code_lengths     storm_lodepng_huffman_code_lengths
#define lodepng_deflate                  storm_lodepng_deflate
#define lodepng_read32bitInt             storm_lodepng_read32bitInt

#include <lodepng.cpp>

namespace storm {

Texture::Pointer parsePng(
    GpuContext::Pointer gpuContext,
    BinaryInputStream &stream,
    const Texture::LoadingParameters &parameters )
{
    const std::vector<char> buffer(
        std::istreambuf_iterator<char> {*stream},
        std::istreambuf_iterator<char> {} );

    uint8_t *texels = nullptr;
    unsigned width = 0;
    unsigned height = 0;

    if( const unsigned error = lodepng_decode32(
            &texels,
            &width,
            &height,
            reinterpret_cast<const uint8_t*>(buffer.data()),
            buffer.size()) ) {
        if( texels ) {
            lodepng_free( texels );
        }

        throw ResourceLoadingError() <<
            "Couldn't read a PNG texture: " << lodepng_error_text( error );
    }

    Texture::Separate2dDescription description;
    if( parameters.defaultColorSpace == Texture::ColorSpace::sRGB )
        description.format = Texture::Format::SrgbaNormUint8;
    else
        description.format = Texture::Format::RgbaNormUint8;
    description.width = width;
    description.height = height;
    description.mipLevels = 1;
    description.resourceType = ResourceType::Static;

    Texture::Pointer texture = Texture::create( gpuContext, description );

    Texture::Separate2dRegion region;
    region.mipLevel = 0;
    region.x = 0;
    region.y = 0;
    region.width = width;
    region.height = height;

    texture->setTexels( region, texels );

    lodepng_free( texels );

    return texture;
}

}
