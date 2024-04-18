#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
namespace DGERendering::Core
{
    class Shader
    {
    private:
        unsigned int m_programId;

        std::unordered_map<std::string, unsigned int> m_uniforms;
        unsigned int getCompliedShader(unsigned int p_shaderType, const std::string& p_shaderSource);

    public:
        Shader() = default;
        bool Load(const std::string& p_vertexShaderFile, const std::string& p_fragmentShaderFile);

        void         Use();
        void         Unload();
        unsigned int GetProgramId() { return m_programId; }

        void Set(const std::string& p_name, int p_value);

        void Set(const std::string& p_name, bool p_value);

        void Set(const std::string& p_name, float p_value);

        void Set(const std::string& p_name, const glm::vec2& p_value);

        void Set(const std::string& p_name, const glm::vec3& p_value);

        void Set(const std::string& p_name, const glm::vec4& p_value);

        void Set(const std::string& p_name, const glm::mat4& p_value);

        unsigned int GetAttributeLocation(const std::string& p_name);

    private:
        void checkCompileErrors(unsigned int p_shader, std::string p_type);
    };
} // namespace DGERendering::Core