file(GLOB SRC "*.cpp")
add_executable(01_Cube ${SRC})
target_link_libraries(01_Cube Lums_shared)