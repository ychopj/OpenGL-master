#pragma once

#include "DGERendering/Core/Shader.h"
#include <glm/glm.hpp>

namespace DGERendering::Core
{
    class Light
    {
    public:
        Light();
        ~Light() {}

        void Update(Shader* p_shader);

    private:
        glm::vec3 m_position;
        glm::vec3 m_color;
        float     m_strength;
    };

} // namespace DGERendering::Core