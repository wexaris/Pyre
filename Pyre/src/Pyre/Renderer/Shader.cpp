#include "pyrepch.hpp"
#include "Pyre/Renderer/Shader.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Pyre {

    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}