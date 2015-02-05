file(GLOB SRC "*.cpp")
add_executable(03_Hello ${SRC})
target_link_libraries(03_Hello Lums_shared)