project(imgui)

set(_imgui_Sources
    imconfig.h
    imgui.cpp
    imgui.h
    imgui.natvis
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_widgets.cpp
    imgui_tables.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    LICENSE.txt
)

add_library(${PROJECT_NAME} STATIC ${_imgui_Sources} )

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_compile_definitions(${PROJECT_NAME} PUBLIC "ImDrawIdx=unsigned int")
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_DISABLE_OBSOLETE_FUNCTIONS)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "external")

