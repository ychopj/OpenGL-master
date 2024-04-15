#include "DGERendering/Core/Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <glad/glad.h>
#include <stdexcept>
#include <string>
#include <iostream>

namespace DGERendering::Core {
    unsigned int Shader::getCompliedShader(unsigned int p_shaderType, const std::string &p_shaderSource) {
        unsigned int shader = glCreateShader(p_shaderType);
        const char *source = p_shaderSource.c_str();
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            int length;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(shader, length, &length, message);
            std::string error_message = "Failed to compile shader: " + std::string(message);
            throw std::runtime_error(error_message);
        }

        return shader;
    }

    bool Shader::Load(const std::string &p_vertexShaderFile, const std::string &p_fragmentShaderFile) {
        std::ifstream is_vertex_shader(p_vertexShaderFile);
        const std::string VERTEX_SHADER_SOURCE(
                (std::istreambuf_iterator<char>(is_vertex_shader)), std::istreambuf_iterator<char>());
        std::ifstream is_fragment_shader(p_fragmentShaderFile);
        const std::string FRAGMENT_SHADER_SOURCE(
                (std::istreambuf_iterator<char>(is_fragment_shader)), std::istreambuf_iterator<char>());

        m_programId = glCreateProgram();

        unsigned int vertex_shader = getCompliedShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE);
        checkCompileErrors(vertex_shader, "VERTEX");
        unsigned int fragment_shader = getCompliedShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE);
        checkCompileErrors(fragment_shader, "FRAGMENT");

        glAttachShader(m_programId, vertex_shader);
        glAttachShader(m_programId, fragment_shader);
        glLinkProgram(m_programId);
        checkCompileErrors(m_programId, "PROGRAM");
        glValidateProgram(m_programId);

        // cache the m_uniforms location
        GLint numm_uniforms;
        glGetProgramiv(m_programId, GL_ACTIVE_UNIFORMS, &numm_uniforms);
        for (GLint i = 0; i < numm_uniforms; i++) {
            const GLsizei bufSize = 32; // maximum name length
            GLchar name[bufSize];       // variable name in GLSL
            GLsizei length;             // name length
            GLint size;                 // size of the variable
            GLenum type;                // type of the variable (float, vec3 or mat4, etc)

            // get the name of this uniform
            glGetActiveUniform(m_programId, (GLuint) i, bufSize, &length, &size, &type, name);

            // cache for later use
            m_uniforms[std::string(name)] = i;
        }


        glDeleteProgram(vertex_shader);
        glDeleteProgram(fragment_shader);
        is_fragment_shader.close();
        is_vertex_shader.close();

        return true;
    }

    void Shader::Use() { glUseProgram(m_programId); }

    void Shader::Unload() { glDeleteProgram(m_programId); }

    void Shader::Set(const std::string &name, int value) {
        Use();
        glUniform1i(m_uniforms[name], value);
    }

    void Shader::Set(const std::string &name, bool value) {
        Set(name, value ? 1 : 0);
    }

    void Shader::Set(const std::string &name, float value) {
        Use();
        glUniform1f(m_uniforms[name], value);
    }

    void Shader::Set(const std::string &name, const glm::vec2 &value) {
        Use();
        glUniform2fv(m_uniforms[name], 1, glm::value_ptr(value));
    }

    void Shader::Set(const std::string &name, const glm::vec3 &value) {
        Use();
        glUniform3fv(m_uniforms[name], 1, glm::value_ptr(value));
    }

    void Shader::Set(const std::string &name, const glm::vec4 &value) {
        Use();
        glUniform4fv(m_uniforms[name], 1, glm::value_ptr(value));
    }

    void Shader::Set(const std::string &name, const glm::mat4 &value) {
        Use();
        glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, glm::value_ptr(value));
    }

    unsigned int Shader::GetAttributeLocation(const std::string &p_name) {
        return glGetAttribLocation(m_programId, p_name.c_str());
    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                          << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }

    }

} // namespace DGERendering::Core
