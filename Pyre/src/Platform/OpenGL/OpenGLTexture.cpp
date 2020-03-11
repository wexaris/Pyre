#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLTexture.hpp"

#include <stb_image/stb_image.h>
#include <glad/glad.h>

namespace Pyre {

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) :
        m_Width(width),
        m_Height(height),
        m_InternalFormat(GL_RGBA8),
        m_DataFormat(GL_RGBA)
    {
        PYRE_PROFILE_FUNCTION();

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) :
        path(path)
    {
        PYRE_PROFILE_FUNCTION();

        int width, height, channels;

        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        {
            PYRE_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        PYRE_CORE_ASSERT(data, "Failed to load image: '{}'", path);

        m_Width = width;
        m_Height = height;

        if (channels == 4) {
            m_InternalFormat = GL_RGBA8;
            m_DataFormat = GL_RGBA;
        }
        else if (channels == 3) {
            m_InternalFormat = GL_RGB8;
            m_DataFormat = GL_RGB;
        }

        PYRE_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Unsupported image format: '{}'", path);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    void OpenGLTexture2D::SetData(void* data, uint32_t size) {
        PYRE_PROFILE_FUNCTION();

        uint32_t bpp = (m_DataFormat == GL_RGBA) ? 4 : 3;
        PYRE_CORE_ASSERT(size == (m_Width * m_Height * bpp), "Image data doesn't match texture properties!");
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        PYRE_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        PYRE_PROFILE_FUNCTION();

        glBindTextureUnit(0, m_RendererID);
    }

}