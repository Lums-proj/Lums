file(GLOB SRC "*.cpp")
file(GLOB HEADER "../include/Lums/*.hpp")
set(LINK_LIB ${OPENGL_gl_LIBRARY} ${PNG_LIBRARIES} ${FREETYPE_LIBRARIES})

if(APPLE)
    file(GLOB OS_SRC "MacOSX/*.cpp" "MacOSX/*.mm")
    include_directories(MacOSX)
    list(APPEND LINK_LIB "-framework Cocoa")
endif()

if(WIN32)
	file(GLOB OS_SRC "Windows/*.cpp")
endif()

list(APPEND SRC ${OS_SRC})

set(LUMS_ALL lums_shared)

add_library(Lums_shared SHARED ${SRC} ${HEADER})
set_target_properties(Lums_shared PROPERTIES OUTPUT_NAME Lums DEFINE_SYMBOL "EXPORT_DLL")
target_link_libraries(Lums_shared ${LINK_LIB})
install(TARGETS Lums_shared DESTINATION lib)

if (WIN32)
    file(GLOB DLL "${CMAKE_SOURCE_DIR}/ext/win32/bin/*.dll")
    file(COPY ${DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

if (NOT WIN32)
	add_library(Lums_static STATIC ${SRC} ${HEADER})
	set_target_properties(Lums_static PROPERTIES OUTPUT_NAME Lums)
	install(TARGETS Lums_static DESTINATION lib)
	list(APPEND LUMS_ALL lums_static)
endif()

if (APPLE)
    add_library(Lums_framework SHARED ${SRC} ${HEADER})
    set_target_properties(Lums_framework PROPERTIES OUTPUT_NAME Lums FRAMEWORK ON PUBLIC_HEADER "${HEADER}")
    target_link_libraries(Lums_framework ${LINK_LIB})
    install(TARGETS Lums_framework DESTINATION Library/Frameworks)
    list(APPEND LUMS_ALL lums_framework)
endif ()

install(DIRECTORY ../include/Lums DESTINATION include)
add_custom_target(Lums DEPENDS ${LUMS_ALL})