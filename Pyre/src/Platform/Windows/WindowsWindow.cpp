#include "pyrepch.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

#include <glad/glad.h>

namespace Pyre {

    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWError(int error, const char* msg) {
        PYRE_CORE_ERROR("GLFW Error ({}): {}", error, msg);
    }

    Scope<Window> Window::Create(const WindowProperties& properties) {
        return MakeScope<WindowsWindow>(properties);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties) {
        PYRE_PROFILE_FUNCTION();

        m_Data.Title = properties.Title;
        m_Data.Width = properties.Width;
        m_Data.Height = properties.Height;
        m_Data.VSync = true;

        // Initialize GLFW
        if (s_GLFWWindowCount == 0) {
            PYRE_PROFILE_SCOPE("glfwInit()");
            int good = glfwInit();
            PYRE_CORE_ASSERT(good, "Failed to initialize GLFW!");
            glfwSetErrorCallback(GLFWError);
        }

        { // Create window
            PYRE_PROFILE_SCOPE("glfwCreateWindow()");

#ifdef PYRE_DEBUG
            if (Renderer::GetAPI() == RenderAPI::API::OpenGL)
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

            m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
            s_GLFWWindowCount++;
        }
        m_Context = GraphicsContext::Create(m_Window);

        PYRE_CORE_INFO("Created window: '{}' ({}, {})", m_Data.Title, m_Data.Width, m_Data.Height);

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(m_Data.VSync);
        
        // Get window position
        int x, y;
        glfwGetWindowPos(m_Window, &x, &y);
        m_Data.PosX = x;
        m_Data.PosY = y;

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS: {
                KeyPressEvent event(static_cast<KeyCode>(key), 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleaseEvent event(static_cast<KeyCode>(key));
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressEvent event(static_cast<KeyCode>(key), 1); // TODO: get repeat count
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_CRITICAL("Unrecognised key action from GLFW!");
                break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypeEvent event(static_cast<KeyCode>(keycode));
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS: {
                MouseButtonPressEvent event(static_cast<MouseCode>(button));
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleaseEvent event(static_cast<MouseCode>(button));
                data.EventCallback(event);
                break;
            }
            default:
                PYRE_CORE_CRITICAL("Unrecognised mouse button action from GLFW!");
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
                PYRE_CORE_CRITICAL("Unrecognised window focus state from GLFW!");
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
                PYRE_CORE_CRITICAL("Unrecognised window maximize state from GLFW!");
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
                PYRE_CORE_CRITICAL("Unrecognised window minimize state from GLFW!");
                break;
            }
        });
        
    }

    WindowsWindow::~WindowsWindow() {
        PYRE_PROFILE_FUNCTION();

        glfwDestroyWindow(m_Window);
        s_GLFWWindowCount--;

        if (s_GLFWWindowCount == 0) {
            PYRE_CORE_INFO("Terminating GLFW");
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate() {
        PYRE_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled) {
        PYRE_PROFILE_FUNCTION();

        m_Data.VSync = enabled;

        if (m_Data.VSync) { glfwSwapInterval(1); } 
        else { glfwSwapInterval(0); }
    }


}