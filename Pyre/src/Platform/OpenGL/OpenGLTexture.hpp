#pragma once
#include "Pyre/Renderer/Texture.hpp"

namespace Pyre {

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D();

        void Bind(uint32_t slot = 0) const override;

        uint32_t GetWidth() const override { return m_Width; }
        uint32_t GetHeight() const override { return m_Height; }

    private:
        uint32_t m_RendererID;

        std::string path;
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
    };

}