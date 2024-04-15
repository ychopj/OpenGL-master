#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

namespace DGERendering::Core {
    class Shader {
    private:
        unsigned int m_programId;
        std::unordered_map<std::string, unsigned int> m_uniforms;

        unsigned int getCompliedShader(unsigned int p_shaderType, const std::string &p_shaderSource);

        void checkCompileErrors(unsigned int shader, std::string type);

    public:
        Shader() = default;

        bool Load(const std::string &p_vertexShaderFile, const std::string &p_fragmentShaderFile);

        void Use();

        void Unload();

        unsigned int GetProgramId() { return m_programId; }

        void Set(const std::string &name, int value);

        void Set(const std::string &name, bool value);

        void Set(const std::string &name, float value);

        void Set(const std::string &name, const glm::vec2 &value);

        void Set(const std::string &name, const glm::vec3 &value);

        void Set(const std::string &name, const glm::vec4 &value);

        void Set(const std::string &name, const glm::mat4 &value);

        unsigned int GetAttributeLocation(const std::string &p_name);
    };
} // namespace DGERendering::Core