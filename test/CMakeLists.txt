file(GLOB SRC "*.cpp")
add_executable(unit ${SRC})
target_link_libraries(unit Lums_shared)
add_custom_target(tests COMMAND unit -c DEPENDS unit)