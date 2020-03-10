#pragma once
#include "Pyre/Renderer/RenderAPI.hpp"

namespace Pyre {

    class RenderCommand {
    public:
        RenderCommand() = delete;

        static inline void Init() {
            s_RenderAPI->Init();
        }

        static inline void Clear(const glm::vec4& color) {
            s_RenderAPI->Clear(color);
        }

        static inline void DrawElement(const Ref<VertexArray>& vertexArray) {
            s_RenderAPI->DrawElement(vertexArray);
        }

        static inline void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RenderAPI->SetViewport(x, y, width, height);
        }

    private:
        static Scope<RenderAPI> s_RenderAPI;
    };

}