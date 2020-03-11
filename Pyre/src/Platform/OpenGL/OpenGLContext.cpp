#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLContext.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Pyre {

    OpenGLContext::OpenGLContext(GLFWwindow* window) 
        : m_Window(window)
    {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(m_Window, "Window handle is null!")

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        PYRE_CORE_ASSERT(status, "Failed to initialize Glad!");

        PYRE_CORE_INFO("OpenGL Information", glGetString(GL_VENDOR));
        PYRE_CORE_INFO("  Vendor: {}", glGetString(GL_VENDOR));
        PYRE_CORE_INFO("  Renderer: {}", glGetString(GL_RENDERER));
        PYRE_CORE_INFO("  Version: {}", glGetString(GL_VERSION));

#ifdef PYRE_ENABLE_ASSERTS
        int verMajor, verMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &verMajor);
        glGetIntegerv(GL_MINOR_VERSION, &verMinor);

        PYRE_CORE_ASSERT(verMajor > 4 || (verMajor == 4 && verMinor >= 5), "Pyre requires OpenGL 4.5 or newer!");
#endif
    }

    void OpenGLContext::SwapBuffers() {
        PYRE_PROFILE_FUNCTION();

        glfwSwapBuffers(m_Window);
    }

}