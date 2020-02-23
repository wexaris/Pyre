#include "pyrepch.hpp"
#include "Pyre/Renderer/OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Pyre {

    OpenGLContext::OpenGLContext(GLFWwindow* window) 
        : m_Window(window)
    {
        PYRE_CORE_ASSERT(m_Window, "Window handle is null!")

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        PYRE_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    OpenGLContext::~OpenGLContext() {
        
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }

}