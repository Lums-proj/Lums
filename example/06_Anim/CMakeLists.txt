file(GLOB SRC "*.cpp")
add_executable(06_Anim ${SRC})
file(COPY anim.frag.glsl anim.vert.glsl animtex.frag.glsl animtex.vert.glsl DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(06_Anim Lums_shared)
