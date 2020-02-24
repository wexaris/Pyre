#pragma once

namespace Pyre {

    enum class RendererAPI {
        None   = 0,
        OpenGL = 1
    };

    class Renderer {
    public:
        Renderer() = default;

        static inline RendererAPI GetAPI() { return s_RendererAPI; }
        static inline RendererAPI SetAPI(RendererAPI api) { s_RendererAPI = api; }

    private:
        static RendererAPI s_RendererAPI;
    };

}