#ifdef DMS
#include <glad/glad.h>
#include "DGERendering/MeshRender/DGEMesh.h"

namespace DGERendering::MeshRender
{
    void DGEVertexIndexBuffer::CreateBuffers(
        const std::vector<DGEVertexHolder>& p_vertices,
        const std::vector<unsigned int>&    p_indices)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_ibo);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, p_vertices.size() * sizeof(DGEVertexHolder), p_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(GLuint), p_indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DGEVertexHolder), 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DGEVertexHolder), (void*)offsetof(DGEVertexHolder, m_normal));

        glBindVertexArray(0);
    }

    void DGEVertexIndexBuffer::DeleteBuffers()
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &m_ibo);
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void DGEVertexIndexBuffer::Bind() { glBindVertexArray(m_vao); }

    void DGEVertexIndexBuffer::UnBind() { glBindVertexArray(0); }

    void DGEVertexIndexBuffer::Draw(int p_indexCount)
    {
        Bind();
        glDrawElements(GL_TRIANGLES, p_indexCount, GL_UNSIGNED_INT, nullptr);
        UnBind();
    }

    bool DGEMesh::Load(submesh& p_mesh)
    {
        m_vertices.clear();
        m_vertexIndices.clear();
        for (int index = 0; index < p_mesh.positions.size(); index++)
        {
            DGEVertexHolder vertex;
            vertex.m_pos = p_mesh.positions[index];
            vertex.m_normal = p_mesh.normals[index];
            AddVertex(vertex);
        }
        for (int index = 0; index < p_mesh.indices.size(); index++)
        {
            AddVertexIndex(p_mesh.indices[index]);
        }
        Initialize();
        return true;
    }

    DGEMesh::~DGEMesh() { DeleteBuffers(); }

    void DGEMesh::Initialize()
    {
        if (!m_renderBufferManager)
            m_renderBufferManager = std::make_unique<DGEVertexIndexBuffer>();
        CreateBuffers();
    }

    void DGEMesh::CreateBuffers() { m_renderBufferManager->CreateBuffers(m_vertices, m_vertexIndices); }

    void DGEMesh::DeleteBuffers() { m_renderBufferManager->DeleteBuffers(); }

    void DGEMesh::Bind() { m_renderBufferManager->Bind(); }

    void DGEMesh::UnBind() { m_renderBufferManager->UnBind(); }

    void DGEMesh::Render() { m_renderBufferManager->Draw((int)m_vertexIndices.size()); }

} // namespace DGERendering::MeshRender
#endif