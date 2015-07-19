file(GLOB SRC "*.cpp")
add_executable(benchmark ${SRC})
target_link_libraries(benchmark Lums_shared)
