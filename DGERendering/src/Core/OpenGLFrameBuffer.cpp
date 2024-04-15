#include <glad/glad.h>
#include "DGERendering/Core/OpenGLFrameBuffer.h"

void DGERendering::Core::OpenGLFrameBuffer::CreateBuffers(unsigned int p_width, unsigned int p_height)
{
    m_width = p_width;
    m_height = p_height;
    if (m_fbo)
    {
        DeleteBuffers();
    }
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p_width, p_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texId, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &m_depthId);
    glBindTexture(GL_TEXTURE_2D, m_depthId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, p_width, p_height);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_depthId, 0);

    GLenum buffers[4] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(m_texId, buffers);

    Unbind();
}

void DGERendering::Core::OpenGLFrameBuffer::DeleteBuffers()
{
    if (m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
        glDeleteTextures(1, &m_texId);
        glDeleteTextures(1, &m_depthId);
        m_fbo = 0;
        m_texId = 0;
        m_depthId = 0;
    }
}

void DGERendering::Core::OpenGLFrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DGERendering::Core::OpenGLFrameBuffer::Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

unsigned int DGERendering::Core::OpenGLFrameBuffer::GetTexture() { return m_texId; }
