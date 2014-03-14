cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8.12.2)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "In-source builds are not allowed; please specify standalone build directory.")
endif()

project(storm)

option(storm_build_examples "Whether to build examples or not" ON)

include_directories(include src)

if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /GR-")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /D NDEBUG")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT /D NDEBUG")
endif()

set(storm_includes
    ${CMAKE_SOURCE_DIR}/include/storm/blending_technique.h
    ${CMAKE_SOURCE_DIR}/include/storm/buffer.h
    ${CMAKE_SOURCE_DIR}/include/storm/camera.h
    ${CMAKE_SOURCE_DIR}/include/storm/clock.h
    ${CMAKE_SOURCE_DIR}/include/storm/color.h
    ${CMAKE_SOURCE_DIR}/include/storm/common_vertex_types.h
    ${CMAKE_SOURCE_DIR}/include/storm/dimensions.h
    ${CMAKE_SOURCE_DIR}/include/storm/display.h
    ${CMAKE_SOURCE_DIR}/include/storm/event_handler.h
    ${CMAKE_SOURCE_DIR}/include/storm/exception.h
    ${CMAKE_SOURCE_DIR}/include/storm/flat_vector.h
    ${CMAKE_SOURCE_DIR}/include/storm/flat_vector.inl
    ${CMAKE_SOURCE_DIR}/include/storm/framework.h
    ${CMAKE_SOURCE_DIR}/include/storm/keyboard.h
    ${CMAKE_SOURCE_DIR}/include/storm/math.h
    ${CMAKE_SOURCE_DIR}/include/storm/matrix.h
    ${CMAKE_SOURCE_DIR}/include/storm/matrix.inl
    ${CMAKE_SOURCE_DIR}/include/storm/mesh.h
    ${CMAKE_SOURCE_DIR}/include/storm/mouse.h
    ${CMAKE_SOURCE_DIR}/include/storm/output_technique.h
    ${CMAKE_SOURCE_DIR}/include/storm/quaternion.h
    ${CMAKE_SOURCE_DIR}/include/storm/quaternion.inl
    ${CMAKE_SOURCE_DIR}/include/storm/rasterization_technique.h
    ${CMAKE_SOURCE_DIR}/include/storm/rectangle.h
    ${CMAKE_SOURCE_DIR}/include/storm/rendering_buffer_set.h
    ${CMAKE_SOURCE_DIR}/include/storm/rendering_system.h
    ${CMAKE_SOURCE_DIR}/include/storm/rendering_window.h
    ${CMAKE_SOURCE_DIR}/include/storm/resource_type.h
    ${CMAKE_SOURCE_DIR}/include/storm/sampler.h
    ${CMAKE_SOURCE_DIR}/include/storm/shader.h
    ${CMAKE_SOURCE_DIR}/include/storm/storm.h
    ${CMAKE_SOURCE_DIR}/include/storm/texture.h
    ${CMAKE_SOURCE_DIR}/include/storm/transformation.h
    ${CMAKE_SOURCE_DIR}/include/storm/vector.h
    ${CMAKE_SOURCE_DIR}/include/storm/vector.inl
    ${CMAKE_SOURCE_DIR}/include/storm/vertex_format.h
)

set(storm_common_sources
    ${CMAKE_SOURCE_DIR}/src/storm/blending_technique.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/camera.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/color.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/common_vertex_types.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/event_handler_vector.h
    ${CMAKE_SOURCE_DIR}/src/storm/exception.cpp
    # ${CMAKE_SOURCE_DIR}/src/storm/high_precision_clock.cpp
    # ${CMAKE_SOURCE_DIR}/src/storm/high_precision_clock.h
    ${CMAKE_SOURCE_DIR}/src/storm/matrix.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/mesh.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/noncopyable.h
    ${CMAKE_SOURCE_DIR}/src/storm/output_technique.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/rasterization_technique.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/rendering_system_common.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/rendering_system_common.h
    ${CMAKE_SOURCE_DIR}/src/storm/sampler.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/shader.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/throw_exception.h
    ${CMAKE_SOURCE_DIR}/src/storm/transformation.cpp
)

set(storm_ogl_sources
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/api_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/api_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/blending_technique_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/blending_technique_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/buffer_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/buffer_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/check_result_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/handle_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/mesh_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/mesh_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/output_technique_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/output_technique_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rasterization_technique_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rasterization_technique_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rendering_buffer_set_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rendering_buffer_set_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rendering_system_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/rendering_system_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/resource_type_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/resource_type_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/sampler_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/sampler_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/shader_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/shader_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/texture_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/texture_ogl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/vertex_format_ogl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/ogl/vertex_format_ogl.h
)

set(storm_win_sources
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/check_result.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/display_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/display_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/framework_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/framework_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/input_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/input_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/keyboard_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/keyboard_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/mouse_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/mouse_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/multimedia_clock_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/multimedia_clock_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/rendering_system_wgl.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/rendering_window_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/rendering_window_win.h
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/window_procedure_win.cpp
    ${CMAKE_SOURCE_DIR}/src/storm/platform/win/window_procedure_win.h
)

add_library(storm STATIC
    ${storm_includes}
    ${storm_common_sources}
    ${storm_ogl_sources}
    ${storm_win_sources}
)

if(storm_build_examples)
    add_subdirectory(examples/triangle_rendering)
endif()
