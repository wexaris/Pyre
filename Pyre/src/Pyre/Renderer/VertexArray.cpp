#include "pyrepch.hpp"
#include "Pyre/Renderer/VertexArray.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Pyre {

    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLVertexArray>();
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}