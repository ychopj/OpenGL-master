#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <imgui/imgui.h>

#include "DGERendering/Objects/SceneObject.h"

DGERendering::Objects::SceneObject::SceneObject() { m_name = "object"; }
DGERendering::Objects::SceneObject::SceneObject(std::string p_name, bool p_isEditor) : m_name(p_name), m_isEditor(p_isEditor)
{
}
void DGERendering::Objects::SceneObject::RenderAttribute()
{
    ImGui::Text("%s", ("name : " + m_name).c_str());
    ImGui::NewLine();
    ImGui::Text("%s", ("id : " + std::to_string(m_id)).c_str());
}




#ifdef DMS
using namespace DGE;
#include <Modeling/interface/vector_imp.h>

DGERendering::Objects::SceneDGEEntity3D::SceneDGEEntity3D(std::shared_ptr<DGE::Entity3D> p_entity, bool p_isEditor)
{
    m_isEditor = p_isEditor;
    m_Entity = p_entity;
    myMeshing.GenerateSubmesh(m_Entity, m_Mesh);
    setupMesh();

    DGERendering::Resources::Material* material;
    material = DGERendering::Resources::MaterialManager::CreateMaterialByType(DGERendering::Resources::MODEL_MATERIAL);
    DGERendering::Resources::ModelMaterial* tmp = dynamic_cast<DGERendering::Resources::ModelMaterial*>(material);
    m_MeshRender = new DGERendering::Core::DGEMeshRender(material, &m_Mesh);
    m_atr_meshRender = new DGERendering::Resources::ATR_MeshRender(m_MeshRender);
}

DGERendering::Objects::SceneDGEEntity3D::SceneDGEEntity3D(
    std::shared_ptr<DGE::Entity3D> p_entity,
    std::string                    p_name,
    bool                           p_isEditor)
    : SceneDGEEntity3D(p_entity, p_isEditor)
{
    m_name = p_name;
}

DGERendering::Objects::SceneDGEEntity3D::~SceneDGEEntity3D()
{
    delete m_MeshRender;
    delete m_atr_meshRender;
}

void DGERendering::Objects::SceneDGEEntity3D::RenderAttribute()
{
    // position
    static float tmp_position[3];
    tmp_position[0] = m_Entity->GetTransform().GetPosition().x;
    tmp_position[1] = m_Entity->GetTransform().GetPosition().y;
    tmp_position[2] = m_Entity->GetTransform().GetPosition().z;
    ImGui::DragFloat3("Position", tmp_position, 0.1f);
    // rotation
    static float tmp_rotation[3];
    tmp_rotation[0] = m_Entity->GetTransform().GetRotation().x * 180 / PI;
    tmp_rotation[1] = m_Entity->GetTransform().GetRotation().y * 180 / PI;
    tmp_rotation[2] = m_Entity->GetTransform().GetRotation().z * 180 / PI;
    ImGui::DragFloat3("Rotation", tmp_rotation, 0.1f);
    // scale
    static float tmp_scale[3];
    tmp_scale[0] = m_Entity->GetTransform().GetScaling().x;
    tmp_scale[1] = m_Entity->GetTransform().GetScaling().x;
    tmp_scale[2] = m_Entity->GetTransform().GetScaling().x;
    ImGui::DragFloat3("Scale", tmp_scale, 0.1f);

    // Transform3 _transform;
    // _transform.SetPosition(Vector3(tmp_position[0], tmp_position[1], tmp_position[2]));
    // _transform.SetRotation(tmp_rotation[0], tmp_rotation[1], tmp_rotation[2]);
    // _transform.SetScaling(Vector3(tmp_scale[0], tmp_scale[1], tmp_scale[2]));
    // m_Entity->SetTransform(_transform);

    m_atr_meshRender->UI_Implement();
}

void DGERendering::Objects::SceneDGEEntity3D::Draw()
{
    myMeshing.GenerateSubmesh(m_Entity, m_Mesh);
    setupMesh();
    m_MeshRender->Draw();
}

inline DGE::vec3 Torgb(int p_v)
{
    return DGE::vec3(GetRValue(p_v) / 255.0f, GetGValue(p_v) / 255.0f, GetBValue(p_v) / 255.0f);
}

void DGERendering::Objects::SceneDGEEntity3D::setupMesh()
{
    m_Mesh.m_submesh.calc_aabb();
    if (m_Mesh.m_submesh.vertices.empty())
        return;
    {
        m_Mesh.m_submesh.positions.assign(m_Mesh.m_submesh.vertices.size(), DGE::vec3::ZERO);
        for (int i = 0; i < m_Mesh.m_submesh.vertices.size(); i++)
        {
            m_Mesh.m_submesh.positions[i] = m_Mesh.m_submesh.vertices[i].p;
        }
    }
    {
        m_Mesh.m_submesh.normals.assign(m_Mesh.m_submesh.vertices.size(), DGE::vec3::ZERO);
        m_Mesh.m_submesh.colors.assign(m_Mesh.m_submesh.vertices.size(), DGE::vec3::ZERO);
        for (int i = 0; i < m_Mesh.m_submesh.tris.size(); i++)
        {
            int t1 = m_Mesh.m_submesh.tris[i].v[0];
            int t2 = m_Mesh.m_submesh.tris[i].v[1];
            int t3 = m_Mesh.m_submesh.tris[i].v[2];

            DGE::vertex& p1 = m_Mesh.m_submesh.vertices[t1];
            DGE::vertex& p2 = m_Mesh.m_submesh.vertices[t2];
            DGE::vertex& p3 = m_Mesh.m_submesh.vertices[t3];

            DGE::vec3 nm = -(p2.p - p1.p).cross(p3.p - p1.p);
            nm.norm();
            m_Mesh.m_submesh.normals[t1] += nm;
            m_Mesh.m_submesh.normals[t2] += nm;
            m_Mesh.m_submesh.normals[t3] += nm;

            {
                m_Mesh.m_submesh.colors[t1] = Torgb(p1.cor);
                m_Mesh.m_submesh.colors[t2] = Torgb(p2.cor);
                m_Mesh.m_submesh.colors[t3] = Torgb(p3.cor);
            }
        }
    }
    {
        m_Mesh.m_submesh.uvs.assign(m_Mesh.m_submesh.vertices.size(), DGE::vec2::ZERO);
        for (int i = 0; i < m_Mesh.m_submesh.vertices.size(); i++)
        {
            m_Mesh.m_submesh.uvs[i] = m_Mesh.m_submesh.vertices[i].uv;
        }
    }
    {
        for (int i = 0; i < m_Mesh.m_submesh.vertices.size(); i++)
        {
            if (m_Mesh.m_submesh.vertices[i].n != DGE::vec3::ZERO)
                m_Mesh.m_submesh.normals[i] = m_Mesh.m_submesh.vertices[i].n;
            else
                m_Mesh.m_submesh.normals[i].norm();
        }
        m_Mesh.m_submesh.indices.assign(m_Mesh.m_submesh.tris.size() * 3, 0);
        for (int cnt = 0, i = 0; i < m_Mesh.m_submesh.tris.size(); i++)
        {
            m_Mesh.m_submesh.indices[cnt++] = m_Mesh.m_submesh.tris[i].v[0];
            m_Mesh.m_submesh.indices[cnt++] = m_Mesh.m_submesh.tris[i].v[1];
            m_Mesh.m_submesh.indices[cnt++] = m_Mesh.m_submesh.tris[i].v[2];
        }
    }
}

// DGERendering::Objects::SceneAuxObject::SceneAuxObject(
//     std::shared_ptr<VERLIST> p_verlist,
//     std::string              p_name,
//     bool                     p_isEditor)
// {
//     m_verlist = p_verlist;
//     m_isEditor = p_isEditor;
//     m_name = p_name;
// }

// DGERendering::Objects::SceneAuxObject::~SceneAuxObject() {}

// void DGERendering::Objects::SceneAuxObject::RenderAttribute() {}

// void DGERendering::Objects::SceneAuxObject::Draw() {}

DGERendering::Objects::SceneFormPHG::SceneFormPHG(
    std::vector<SUBMESHPTR> p_smlist,
    std::string             p_name,
    bool                    p_isEditor /*= false*/)
{
    m_name = p_name;
    m_isEditor = p_isEditor;
    m_smlist = p_smlist;
    m_renderList.reserve(m_smlist.size());
    for (auto sm : m_smlist)
    {
        setup(*sm);
        m_renderList.emplace_back();
        m_renderList.back().Load(*sm);
    }
}

void DGERendering::Objects::SceneFormPHG::setup(submesh& p_mesh)
{
    p_mesh.calc_aabb();
    if (p_mesh.vertices.empty())
        return;
    {
        p_mesh.positions.assign(p_mesh.vertices.size(), vector3::ZERO);
        for (int i = 0; i < p_mesh.vertices.size(); i++)
        {
            p_mesh.positions[i] = p_mesh.vertices[i].p;
        }
    }
    {
        p_mesh.normals.assign(p_mesh.vertices.size(), vec3::ZERO);
        p_mesh.colors.assign(p_mesh.vertices.size(), vec3::ZERO);
        for (int i = 0; i < p_mesh.tris.size(); i++)
        {
            int t1 = p_mesh.tris[i].v[0];
            int t2 = p_mesh.tris[i].v[1];
            int t3 = p_mesh.tris[i].v[2];

            vertex& p1 = p_mesh.vertices[t1];
            vertex& p2 = p_mesh.vertices[t2];
            vertex& p3 = p_mesh.vertices[t3];

            vec3 nm = -(p2.p - p1.p).cross(p3.p - p1.p);
            nm.norm();
            p_mesh.normals[t1] += nm;
            p_mesh.normals[t2] += nm;
            p_mesh.normals[t3] += nm;

            /*{
                mesh.colors[t1] = torgb(p1.cor);
                mesh.colors[t2] = torgb(p2.cor);
                mesh.colors[t3] = torgb(p3.cor);
            }*/
            /*  else
              {
                  mesh.colors[t1] = VGRAY;
                  mesh.colors[t2] = VGRAY;
                  mesh.colors[t3] = VGRAY;
              }*/
        }
    }
    {
        for (int i = 0; i < p_mesh.vertices.size(); i++)
        {
            if (p_mesh.vertices[i].n != vec3::ZERO)
                p_mesh.normals[i] = p_mesh.vertices[i].n;
            else
                p_mesh.normals[i].norm();
        }
        p_mesh.indices.assign(p_mesh.tris.size() * 3, 0);
        for (int cnt = 0, i = 0; i < p_mesh.tris.size(); i++)
        {
            p_mesh.indices[cnt++] = p_mesh.tris[i].v[0];
            p_mesh.indices[cnt++] = p_mesh.tris[i].v[1];
            p_mesh.indices[cnt++] = p_mesh.tris[i].v[2];
        }
    }
    /*    mesh.vertices.clear();
        mesh.tris.clear();
        mesh.cors.clear();*/

    /* for (auto sm : m_smlist)
     {
         gl_drawSm(*sm);
     }*/
}

void DGERendering::Objects::SceneFormPHG::drawSm(submesh& p_mesh)
{
    // glDisable(GL_CULL_FACE);
    // glPushMatrix();
    // glScalef(1.0, 1.0, 1.0);

    // if (p_mesh.positions.empty())
    //     return;

    // glEnableClientState(GL_VERTEX_ARRAY);
    // glVertexPointer(3, GL_FLOAT, sizeof(DGE::vec3), &p_mesh.positions[0]);

    // if (!p_mesh.normals.empty())
    // {
    //     glEnableClientState(GL_NORMAL_ARRAY);
    //     glNormalPointer(GL_FLOAT, sizeof(DGE::vec3), &p_mesh.normals[0]);
    //     glEnableClientState(GL_COLOR_ARRAY);
    //     glColorPointer(3, GL_FLOAT, sizeof(DGE::vec3), &p_mesh.colors[0]);
    // }

    // if (!p_mesh.uvs.empty())
    // {
    //     // glEnable(GL_TEXTURE_2D);
    //     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //     glTexCoordPointer(2, GL_FLOAT, sizeof(DGE::vec2), &p_mesh.uvs[0]);
    // }

    // glDrawElements(GL_TRIANGLES, p_mesh.indices.size(), GL_UNSIGNED_INT, &p_mesh.indices[0]);

    // glDisableClientState(GL_VERTEX_ARRAY);

    // if (!p_mesh.normals.empty())
    // {
    //     glDisableClientState(GL_COLOR_ARRAY);
    //     glDisableClientState(GL_NORMAL_ARRAY);
    // }

    // if (!p_mesh.uvs.empty())
    // {
    //     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    // }
    // glPopMatrix();
    // glActiveTexture(GL_TEXTURE0);
}

void DGERendering::Objects::SceneFormPHG::Draw()
{
    for (auto& mesh_render : m_renderList)
        mesh_render.Render();
}

DGERendering::Objects::GraphObject::GraphObject(
    std::shared_ptr<std::vector<VERLIST>> p_vecVerlist,
    std::string                           p_name,
    bool                                  p_isEditor /*= false*/)
{
    m_name = p_name;
    m_isEditor = p_isEditor;
}

void DGERendering::Objects::GraphObject::Draw()
{
    if (m_vecVerlist == nullptr)
        return;
    glDrawElements(GL_TRIANGLES, m_vecVerlist->size(), GL_UNSIGNED_INT, &(*m_vecVerlist)[0]);
}

#endif
