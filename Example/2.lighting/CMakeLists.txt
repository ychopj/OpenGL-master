cmake_minimum_required (VERSION 3.27)
project (one)

set (OPENGL_LIBRARIES ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})

file (GLOB_RECURSE ProjectSources *.c*)
file (GLOB_RECURSE ProjectHeaders *.h*)
#add_definitions(-DSHADER_DIR="${CAD_ROOT_DIR}/resource_/shader/")
#add_definitions(-DTEXTURE_DIR="${CAD_ROOT_DIR}/resource_/texture/")

foreach(source_file ${ProjectSources})
    # 获取源文件的文件名（不包含路径和扩展名）
    get_filename_component(EXEC_NAME ${source_file} NAME_WE)
    add_executable(${EXEC_NAME} ${source_file}
            ${CAD_ROOT_DIR}/External/glad/src/glad.c)
    target_link_libraries (${EXEC_NAME} PRIVATE  glfw3 OpenGL32 imgui  stb_image Rendering)
endforeach()

