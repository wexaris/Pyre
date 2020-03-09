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
        shader->UploadUniformMat4("uViewProj", s_SceneData->ViewProjMatrix);
        shader->UploadUniformMat4("uTransform", transform);

        vertexArray->Bind();
        RenderCommand::DrawElement(vertexArray);
    }

}