file(GLOB SRC "*.cpp")
add_executable(01_Cube ${SRC})
file(COPY cube.frag.glsl cube.vert.glsl DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(01_Cube Lums_shared)
