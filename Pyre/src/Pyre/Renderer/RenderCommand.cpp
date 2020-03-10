#include "pyrepch.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"

namespace Pyre {

    Scope<RenderAPI> RenderCommand::s_RenderAPI = RenderAPI::Create();

}