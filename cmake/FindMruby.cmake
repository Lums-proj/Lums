#
# FindMruby.cmake
#

set(MRUBY_SEARCH_PATH
	/usr
	/usr/local
	~/.brew
)

find_library(
	MRUBY_LIBRARY
	mruby
	PATHS
	${MRUBY_SEARCH_PATH}
	PATH_SUFFIXES
	lib lib64
)

find_path(
	MRUBY_INCLUDE_DIRS
	mruby.h
	PATHS
	${MRUBY_SEARCH_PATH}
	PATH_SUFFIXES
	include
)

message(STATUS "Found mruby: ${MRUBY_LIBRARY}")
