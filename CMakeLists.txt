cmake_minimum_required(VERSION 3.0)
project(lums)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-std=c++11 -fno-rtti -fno-exceptions -fcolor-diagnostics -Wall")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
add_subdirectory(src)
add_subdirectory(tests)
