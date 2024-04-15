#pragma once
#ifdef DMS
#include <vector>
#include <DGE.h>

namespace DGERendering::MeshRender
{
    using namespace DGE;
    class DGEVertexHolder
    {
    public:
        DGEVertexHolder() : m_pos(), m_normal() {}
        DGEVertexHolder(const vec3& p_pos, const vec3& p_normal) : m_pos(p_pos), m_normal(p_normal) {}
        ~DGEVertexHolder() = default;
        vec3 m_pos;
        vec3 m_normal;
        // vec2 m_uv;
    };

    class DGEVertexIndexBuffer
    {
    public:
        DGEVertexIndexBuffer() : m_vbo{0}, m_vao{0}, m_ibo{0} {}
        void CreateBuffers(const std::vector<DGEVertexHolder>& p_vertices, const std::vector<unsigned int>& p_indices);
        void DeleteBuffers();
        void Bind();
        void UnBind();
        void Draw(int p_indexCount);

    private:
        unsigned int m_vbo;
        unsigned int m_vao;
        unsigned int m_ibo;
    };

    class DGEMesh
    {
    public:
        DGEMesh() {}
        DGEMesh(const DGEMesh& p_other)
        {
            m_vertices = p_other.m_vertices;
            m_vertexIndices = p_other.m_vertexIndices;
            m_renderBufferManager = std::make_unique<DGEVertexIndexBuffer>(*p_other.m_renderBufferManager);
        }
        ~DGEMesh();

        bool Load(submesh& p_mesh);
        void AddVertex(const DGEVertexHolder& p_vertex) { m_vertices.push_back(p_vertex); }
        void AddVertexIndex(unsigned int p_vertexIdx) { m_vertexIndices.push_back(p_vertexIdx); }

        std::vector<unsigned int> GetVertexIndices() { return m_vertexIndices; }

        void Initialize();
        void CreateBuffers();
        void DeleteBuffers();
        void Render();
        void Bind();
        void UnBind();

    private:
        std::unique_ptr<DGEVertexIndexBuffer> m_renderBufferManager;
        std::vector<DGEVertexHolder>          m_vertices;
        std::vector<unsigned int>             m_vertexIndices;
    };
} // namespace DGERendering::MeshRender
#endif