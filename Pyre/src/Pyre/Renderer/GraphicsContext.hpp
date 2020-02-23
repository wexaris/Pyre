#pragma once

namespace Pyre {

    class GraphicsContext {
    public:
        GraphicsContext() = default;
        virtual ~GraphicsContext() = default;

        virtual void SwapBuffers() = 0;
    };

}