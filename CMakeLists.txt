cmake_minimum_required(VERSION 3.27)
project(OpenGL)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED   YES)
set(CMAKE_CXX_STANDARD 17)

get_filename_component(CAD_ROOT_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE CACHE)
list(APPEND CMAKE_MODULE_PATH ${CAD_ROOT_DIR}/misc/cmake-modules)

# 添加头文件目录
include_directories( ${PROJECT_SOURCE_DIR}/External/)
include_directories( ${PROJECT_SOURCE_DIR}/External/imgui)
include_directories( ${PROJECT_SOURCE_DIR}/External/glfw/include)
include_directories( ${PROJECT_SOURCE_DIR}/External/glad/include)
include_directories(includes)
#库目录
link_directories(${PROJECT_SOURCE_DIR}/External/glfw/lib-vc2010-64)
link_directories(${PROJECT_SOURCE_DIR}/External/assimp)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

add_subdirectory(Example)
