#include "pyrepch.hpp"
#include "Pyre/Windows/WindowsWindow.hpp"

namespace Pyre {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProperties& properties) {
        return new WindowsWindow(properties);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties) {
        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;
        m_Data.VSync = true;

        PYRE_CORE_INFO("Creating window '{}' ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);

        if (!s_GLFWInitialized) {
            int good = glfwInit();
            PYRE_CORE_ASSERT(good, "Failed to initialize GLFW!");

            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(m_Data.VSync);
    }

    WindowsWindow::~WindowsWindow() {
        glfwDestroyWindow(m_Window);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled) {
        m_Data.VSync = enabled;

        if (m_Data.VSync) { glfwSwapInterval(1); } 
        else { glfwSwapInterval(0); }
    }


}