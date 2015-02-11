#
# FindFreeType.cmake
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

	set (FREETYPE_LIBRARIES "${WIN_LIB_PATH}/lib/freetype.lib")
	set (FREETYPE_INCLUDE_DIRS "${WIN_LIB_PATH}/include")

else()

	set(FREETYPE_SEARCH_PATH
		/usr
		/usr/local
		~/.brew
	)

	find_library(
		FREETYPE_LIBRARIES
		freetype
		PATHS
		${FREETYPE_SEARCH_PATH}
		PATH_SUFFIXES lib lib64
	)

	find_path(
	 	FREETYPE_INCLUDE_DIRS
	 	ft2build.h
	 	PATHS
	 	${FREETYPE_SEARCH_PATH}
	 	PATH_SUFFIXES include
	 	NO_DEFAULT_PATH
	)

endif()

message(STATUS "Found freetype: ${FREETYPE_LIBRARIES}")
