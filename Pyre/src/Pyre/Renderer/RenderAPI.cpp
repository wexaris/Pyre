#include "pyrepch.hpp"
#include "Pyre/Renderer/RenderAPI.hpp"

#include "Platform/OpenGL/OpenGLRenderAPI.hpp"

namespace Pyre {

    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;

    Scope<RenderAPI> RenderAPI::Create() {
        switch (s_API)
        {
        case RenderAPI::API::OpenGL: return MakeScope<OpenGLRenderAPI>();
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}