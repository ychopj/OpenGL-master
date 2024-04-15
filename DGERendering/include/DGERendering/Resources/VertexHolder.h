#pragma once
#include <glm/glm.hpp>
namespace DGERendering::Resources
{
    class VertexHolder
    {
    public:
        VertexHolder() : m_pos(),m_normal(){}

        VertexHolder(const glm::vec3& p_pos, const glm::vec3& p_normal)
            :m_pos(p_pos), m_normal(p_normal)
        {}

        ~VertexHolder() = default;

        glm::vec3 m_pos;
        glm::vec3 m_normal;
        glm::vec2 m_uv;

    };
}
