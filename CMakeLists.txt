cmake_minimum_required(VERSION 3.11.1)

project(storm)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)

option(storm_build_examples "Whether to build examples or not" ON)

add_library(storm STATIC)

target_compile_features(storm PUBLIC cxx_std_17)
target_link_libraries(storm PRIVATE OpenGL::GL)
target_include_directories(storm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/contrib
        ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(UNIX)
    find_package(X11 REQUIRED)
    find_package(XCB REQUIRED COMPONENTS xcb xcb-xfixes xcb-xinput)

    if(NOT X11_Xrandr_FOUND)
        message(FATAL_ERROR "The 'Xrandr' library is not found")
    endif()

    target_link_libraries(storm PRIVATE
        ${X11_X11_LIB}
        ${X11_Xrandr_LIB}
        ${XCB_LIBRARIES}
    )
    target_include_directories(storm PRIVATE
        ${X11_X11_INCLUDE_PATH}
        ${X11_Xrandr_INCLUDE_PATH}
        ${XCB_INCLUDE_DIRS}
    )
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
    target_compile_options(storm PRIVATE -Wall $<$<CONFIG:Debug>:-g>)
endif()

macro(storm_contrib archive output_directory)
    add_custom_command(
        OUTPUT ${ARGN}
        COMMAND
            ${CMAKE_COMMAND} -E make_directory ${output_directory}
        COMMAND
            ${CMAKE_COMMAND} -E chdir ${output_directory}
            ${CMAKE_COMMAND} -E tar zxf ${archive}
        # We need to update the timestamp of output files. When it's newer
        # than the timestamp of the archive file CMake skips unpacking.
        COMMAND ${CMAKE_COMMAND} -E touch ${ARGN}
        DEPENDS ${archive}
    )
endmacro()

storm_contrib(
    ${CMAKE_CURRENT_SOURCE_DIR}/contrib/glcorearb-20180525.tar.gz
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL/glcorearb.h
)

storm_contrib(
    ${CMAKE_CURRENT_SOURCE_DIR}/contrib/khrplatform-20180315.tar.gz
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/KHR
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/KHR/khrplatform.h
)

storm_contrib(
    ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wglext-20181130.tar.gz
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL/wglext.h
)

storm_contrib(
    ${CMAKE_CURRENT_SOURCE_DIR}/contrib/lodepng-20180326.tar.gz
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng/lodepng.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng/lodepng.h
)

# See the 'texture_png.cpp' file for the details
set_source_files_properties(
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng/lodepng.cpp PROPERTIES
        HEADER_FILE_ONLY TRUE
)

target_sources(storm PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng/lodepng.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/lodepng/lodepng.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/blending_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/color.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/common_vertex_types.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/exception.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/input.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/matrix.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/output_technique.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/proxy_window_observer.cpp
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
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL/glcorearb.h
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/GL/wglext.h
    ${CMAKE_CURRENT_BINARY_DIR}/contrib/KHR/khrplatform.h
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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/win/window.cpp
    )
elseif(UNIX)
    target_sources(storm PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/posix/clock_posix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/display_x11.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/invisible_cursor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/pointer_locking_region.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/rendering_system_glx.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/storm/platform/x11/xcb_connection.cpp
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
    FILE storm-config-base.cmake
)

install(FILES storm-config.cmake DESTINATION lib/cmake/storm)

if(storm_build_examples)
    add_subdirectory(examples/advanced_rendering)
    add_subdirectory(examples/triangle_rendering)
    add_subdirectory(examples/user_input)
endif()
