find_package(OpenGL REQUIRED)

if(UNIX)
    find_package(X11 REQUIRED)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/storm-config-base.cmake)
