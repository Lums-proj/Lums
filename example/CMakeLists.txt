include_directories(../include)
add_subdirectory(01_Cube)
add_subdirectory(02_Nyan)
add_custom_target(example DEPENDS 01_Cube 02_Nyan)