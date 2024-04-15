project(imgui_node_editor VERSION 1.76)

find_package(imgui REQUIRED)
set(_imgui_node_editor_Sources
        crude_json.cpp
        crude_json.h
        imgui_bezier_math.h
        imgui_bezier_math.inl
        imgui_canvas.cpp
        imgui_canvas.cpp
        imgui_canvas.h
        imgui_canvas.h
        imgui_extra_math.h
        imgui_extra_math.inl
        imgui_node_editor_api.cpp
        imgui_node_editor_internal.h
        imgui_node_editor_internal.inl
        imgui_node_editor.cpp
        imgui_node_editor.h
        imgui_node_editor.natvis
)

add_library(imgui_node_editor STATIC
        ${_imgui_node_editor_Sources}
)

target_link_libraries(imgui_node_editor PUBLIC imgui)

source_group(TREE ${CAD_ROOT_DIR}/External/node-editor FILES ${_imgui_node_editor_Sources})


