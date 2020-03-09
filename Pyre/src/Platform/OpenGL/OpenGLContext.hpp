#pragma once
#include "Pyre/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Pyre {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* window);
        virtual ~OpenGLContext() = default;
        
        void SwapBuffers() override;

    private:
        GLFWwindow* m_Window;
    };

}