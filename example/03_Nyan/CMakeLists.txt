file(GLOB SRC "*.cpp")
add_executable(03_Nyan ${SRC})
configure_file(Nyan.png Nyan.png COPYONLY)
target_link_libraries(03_Nyan Lums_shared)