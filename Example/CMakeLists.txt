find_package(OpenGL REQUIRED)
find_package(imgui REQUIRED)
find_package(stb_image REQUIRED)
find_package(ScopeGuard REQUIRED)
find_package(Rendering REQUIRED)

include_directories( ${CAD_ROOT_DIR}/DGERendering/include)

add_subdirectory(1.getting_started)
#add_subdirectory(2.lighting)
#add_subdirectory(3.model_loading)
#add_subdirectory(4.advanced_opengl)
#add_subdirectory(5.advanced_lighting)