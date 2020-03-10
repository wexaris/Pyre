#pragma once

namespace Pyre {

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;

        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(void* window);
    };

}