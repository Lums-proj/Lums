file(GLOB SRC "*.cpp")
add_executable(02_Nyan ${SRC})
configure_file(Nyan.png Nyan.png COPYONLY)
target_link_libraries(02_Nyan Lums_shared)