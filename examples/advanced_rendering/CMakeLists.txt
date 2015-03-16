add_executable(storm_advanced_rendering WIN32
    resources.cpp
    resources.h
    advanced_rendering.cpp
)

target_link_libraries(storm_advanced_rendering storm)

if(WIN32)
    target_link_libraries(storm_advanced_rendering opengl32.lib)
elseif(UNIX)
    target_link_libraries(storm_advanced_rendering X11 GL)
endif()
