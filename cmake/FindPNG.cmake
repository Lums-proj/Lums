#
# FindPNG.cmake
#

find_package(ZLIB)

set(PNG_SEARCH_PATH
	/usr
	/usr/local
	~/.brew
)

find_library(
	PNG_LIBRARIES
	libpng.a
	PATHS
	${PNG_SEARCH_PATH}
	PATH_SUFFIXES lib lib64
)

find_path(
 	PNG_INCLUDE_DIRS
 	png.h
 	PATHS
 	${PNG_SEARCH_PATH}
 	PATH_SUFFIXES include
 	NO_DEFAULT_PATH
)

list(APPEND PNG_LIBRARIES ${ZLIB_LIBRARIES})

message(STATUS "Found libpng: ${PNG_LIBRARIES}")
message(STATUS "toto ${PNG_INCLUDE_DIRS}")
