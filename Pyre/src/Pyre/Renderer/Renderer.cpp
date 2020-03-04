#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    void Renderer::BeginScene() {

    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
        RenderCommand::DrawElement(vertexArray);
    }

}