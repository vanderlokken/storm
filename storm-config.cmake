include(${CMAKE_CURRENT_LIST_DIR}/storm-config-base.cmake)

find_package(OpenGL REQUIRED)

if(UNIX)
    find_package(X11 REQUIRED)
endif()

get_target_property(STORM_INTERFACE_LINK_LIBRARIES
    storm::storm INTERFACE_LINK_LIBRARIES
)

if(STORM_INTERFACE_LINK_LIBRARIES MATCHES ".*PNG::PNG.*")
    find_package(PNG REQUIRED)
endif()

unset(STORM_INTERFACE_LINK_LIBRARIES)
