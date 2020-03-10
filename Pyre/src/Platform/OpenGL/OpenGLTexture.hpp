#pragma once
#include "Pyre/Renderer/Texture.hpp"
#include <glad/glad.h>

namespace Pyre {

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        void Bind(uint32_t slot = 0) const override;

        void SetData(void* data, uint32_t size) override;

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

    private:
        uint32_t m_RendererID;

        std::string path;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;

        GLenum m_InternalFormat;
        GLenum m_DataFormat;
    };

}