file(GLOB SRC "*.cpp")
add_executable(04_Audio ${SRC})
file(COPY font.frag.glsl font.vert.glsl music.ogg jump.ogg DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(04_Audio Lums_shared)