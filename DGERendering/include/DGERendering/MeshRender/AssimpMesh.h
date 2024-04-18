#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace DGERendering::MeshRender
{
    class VertexHolder
    {
    public:
        VertexHolder() : m_pos(), m_normal() {}

        VertexHolder(const glm::vec3& p_pos, const glm::vec3& p_normal) : m_pos(p_pos), m_normal(p_normal) {}

        ~VertexHolder() = default;

        glm::vec3 m_pos;
        glm::vec3 m_normal;
        glm::vec2 m_uv;
    };
    class OpenGLVertexIndexBuffer
    {
    public:
        OpenGLVertexIndexBuffer() : m_vbo{0}, m_vao{0}, m_ibo{0} {}
        void CreateBuffers(const std::vector<VertexHolder>& p_vertices, const std::vector<unsigned int>& p_indices);
        void DeleteBuffers();
        void Bind();
        void UnBind();
        void Draw(int p_indexCount);

    private:
        unsigned int m_vbo;
        unsigned int m_vao;
        unsigned int m_ibo;
    };
    class AssimpMesh
    {
    public:
        AssimpMesh() = default;
        ~AssimpMesh();

        bool Load(const std::string& p_filePath);
        void AddVertex(const VertexHolder& p_vertex) { m_vertices.push_back(p_vertex); }
        void AddVertexIndex(unsigned int p_vertexIdx) { m_vertexIndices.push_back(p_vertexIdx); }

        std::vector<unsigned int> GetVertexIndices() { return m_vertexIndices; }

        void Initialize();
        void CreateBuffers();
        void DeleteBuffers();
        void Render();
        void Bind();
        void UnBind();

    private:
        std::unique_ptr<OpenGLVertexIndexBuffer> m_renderBufferManager;
        std::vector<VertexHolder>                m_vertices;
        std::vector<unsigned int>                m_vertexIndices;
    };

} // namespace DGERendering::MeshRender