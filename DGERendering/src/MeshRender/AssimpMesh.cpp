#include <glad/glad.h>
#include "DGERendering/MeshRender/AssimpMesh.h"

namespace DGERendering::MeshRender
{

    void OpenGLVertexIndexBuffer::CreateBuffers(
        const std::vector<VertexHolder>& p_vertices,
        const std::vector<unsigned int>& p_indices)
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_ibo);
        glGenBuffers(1, &m_vbo);
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(
            GL_ARRAY_BUFFER, p_vertices.size() * sizeof(VertexHolder), p_vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER, p_indices.size() * sizeof(GLuint), p_indices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), (void*)offsetof(VertexHolder, m_normal));

        glBindVertexArray(0);
    }

    void OpenGLVertexIndexBuffer::DeleteBuffers()
    {
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &m_ibo);
        glDeleteBuffers(1, &m_vbo);
        glDeleteVertexArrays(1, &m_vao);
    }

    void OpenGLVertexIndexBuffer::Bind() { glBindVertexArray(m_vao); }

    void OpenGLVertexIndexBuffer::UnBind() { glBindVertexArray(0); }

    void OpenGLVertexIndexBuffer::Draw(int p_indexCount)
    {
        Bind();
        glDrawElements(GL_TRIANGLES, p_indexCount, GL_UNSIGNED_INT, nullptr);
        UnBind();
    }

    AssimpMesh::~AssimpMesh() { DeleteBuffers(); }

    bool AssimpMesh::Load(const std::string& p_filePath)
    {
        const uint32_t C_MESH_IMPORT_FLAGS = aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                             aiProcess_SortByPType | aiProcess_GenNormals |
                                             aiProcess_GenUVCoords | aiProcess_OptimizeMeshes |
                                             aiProcess_ValidateDataStructure;

        Assimp::Importer importer;

        const aiScene* p_scene = importer.ReadFile(p_filePath.c_str(), C_MESH_IMPORT_FLAGS);

        if (p_scene && p_scene->HasMeshes())
        {
            m_vertexIndices.clear();
            m_vertices.clear();

            auto* mesh = p_scene->mMeshes[0];

            for (uint32_t i = 0; i < mesh->mNumVertices; i++)
            {
                VertexHolder vh;
                vh.m_pos = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
                vh.m_normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

                AddVertex(vh);
            }

            for (size_t i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];

                for (size_t j = 0; j < face.mNumIndices; j++)
                    AddVertexIndex(face.mIndices[j]);
            }

            Initialize();
            return true;
        }
        return false;
    }

    void AssimpMesh::Initialize()
    {
        m_renderBufferManager = std::make_unique<OpenGLVertexIndexBuffer>();
        CreateBuffers();
    }

    void AssimpMesh::CreateBuffers() { m_renderBufferManager->CreateBuffers(m_vertices, m_vertexIndices); }

    void AssimpMesh::DeleteBuffers() { m_renderBufferManager->DeleteBuffers(); }

    void AssimpMesh::Bind() { m_renderBufferManager->Bind(); }

    void AssimpMesh::UnBind() { m_renderBufferManager->UnBind(); }

    void AssimpMesh::Render() { m_renderBufferManager->Draw((int)m_vertexIndices.size()); }
} // namespace DGERendering::MeshRender
