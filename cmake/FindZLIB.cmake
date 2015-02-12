#
# FindZLIB.cmake
#

if (WIN32)

	set(WIN_LIB_PATH ${CMAKE_SOURCE_DIR}/ext)
	if (MSVC)
		set(WIN_LIB_PATH "${WIN_LIB_PATH}/msvc")
	else()
		set(WIN_LIB_PATH "${WIN_LIB_PATH}/mingw")
	endif()
	if (${CMAKE_SIZEOF_VOID_P} EQUAL 8)
		set (WIN_LIB_PATH "${WIN_LIB_PATH}64")
	endif()

	if (CMAKE_BUILD_TYPE MATCHES "Debug")
		set (WIN_DEBUG "d")
	endif()

	set (ZLIB_LIBRARIES "${WIN_LIB_PATH}/lib/zlib${WIN_DEBUG}.lib")
	set (ZLIB_INCLUDE_DIRS "${WIN_LIB_PATH}/include")
	set (ZLIB_RUNTIME "${WIN_LIB_PATH}/bin/zlib${WIN_DEBUG}.dll")

else()

	set(ZLIB_SEARCH_PATH
		/usr
		/usr/local
		~/.brew
	)

	find_library(
		ZLIB_LIBRARIES
		z
		PATHS
		${ZLIB_SEARCH_PATH}
		PATH_SUFFIXES lib lib64
	)

	find_path(
	 	ZLIB_INCLUDE_DIRS
	 	zlib.h
	 	PATHS
	 	${ZLIB_SEARCH_PATH}
	 	PATH_SUFFIXES include
	 	NO_DEFAULT_PATH
	)

endif()

message(STATUS "Found zlib: ${ZLIB_LIBRARIES}")

