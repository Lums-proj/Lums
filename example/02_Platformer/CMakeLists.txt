file(GLOB SRC "*.cpp")
add_executable(02_Platformer ${SRC})
target_link_libraries(02_Platformer Lums_shared)