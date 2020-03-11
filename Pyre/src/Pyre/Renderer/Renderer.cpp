#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Renderer/Renderer2D.hpp"

namespace Pyre {

    Scope<Renderer::SceneData> Renderer::s_SceneData = MakeScope<Renderer::SceneData>();

    void Renderer::Init() {
        PYRE_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown() {
        PYRE_PROFILE_FUNCTION();

        Renderer2D::Shutdown();
    }

    void Renderer::BeginScene(OrthographicCamera& camera) {
        PYRE_PROFILE_FUNCTION();

        s_SceneData->ViewProjMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
        PYRE_PROFILE_FUNCTION();
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
        PYRE_PROFILE_FUNCTION();

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