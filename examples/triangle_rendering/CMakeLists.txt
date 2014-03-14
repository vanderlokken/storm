add_executable(storm_triangle_rendering WIN32
    triangle_rendering.cpp
)

target_link_libraries(storm_triangle_rendering storm)

if(WIN32)
    target_link_libraries(storm_triangle_rendering opengl32.lib)
endif()

add_custom_command(
    TARGET storm_triangle_rendering POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/vertex_shader.glsl" $<TARGET_FILE_DIR:storm_triangle_rendering>
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/pixel_shader.glsl" $<TARGET_FILE_DIR:storm_triangle_rendering>
)
