project(imnodes)

set(_imnodes_Sources
        imnodes.h
        imnodes_internal.h
        imnodes.cpp
)
find_package(imgui REQUIRED)
add_library(${PROJECT_NAME} STATIC ${_imnodes_Sources})
target_include_directories(imnodes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ${CAD_ROOT_DIR}/External/imgui/
)

target_link_libraries(imnodes PUBLIC imgui)

# Example projects
if(IMNODES_EXAMPLES)

    find_package(SDL2 CONFIG REQUIRED)

    add_executable(colornode
        ${CMAKE_CURRENT_SOURCE_DIR}/imnodes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/color_node_editor.cpp)
    target_link_libraries(colornode imnodes SDL2::SDL2)
    if (APPLE)
        target_link_libraries(colornode "-framework OpenGL")
    elseif(MSVC)
        target_link_libraries(colornode "opengl32")
    else()
        target_link_libraries(colornode X11 Xext GL)
    endif()

    add_executable(multieditor
        ${CMAKE_CURRENT_SOURCE_DIR}/imnodes.cpp 
        ${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/multi_editor.cpp)
    target_link_libraries(multieditor imnodes SDL2::SDL2)
    if (APPLE)
        target_link_libraries(multieditor "-framework OpenGL")
    elseif(MSVC)
        target_link_libraries(multieditor "opengl32")
    else()
        target_link_libraries(multieditor X11 Xext GL)
    endif()

    add_executable(saveload
        ${CMAKE_CURRENT_SOURCE_DIR}/imnodes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/save_load.cpp)
    target_link_libraries(saveload imnodes SDL2::SDL2)
    if (APPLE)
        target_link_libraries(saveload "-framework OpenGL")
    elseif(MSVC)
        target_link_libraries(saveload "opengl32")
    else()
        target_link_libraries(saveload X11 Xext GL)
    endif()

    add_executable(hello
        ${CMAKE_CURRENT_SOURCE_DIR}/imnodes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/example/hello.cpp)
    target_link_libraries(hello imnodes SDL2::SDL2)
    if (APPLE)
        target_link_libraries(hello "-framework OpenGL")
    elseif(MSVC)
        target_link_libraries(hello "opengl32")
    else()
        target_link_libraries(hello X11 Xext GL)
    endif()
endif()
