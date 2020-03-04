#pragma once
#include "Pyre/Renderer/RenderCommand.hpp"

namespace Pyre {

    class Renderer {
    public:
        Renderer() = default;

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        static inline RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
        static inline void SetAPI(RenderAPI::API api) { RenderAPI::SetAPI(api); }
    };

}