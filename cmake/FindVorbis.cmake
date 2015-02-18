#
# FindVorbis.cmake
#

set(VORBIS_SEARCH_PATH
	/usr
	/usr/local
	~/.brew
)

find_library(
	VORBIS_LIBRARIES
	vorbis
	PATHS
	${VORBIS_SEARCH_PATH}
	PATH_SUFFIXES lib lib64
)

find_library(
	OGG_LIBRARIES
	ogg
	PATHS
	${VORBIS_SEARCH_PATH}
	PATH_SUFFIXES lib lib64
)

find_library(
	VORBISFILE_LIBRARIES
	vorbisfile
	PATHS
	${VORBIS_SEARCH_PATH}
	PATH_SUFFIXES lib lib64
)

find_path(
 	VORBIS_INCLUDE_DIRS
 	vorbis/vorbisfile.h
 	PATHS
 	${VORBIS_SEARCH_PATH}
 	PATH_SUFFIXES include
 	NO_DEFAULT_PATH
)

list(APPEND VORBIS_LIBRARIES ${OGG_LIBRARIES} ${VORBISFILE_LIBRARIES})

message(STATUS "Found vorbis: ${VORBIS_LIBRARIES}")
