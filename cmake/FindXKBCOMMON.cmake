find_package(PkgConfig)

include(FindPackageHandleStandardArgs)

pkg_check_modules(PC_XKBCOMMON QUIET xkbcommon)
pkg_check_modules(PC_XKBCOMMON_X11 QUIET xkbcommon-x11)

find_path(XKBCOMMON_INCLUDE_DIR
    NAMES xkbcommon.h
    HINTS ${PC_XKBCOMMON_INCLUDE_DIRS}
    PATH_SUFFIXES xkbcommon
)

find_path(XKBCOMMON_X11_INCLUDE_DIR
    NAMES xkbcommon-x11.h
    HINTS ${PC_XKBCOMMON_X11_INCLUDE_DIRS}
    PATH_SUFFIXES xkbcommon
)

find_library(XKBCOMMON_LIBRARY
    NAMES xkbcommon
    HINTS ${PC_XKBCOMMON_LIBRARY_DIRS}
)

find_library(XKBCOMMON_X11_LIBRARY
    NAMES xkbcommon-x11
    HINTS ${PC_XKBCOMMON_X11_LIBRARY_DIRS}
)

mark_as_advanced(
    XKBCOMMON_INCLUDE_DIR
    XKBCOMMON_LIBRARY
    XKBCOMMON_X11_INCLUDE_DIR
    XKBCOMMON_X11_LIBRARY
)

find_package_handle_standard_args(XKBCOMMON
    REQUIRED_VARS
        XKBCOMMON_INCLUDE_DIR
        XKBCOMMON_LIBRARY
        XKBCOMMON_X11_INCLUDE_DIR
        XKBCOMMON_X11_LIBRARY
)
