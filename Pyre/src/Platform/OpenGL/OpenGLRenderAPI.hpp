#pragma once
#include "Pyre/Renderer/RenderAPI.hpp"

namespace Pyre {

    class OpenGLRenderAPI : public RenderAPI {
    public:
        OpenGLRenderAPI() = default;
        virtual ~OpenGLRenderAPI() = default;

        void Init() override;

        void Clear(const glm::vec4& color) override;

        void DrawElement(const Ref<VertexArray>& vertexArray) override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

    };

}