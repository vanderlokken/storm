add_executable(storm_triangle_rendering WIN32
    triangle_rendering.cpp
)

target_link_libraries(storm_triangle_rendering storm)

if(WIN32)
    target_link_libraries(storm_triangle_rendering opengl32.lib)
elseif(UNIX)
    target_link_libraries(storm_triangle_rendering X11 GL)
endif()
