#include "pyrepch.hpp"
#include "Pyre/Windows/WindowsWindow.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"
#include <glad/glad.h>

namespace Pyre {

    static bool s_GLFWInitialized = false;

    static void GLFWError(int error, const char* msg) {
        PYRE_CORE_ERROR("GLFW Error ({}): {}", error, msg);
    }

    Window* Window::Create(const WindowProperties& properties) {
        return new WindowsWindow(properties);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties) {
        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;
        m_Data.VSync = true;

        PYRE_CORE_INFO("Creating window '{}' ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);

        // Initialize GLFW
        if (!s_GLFWInitialized) {
            int good = glfwInit();
            PYRE_CORE_ASSERT(good, "Failed to initialize GLFW!");
            glfwSetErrorCallback(GLFWError);
            s_GLFWInitialized = true;
        }

        // Create GLFW window
        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(m_Data.VSync);

        // Get window position
        int x, y;
        glfwGetWindowPos(m_Window, &x, &y);
        m_Data.PosX = x;
        m_Data.PosY = y;

        // Initialize Glad
        int good = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        PYRE_CORE_ASSERT(good, "Failed to initialize Glad!")

        // Add GLFW callbacks
        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS: {
                KeyPressEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleaseEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressEvent event(key, 1); // TODO: get repeat count
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_FATAL("Unrecognised key action from GLFW!");
                break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypeEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS: {
                MouseButtonPressEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleaseEvent event(button);
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_FATAL("Unrecognised mouse button action from GLFW!");
                break;
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseMoveEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.PosX = x;
            data.PosY = y;
            WindowMoveEvent event(x, y);
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (focused)
            {
            case GLFW_TRUE: {
                WindowFocusEvent event;
                data.EventCallback(event);
                break;
            }
            case GLFW_FALSE: {
                WindowLoseFocusEvent event;
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_FATAL("Unrecognised window focus state from GLFW!");
                break;
            }
        });

        glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (maximized)
            {
            case GLFW_TRUE: {
                WindowMaximizeEvent event;
                data.EventCallback(event);
                break;
            }
            case GLFW_FALSE: {
                WindowRestoreEvent event;
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_FATAL("Unrecognised window maximize state from GLFW!");
                break;
            }
        });

        glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int minimized) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (minimized)
            {
            case GLFW_TRUE: {
                WindowMinimizeEvent event;
                data.EventCallback(event);
                break;
            }
            case GLFW_FALSE: {
                WindowRestoreEvent event;
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_FATAL("Unrecognised window minimize state from GLFW!");
                break;
            }
        });
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