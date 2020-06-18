#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLFramebuffer.hpp"

#include <glad/glad.h>

namespace Pyre {

    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProperties& properties) :
        m_Properties(properties)
    {
        PYRE_PROFILE_FUNCTION();

        Reconstruct();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer() {
        PYRE_PROFILE_FUNCTION();

        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFramebuffer::Bind() const {
        PYRE_PROFILE_FUNCTION();

        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Properties.Width, m_Properties.Height);
    }

    void OpenGLFramebuffer::Unbind() const {
        PYRE_PROFILE_FUNCTION();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height) {
        PYRE_PROFILE_FUNCTION();

        m_Properties.Width = width;
        m_Properties.Height = height;
        Reconstruct();
    }

    void OpenGLFramebuffer::Reconstruct() {
        PYRE_PROFILE_FUNCTION();

        if (m_RendererID) {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glCreateFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

        // Create color texture
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
        glTextureStorage2D(m_ColorAttachment, 1, GL_RGBA8, m_Properties.Width, m_Properties.Height);
        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_ColorAttachment, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureSubImage2D(m_ColorAttachment, 0, 0, 0, m_Properties.Width, m_Properties.Height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        
        // Create depth texture
        glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
        glTextureStorage2D(m_DepthAttachment, 1, GL_DEPTH24_STENCIL8, m_Properties.Width, m_Properties.Height);
        glTextureSubImage2D(m_DepthAttachment, 0, 0, 0, m_Properties.Width, m_Properties.Height, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

        // Validate framebuffer
        PYRE_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Failed to create framebuffer!");
        
        // Unbind framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}