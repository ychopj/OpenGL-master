#ifdef DMS
#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <ShapesInclude.h>
#include <DGERendering/Resources/Material.h>

namespace DGERendering::Core
{
    class DGEMeshRender
    {
    public:
        DGERendering::Resources::Material* m_material;
        DGE::Mesh*                         m_mesh;
        // bool        cast_shadow = true;

    public:
        DGEMeshRender(DGERendering::Resources::Material* _material, DGE::Mesh* _mesh)
            : m_material(_material), m_mesh(_mesh)
        {
        }
        ~DGEMeshRender()
        {
            if (m_material == nullptr)
                return;
            delete m_material;
            m_material = nullptr;
        }

        void SetMaterial(
            DGERendering::Resources::EMaterialType type = DGERendering::Resources::MODEL_MATERIAL)
        {
            delete m_material;
            m_material = DGERendering::Resources::MaterialManager::CreateMaterialByType(type);
        }

        void Draw();
    };

} // namespace DGERendering::Core
#endif