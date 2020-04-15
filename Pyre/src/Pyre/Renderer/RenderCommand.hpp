#pragma once
#include "Pyre/Renderer/RenderAPI.hpp"

namespace Pyre {

    class RenderCommand {
    public:
        RenderCommand() = delete;

        static void Init() {
            s_RenderAPI->Init();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RenderAPI->SetViewport(x, y, width, height);
        }

        static void Clear(const glm::vec4& color) {
            s_RenderAPI->Clear(color);
        }

        static void DrawElement(const Ref<VertexArray>& vertexArray, const uint32_t indexCount = 0) {
            s_RenderAPI->DrawElement(vertexArray, indexCount);
        }

    private:
        static Scope<RenderAPI> s_RenderAPI;
    };

}