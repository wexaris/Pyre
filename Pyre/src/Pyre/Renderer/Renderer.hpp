#pragma once
#include "Pyre/Renderer/RenderCommand.hpp"
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Renderer/Shader.hpp"

namespace Pyre {

    class Renderer {
    public:
        static void Init();

        static void BeginScene(OrthographicCamera* camera);
        static void EndScene();

        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));

        static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
        static inline void SetAPI(RenderAPI::API api) { RenderAPI::SetAPI(api); }

    private:
        static OrthographicCamera* s_Camera;

        Renderer() = delete;
    };

}