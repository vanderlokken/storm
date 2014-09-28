add_executable(storm_triangle_rendering WIN32
    triangle_rendering.cpp
)

target_link_libraries(storm_triangle_rendering storm)

if(WIN32)
    target_link_libraries(storm_triangle_rendering opengl32.lib)
elseif(UNIX)
    target_link_libraries(storm_triangle_rendering X11 GL)
endif()

add_custom_command(
    TARGET storm_triangle_rendering POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.glsl" "${CMAKE_CURRENT_BINARY_DIR}/vertex_shader.glsl"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/pixel_shader.glsl" "${CMAKE_CURRENT_BINARY_DIR}/pixel_shader.glsl"
)
