#include "pyrepch.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLRenderAPI.hpp"

namespace Pyre {

    Scope<RenderAPI> RenderCommand::s_RenderAPI = MakeScope<OpenGLRenderAPI>();

}