#include <glad/glad.h>
#include "DGERendering/Resources/GGrid.h"
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
namespace DGERendering::Resources
{
    GGrid::GGrid() : m_shader(nullptr) {}

    GGrid::~GGrid()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
    }

    void GGrid::Initialize()
    {
        // Set up vertex data and buffers

        float gridSize = 10.0f;
        float gridSpacing = 1.0f;
        float halfSize = gridSize / 2.0f;

        for (float x = -halfSize; x <= halfSize; x += gridSpacing)
        {
            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(-halfSize);
            vertices.push_back(x);
            vertices.push_back(0.0f);
            vertices.push_back(halfSize);
        }
        for (float z = -halfSize; z <= halfSize; z += gridSpacing)
        {
            vertices.push_back(-halfSize);
            vertices.push_back(0.0f);
            vertices.push_back(z);
            vertices.push_back(halfSize);
            vertices.push_back(0.0f);
            vertices.push_back(z);
        }

        m_shader = std::make_unique<DGERendering::Core::Shader>();
        m_shader->Load(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);

        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void GGrid::Draw()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_shader->Use();
        m_shader->Set("centerLine", glm::vec3(0, 0, 0));
        glBindVertexArray(m_vao);
        glDrawArrays(GL_LINES, 0, vertices.size() / 3);
        glBindVertexArray(0);
        glDisable(GL_BLEND);
    }
} // namespace DGERendering::Resources