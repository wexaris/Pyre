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

    private:
        static Scope<RenderAPI> s_RenderAPI;
    };

}