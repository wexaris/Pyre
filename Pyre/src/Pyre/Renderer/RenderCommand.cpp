#include "pyrepch.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"
#include "Pyre/Renderer/OpenGLRenderAPI.hpp"

namespace Pyre {

    RenderAPI* RenderCommand::s_RenderAPI = new OpenGLRenderAPI();

}