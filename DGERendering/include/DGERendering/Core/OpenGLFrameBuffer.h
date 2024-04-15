#pragma once

namespace DGERendering::Core
{
    class OpenGLFrameBuffer
    {
    public:
        OpenGLFrameBuffer() : m_fbo(0), m_depthId(0) {}

        void CreateBuffers(unsigned int p_width, unsigned int p_height);
        void DeleteBuffers();
        void Bind();
        void Unbind();

        unsigned int GetTexture();

    private:
        unsigned int m_fbo = 0;
        unsigned int m_texId = 0;
        unsigned int m_depthId = 0;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
    };
} // namespace DGERendering::Core