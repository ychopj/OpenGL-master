project(Rendering LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/*.inl")
set(_Rendering_SourceDir  ${SOURCES})

include_directories(include)

find_package(stb_image REQUIRED)
find_package(imgui REQUIRED)

add_library(Rendering STATIC ${_Rendering_SourceDir}
        ${CAD_ROOT_DIR}/External/glad/src/glad.c
)
target_link_libraries(Rendering PUBLIC stb_image imgui)

target_compile_definitions(${PROJECT_NAME} PUBLIC SHADER_DIR="${CAD_ROOT_DIR}/resource_/shader/")
target_compile_definitions(${PROJECT_NAME} PUBLIC TEXTURE_DIR="${CAD_ROOT_DIR}/resource_/texture/")
target_compile_definitions(${PROJECT_NAME} PUBLIC MODEL_DIR="${CAD_ROOT_DIR}/resource_/model/")
target_link_libraries(${PROJECT_NAME} PRIVATE assimp-vc142-mtd)



