#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    Scope<Renderer::SceneData> Renderer::s_SceneData = MakeScope<Renderer::SceneData>();

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera) {
        s_SceneData->ViewProjMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        shader->Bind();
        shader->SetMat4("uViewProj", s_SceneData->ViewProjMatrix);
        shader->SetMat4("uTransform", transform);

        vertexArray->Bind();
        RenderCommand::DrawElement(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::SetViewport(0, 0, width, height);
    }

}