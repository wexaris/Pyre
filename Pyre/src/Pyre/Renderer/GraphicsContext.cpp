#include "pyrepch.hpp"
#include "Pyre/Renderer/GraphicsContext.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLContext.hpp"

namespace Pyre {

    Scope<GraphicsContext> GraphicsContext::Create(void* window) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeScope<OpenGLContext>((GLFWwindow*)window);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}