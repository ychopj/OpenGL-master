#pragma once

#include <string>
#include <vector>
#include <memory>
#include "DGERendering/Objects/ObjectIDAllocator.h"
//#include "DGERendering/Resources/Attributes.h"
#ifdef DMS
#include <Meshing.h>
#endif
#include <DGERendering/MeshRender/DGEMesh.h>
namespace DGERendering::Objects
{
    //using namespace DGERendering::Resources;
    class SceneObject
    {
    public:
        SceneObject();
        SceneObject(std::string p_name, bool p_isEditor = false);

        void setID(ObjectID p_id) { m_id = p_id; }
        void setName(std::string p_name) { m_name = p_name; }

        ObjectID     getID() const { return m_id; }
        bool         IsEditor() { return m_isEditor; }
        virtual void RenderAttribute();
        virtual void Draw() {}
        virtual ~SceneObject() {}

    public:
        std::string               m_name;
        std::vector<SceneObject*> m_children;
        ObjectID                  m_id{k_invalid_object_id};
        bool                      m_isEditor{false};
    };
    using ObjectPtr = std::shared_ptr<SceneObject>;



#ifdef DMS
    class SceneDGEEntity3D : public SceneObject
    {
    public:
        std::shared_ptr<DGE::Entity3D> m_Entity;
        DGE::Mesh                      m_Mesh;
        DGE::Meshing                   myMeshing;

        DGERendering::Core::DGEMeshRender*       m_MeshRender;
        DGERendering::Resources::ATR_MeshRender* m_atr_meshRender;

    public:
        SceneDGEEntity3D();
        SceneDGEEntity3D(std::shared_ptr<DGE::Entity3D> p_entity, bool p_isEditor = false);
        SceneDGEEntity3D(std::shared_ptr<DGE::Entity3D> p_entity, std::string p_name, bool p_isEditor = false);
        ~SceneDGEEntity3D();
        void RenderAttribute() override;
        void Draw() override;
        void setupMesh();
    };

    using namespace DGE;
    class SceneFormPHG : public SceneObject
    {
    public:
        std::vector<SUBMESHPTR> m_smlist;

    public:
        SceneFormPHG();
        SceneFormPHG(std::vector<SUBMESHPTR> p_smlist, std::string p_name, bool p_isEditor = false);
        void RenderAttribute() override {}
        void Draw() override;

    private:
        void drawSm(submesh& p_mesh);
        void setup(submesh& p_mesh);

    private:
        std::vector<DGERendering::MeshRender::DGEMesh> m_renderList;
    };

    class GraphObject : public SceneObject
    {
    public:
        shared_ptr<std::vector<VERLIST>> m_vecVerlist;

    public:
        GraphObject(shared_ptr<std::vector<VERLIST>> p_vecVerlist, string p_name, bool p_isEditor = false);
        // void RenderAttribute() override;
        void Draw() override;
    };

    // class SceneAuxObject : public SceneObject
    // {
    // public:
    //     shared_ptr<VERLIST> m_verlist;

    // public:
    //     SceneAuxObject(shared_ptr<VERLIST> p_verlist, string p_name, bool p_isEditor = false);
    //     ~SceneAuxObject();
    //     void RenderAttribute() override;
    //     void Draw() override;
    // };
#endif

} // namespace DGERendering::Objects