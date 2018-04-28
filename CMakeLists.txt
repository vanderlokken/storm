cmake_minimum_required(VERSION 3.11.1)

project(storm)

find_package(OpenGL REQUIRED)

option(storm_build_examples "Whether to build examples or not" ON)
option(storm_enable_png_support "Whether to enable PNG support or not" OFF)

add_library(storm STATIC)

target_compile_features(storm PUBLIC cxx_std_17)
target_link_libraries(storm PUBLIC OpenGL::GL)
target_include_directories(storm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE src
)

if(UNIX)
    find_package(X11 REQUIRED)

    if(NOT X11_Xi_FOUND)
        message(FATAL_ERROR "The 'Xi' library is not found")
    endif()

    if(NOT X11_Xrandr_FOUND)
        message(FATAL_ERROR "The 'Xrandr' library is not found")
    endif()

    target_link_libraries(storm PUBLIC
        ${X11_X11_LIB}
        ${X11_Xi_LIB}
        ${X11_Xrandr_LIB}
    )
    target_include_directories(storm PRIVATE
        ${X11_X11_INCLUDE_PATH}
        ${X11_Xi_INCLUDE_PATH}
        ${X11_Xrandr_INCLUDE_PATH}
    )
endif()

if(storm_enable_png_support)
    find_package(PNG REQUIRED)

    target_link_libraries(storm PUBLIC PNG::PNG)
    target_compile_definitions(storm PRIVATE storm_enable_png_support)
endif()

set_target_properties(storm PROPERTIES
    COMPILE_PDB_NAME_DEBUG stormd
    COMPILE_PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
)

if(MSVC)
    set_target_properties(storm PROPERTIES DEBUG_POSTFIX d)
    target_compile_options(storm PRIVATE $<$<CONFIG:Debug>:/Zi> /W4 /GR-)
    target_compile_definitions(storm PRIVATE UNICODE _UNICODE)
elseif(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(storm PRIVATE -Wall)
endif()

set(storm_includes
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/backbuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/blending_technique.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/buffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/camera.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/clock.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/color.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/color.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/common_vertex_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/condition.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/dimensions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/display.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/event_loop.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/exception.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/keyboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/matrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/matrix.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/mesh.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/mouse.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/output_technique.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/quaternion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/quaternion.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/query.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/rasterization_technique.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/rectangle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/rendering_system.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/rendering_window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/resource_type.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/sampler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/shader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/storm.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/texture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/transformation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/vector.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/vector.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/include/storm/vertex_format.h
)

set(storm_common_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/binary_input_stream.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/blending_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/common_vertex_types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/event_loop_common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/exception.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/keyboard_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/keyboard_common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/noncopyable.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/observer_list.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/output_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/rasterization_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/rendering_system_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/rendering_system_common.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/sampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_dds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_dds.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_png.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_png.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/throw_exception.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/transformation.cpp
)

set(glcorearb_header
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/glcorearb.h)

if(NOT EXISTS ${glcorearb_header})
    file(DOWNLOAD "http://www.opengl.org/registry/api/GL/glcorearb.h"
        ${glcorearb_header} STATUS status)
    list(GET status 0 error_code)
    if(error_code)
        file(REMOVE ${glcorearb_header})
        message(FATAL_ERROR "Couldn't download 'glcorearb.h'.")
    endif()
endif()

set(storm_ogl_sources
    ${glcorearb_header}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/api_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/api_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/backbuffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/backbuffer_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/blending_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/blending_technique_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/buffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/buffer_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/check_result_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/condition_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/condition_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/framebuffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/framebuffer_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/handle_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/mesh_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/mesh_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/output_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/output_technique_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/query_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/query_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rasterization_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rasterization_technique_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rendering_system_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rendering_system_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/resource_type_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/resource_type_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/sampler_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/sampler_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/shader_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/shader_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_storage_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_storage_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_ogl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/vertex_format_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/vertex_format_ogl.h
)

if(WIN32)
    set(storm_platform_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/api_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/clock_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/display_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/display_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/event_loop_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/event_loop_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/input_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/input_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/keyboard_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/keyboard_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/mouse_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/mouse_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_window_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_window_win.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/window_procedure_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/window_procedure_win.h
    )
elseif(UNIX)
    set(storm_platform_sources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/posix/clock_posix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_connection_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_connection_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/event_loop_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/event_loop_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/input_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/input_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/keyboard_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/keyboard_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/mouse_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/mouse_x11.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_system_glx.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_system_glx.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_window_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_window_x11.h
    )
endif()

target_sources(storm PRIVATE
    ${storm_includes}
    ${storm_common_sources}
    ${storm_ogl_sources}
    ${storm_platform_sources}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

install(TARGETS storm EXPORT storm-config
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/stormd.pdb
    DESTINATION lib
    CONFIGURATIONS Debug
)

install(EXPORT storm-config
    DESTINATION lib/cmake/storm
    NAMESPACE storm::
)

if(storm_build_examples)
    add_subdirectory(examples/advanced_rendering)
    add_subdirectory(examples/triangle_rendering)
endif()
