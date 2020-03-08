#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    OrthographicCamera* Renderer::s_Camera;

    void Renderer::BeginScene(OrthographicCamera* camera) {
        s_Camera = camera;
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
        shader->Bind();
        shader->UploadUniformMat4("uViewProj", s_Camera->GetViewProjectionMatrix());

        vertexArray->Bind();
        RenderCommand::DrawElement(vertexArray);
    }

}