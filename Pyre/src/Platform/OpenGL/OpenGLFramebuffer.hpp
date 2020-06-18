#pragma once
#include "Pyre/Renderer/Framebuffer.hpp"

namespace Pyre {

    class OpenGLFramebuffer : public Framebuffer {
    public:
        OpenGLFramebuffer(const FramebufferProperties& properties);
        virtual ~OpenGLFramebuffer();

        void Bind() const override;
        void Unbind() const override;

        void Resize(uint32_t width, uint32_t height) override;

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
        const FramebufferProperties& GetProperties() const override { return m_Properties; }

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FramebufferProperties m_Properties;

        void Reconstruct();
    };

}