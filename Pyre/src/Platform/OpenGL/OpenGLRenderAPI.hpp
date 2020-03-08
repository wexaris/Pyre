#pragma once
#include "Pyre/Renderer/RenderAPI.hpp"

namespace Pyre {

    class OpenGLRenderAPI : public RenderAPI {
    public:
        OpenGLRenderAPI() = default;
        virtual ~OpenGLRenderAPI() = default;

        void Clear(const glm::vec4& color) override;

        void DrawElement(const Ref<VertexArray>& vertexArray) override;

    };

}