file(GLOB SRC "*.cpp")
add_executable(03_Hello ${SRC})
file(COPY mario.png hello.mrb music.ogg jump.ogg DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_link_libraries(03_Hello Lums_shared)
