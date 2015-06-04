file(GLOB SRC "*.cpp")
add_executable(03_Font ${SRC})
file(COPY font.frag.glsl font.vert.glsl DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(03_Font Lums_shared)