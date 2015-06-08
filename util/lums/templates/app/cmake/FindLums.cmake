#
# FindLums.cmake
#

find_package(OpenGL)

set(LUMS_SEARCH_PATH
    /usr
    /usr/local
    ~/.brew
)

find_library(LUMS_LIBRARIES
    Lums
    PATHS
    ${LUMS_SEARCH_PATH}
    PATH_SUFFIXES
    lib
    lib64
)

find_path(LUMS_INCLUDE_DIRS
    LumsInclude
    PATHS
    ${LUMS_SEARCH_PATH}
    PATH_SUFFIXES
    include
)

message(STATUS "Found Lums : ${LUMS_LIBRARIES}")

list(APPEND LUMS_LIBRARIES ${OPENGL_gl_LIBRARY})
