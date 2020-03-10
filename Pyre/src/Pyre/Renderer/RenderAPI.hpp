#pragma once
#include "Pyre/Renderer/VertexArray.hpp"

#include <glm/glm.hpp>

namespace Pyre {

    class RenderAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1
        };

        RenderAPI() = default;
        virtual ~RenderAPI() = default;

        virtual void Init() = 0;

        virtual void Clear(const glm::vec4& color) = 0;

        virtual void DrawElement(const Ref<VertexArray>& vertexArray) = 0;

        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

        static inline API GetAPI() { return s_API; }
        static inline void SetAPI(API api) { s_API = api; }

    private:
        static API s_API;
    };

}