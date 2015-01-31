file(GLOB SRC "*.cpp")
add_executable(02_Nyan ${SRC})
file(COPY Nyan.png DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(02_Nyan Lums_shared)