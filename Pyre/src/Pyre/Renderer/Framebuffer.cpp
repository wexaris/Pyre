#include "pyrepch.hpp"
#include "Pyre/Renderer/Framebuffer.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLFramebuffer.hpp"

namespace Pyre {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferProperties& properties) {
        switch (Renderer::GetAPI()) {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLFramebuffer>(properties);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}