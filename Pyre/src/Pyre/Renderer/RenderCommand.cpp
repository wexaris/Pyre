#include "pyrepch.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRenderAPI.hpp"

namespace Pyre {

    RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();

}