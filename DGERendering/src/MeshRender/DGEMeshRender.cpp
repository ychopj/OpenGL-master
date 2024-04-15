#ifdef DMS
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "DGERendering/Core/DGEMeshRender.h"

void DGERendering::Core::DGEMeshRender::Draw()
{
    if (m_material->IsValid() && m_mesh != nullptr)
    {
        // DGE::submesh sm = m_mesh->m_submesh;
        // glDisable(GL_CULL_FACE);
        // glPushMatrix();
        // glScalef(1.0, 1.0, 1.0);

        // if (sm.positions.empty())
        //     return;

        // glEnableClientState(GL_VERTEX_ARRAY);
        // glVertexPointer(3, GL_FLOAT, sizeof(DGE::vec3), &sm.positions[0]);

        // if (!sm.normals.empty())
        // {
        //     glEnableClientState(GL_NORMAL_ARRAY);
        //     glNormalPointer(GL_FLOAT, sizeof(DGE::vec3), &sm.normals[0]);
        //     glEnableClientState(GL_COLOR_ARRAY);
        //     glColorPointer(3, GL_FLOAT, sizeof(DGE::vec3), &sm.colors[0]);
        // }

        // if (!sm.uvs.empty())
        // {
        //     glEnable(GL_TEXTURE_2D);
        //     // if (!EditorSettings::UsePolygonMode)
        //     m_material->Setup();

        //     glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        //     glTexCoordPointer(2, GL_FLOAT, sizeof(DGE::vec2), &sm.uvs[0]);
        // }

        // glDrawElements(GL_TRIANGLES, sm.indices.size(), GL_UNSIGNED_INT, &sm.indices[0]);

        // glDisableClientState(GL_VERTEX_ARRAY);

        // if (!sm.normals.empty())
        // {
        //     glDisableClientState(GL_COLOR_ARRAY);
        //     glDisableClientState(GL_NORMAL_ARRAY);
        // }

        // if (!sm.uvs.empty())
        // {
        //     glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        // }
        // glPopMatrix();
        // glActiveTexture(GL_TEXTURE0);
    }
}
#endif