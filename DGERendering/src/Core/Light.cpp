#include "DGERendering/Core/Light.h"

namespace DGERendering::Core
{
    Light::Light()
    {
        m_color = glm::vec3(1.0f, 1.0f, 1.0f);
        m_position = {1.5f, 3.5f, 3.0f};
        m_strength = 100.0f;
    }

    void Light::Update(Shader* p_shader)
    {
        p_shader->Set("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        p_shader->Set("lightColor", m_color);
        p_shader->Set("lightPos", m_position);
    }

} // namespace DGERendering::Core