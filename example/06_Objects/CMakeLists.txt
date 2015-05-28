file(GLOB SRC "*.cpp")
add_executable(06_Objects ${SRC})
target_link_libraries(06_Objects Lums_shared)
