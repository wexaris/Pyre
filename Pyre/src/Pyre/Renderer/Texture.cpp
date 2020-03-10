#include "pyrepch.hpp"
#include "Pyre/Renderer/Texture.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Pyre {

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(width, height);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLTexture2D>(path);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}