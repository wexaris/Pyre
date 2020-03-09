#include "pyrepch.hpp"
#include "Pyre/Renderer/Texture.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLTexture.hpp"

namespace Pyre {

    Ref<Texture2D> Texture2D::Create(const std::string& path) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}