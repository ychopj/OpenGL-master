#pragma once
#include "DGERendering/Core/Shader.h"
#include <memory>
#include <vector>
#include "learnopengl/filesystem.h"
namespace DGERendering::Resources
{
    class GGrid
    {
    public:
        GGrid();
        ~GGrid();
        void Draw();
        void Initialize();

        std::unique_ptr<DGERendering::Core::Shader> m_shader;

    private:
        unsigned int m_vao, m_vbo;

        std::vector<float> vertices;

        const std::string VERTEX_SHADER_FILE = FileSystem::getPath("resource_/shader/grid_shader.vs");
        const std::string FRAGMENT_SHADER_FILE = FileSystem::getPath("resource_/shader/grid_shader.fs");
    };
} // namespace DGERendering::Resources