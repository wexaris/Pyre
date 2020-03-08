#pragma once
#include "Pyre/Renderer/RenderCommand.hpp"
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Renderer/Shader.hpp"

namespace Pyre {

    class Renderer {
    public:
        Renderer() = delete;

        static void BeginScene(OrthographicCamera* camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
        static inline void SetAPI(RenderAPI::API api) { RenderAPI::SetAPI(api); }

    private:
        static OrthographicCamera* s_Camera;
    };

}