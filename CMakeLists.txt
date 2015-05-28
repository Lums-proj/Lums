cmake_minimum_required(VERSION 3.0)
project(Lums)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(NOT MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-exceptions")
endif()

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(FreeType REQUIRED)
find_package(PNG REQUIRED)
find_package(Vorbis REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories(${PNG_INCLUDE_DIRS} SYSTEM)
include_directories(${FREETYPE_INCLUDE_DIRS} SYSTEM)
include_directories(${VORBIS_INCLUDE_DIRS} SYSTEM)

add_subdirectory(src)
add_subdirectory(lmac)
if (NOT WIN32)
	add_subdirectory(test)
endif()
add_subdirectory(example)