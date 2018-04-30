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
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/include
        src
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

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/glcorearb.h
    COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_CURRENT_BINARY_DIR}/include
    COMMAND ${CMAKE_COMMAND} -E chdir
        ${CMAKE_CURRENT_BINARY_DIR}/include
        ${CMAKE_COMMAND} -E
            tar zxf ${CMAKE_CURRENT_SOURCE_DIR}/contrib/glcorearb.tar.gz
    # We need to update the timestamp of the output file. When it's newer than
    # the timestamp of the archive file CMake skips unpacking.
    COMMAND ${CMAKE_COMMAND} -E touch
        ${CMAKE_CURRENT_BINARY_DIR}/include/glcorearb.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/contrib/glcorearb.tar.gz
)

target_sources(storm PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/blending_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/common_vertex_types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/exception.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/keyboard_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/output_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/rasterization_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/rendering_system_common.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/sampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_dds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/texture_png.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/transformation.cpp
)

target_sources(storm PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/include/glcorearb.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/api_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/backbuffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/blending_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/buffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/condition_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/framebuffer_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/mesh_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/output_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/query_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rasterization_technique_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/rendering_system_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/resource_type_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/sampler_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/shader_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_storage_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/texture_ogl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/ogl/vertex_format_ogl.cpp
)

if(WIN32)
    target_sources(storm PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/clock_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/display_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/event_loop_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/input_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/keyboard_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/mouse_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_window_win.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/window_procedure_win.cpp
    )
elseif(UNIX)
    target_sources(storm PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/posix/clock_posix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_connection_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/event_loop_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/input_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/keyboard_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/mouse_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_system_glx.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_window_x11.cpp
    )
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

install(TARGETS storm EXPORT storm_config
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/stormd.pdb
    DESTINATION lib
    CONFIGURATIONS Debug
)

install(EXPORT storm_config
    DESTINATION lib/cmake/storm
    NAMESPACE storm::
)

if(storm_build_examples)
    add_subdirectory(examples/advanced_rendering)
    add_subdirectory(examples/triangle_rendering)
endif()
