#include "pyrepch.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

#include <stb_image/stb_image.h>

namespace Pyre {

    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWError(int error, const char* msg) {
        PYRE_CORE_ERROR("GLFW Error ({}): {}", error, msg);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties) {
        PYRE_PROFILE_FUNCTION();

        m_WindowData.Title = properties.Title;
        m_WindowData.Width = properties.Width;
        m_WindowData.Height = properties.Height;
        m_WindowData.VSyncEnabled = properties.VSync;

        // Initialize GLFW
        if (s_GLFWWindowCount == 0) {
            PYRE_PROFILE_SCOPE("glfwInit()");
            PYRE_CORE_ASSERT(glfwInit(), "Failed to initialize GLFW!");
            glfwSetErrorCallback(GLFWError);
        }

        { // Store video mode properties
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            m_VideoMode = *glfwGetVideoMode(monitor);
            PYRE_CORE_INFO("Video mode: {}x{}@{}Hz (r{}g{}b{})",
                            m_VideoMode.width, m_VideoMode.height, m_VideoMode.refreshRate,
                            m_VideoMode.redBits, m_VideoMode.greenBits, m_VideoMode.blueBits);
        }

        { // Create window
            PYRE_PROFILE_SCOPE("glfwCreateWindow()");

#ifdef PYRE_DEBUG
            if (Renderer::GetAPI() == RenderAPI::API::OpenGL)
                glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_Window = glfwCreateWindow((int)m_WindowData.Width, (int)m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
            m_Context = GraphicsContext::Create(m_Window);
            s_GLFWWindowCount++;

            PYRE_CORE_INFO("Created window: '{}' ({}, {})", m_WindowData.Title, m_WindowData.Width, m_WindowData.Height);
        }

        // Get window position
        glfwGetWindowPos(m_Window, &(m_WindowData.PosX), &(m_WindowData.PosY));

        // Set window properties
        glfwSetWindowUserPointer(m_Window, &m_WindowData);
        SetWindowMode(properties.Mode, properties.Width, properties.Height);
        SetVSyncEnabled(m_WindowData.VSyncEnabled);
        SetIcon(properties.IconPath);

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS: {
                KeyPressEvent event(static_cast<KeyCode>(key));
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleaseEvent event(static_cast<KeyCode>(key));
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressEvent event(static_cast<KeyCode>(key));
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

    void WindowsWindow::Update() {
        PYRE_PROFILE_FUNCTION();

        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetTitle(const std::string& title) {
        PYRE_PROFILE_FUNCTION();

        m_WindowData.Title = title;

        glfwSetWindowTitle(m_Window, title.c_str());
    }

    void WindowsWindow::SetPosition(unsigned int posX, unsigned int posY) {
        PYRE_PROFILE_FUNCTION();

        m_WindowData.PosX = posX;
        m_WindowData.PosY = posY;

        glfwSetWindowPos(m_Window, m_WindowData.PosX, m_WindowData.PosY);
    }

    void WindowsWindow::SetSize(unsigned int width, unsigned int height) {
        PYRE_PROFILE_FUNCTION();

        m_WindowData.Width = width;
        m_WindowData.Height = height;

        glfwSetWindowSize(m_Window, m_WindowData.Width, m_WindowData.Height);
    }

    void WindowsWindow::SetWindowMode(WindowMode mode, unsigned int width, unsigned int height) {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(m_Window, "Cannot set window mode before window creation!");

        if (mode == m_WindowData.Mode) {
            return;
        }

        // If currently windowed, save window position and size
        if (m_WindowData.Mode == WindowMode::Windowed) {
            m_PrevWindowedProps.PosX = m_WindowData.PosX;
            m_PrevWindowedProps.PosY = m_WindowData.PosY;
            m_PrevWindowedProps.Width = m_WindowData.Width;
            m_PrevWindowedProps.Height = m_WindowData.Height;
        }

        GLFWmonitor* monitor = nullptr;

        if (mode == WindowMode::Windowed) {
            if (width == 0 || height == 0) {
                m_WindowData.Width = m_PrevWindowedProps.Width;
                m_WindowData.Height = m_PrevWindowedProps.Height;
            }
            else {
                m_WindowData.Width = width;
                m_WindowData.Height = height;
            }
        }
        else if (mode == WindowMode::Borderless) {
            m_WindowData.Width = m_VideoMode.width;
            m_WindowData.Height = m_VideoMode.height;
            monitor = glfwGetPrimaryMonitor();
        }
        else if (mode == WindowMode::FullScreen) {
            if (width == 0 || height == 0) {
                m_WindowData.Width = m_VideoMode.width;
                m_WindowData.Height = m_VideoMode.height;
            }
            else {
                m_WindowData.Width = width;
                m_WindowData.Height = height;
            }
            monitor = glfwGetPrimaryMonitor();
        }

        m_WindowData.Mode = mode;

        if (m_WindowData.EventCallback) {
            WindowResizeEvent event(m_WindowData.Width, m_WindowData.Height);
            m_WindowData.EventCallback(event);
        }

        glfwSetWindowMonitor(m_Window, monitor, m_WindowData.PosX, m_WindowData.PosY, m_WindowData.Width, m_WindowData.Height, m_VideoMode.refreshRate);
    }

    void WindowsWindow::SetVSyncEnabled(bool enabled) {
        PYRE_PROFILE_FUNCTION();

        m_WindowData.VSyncEnabled = enabled;
        if (m_WindowData.VSyncEnabled) { glfwSwapInterval(1); }
        else { glfwSwapInterval(0); }
    }

    void WindowsWindow::SetIcon(const std::string& path) {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(m_Window, "Cannot set icon before window creation!");

        if (path.empty()) {
            return;
        }

        int width, height, channels;

        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = nullptr;
        {
            PYRE_PROFILE_SCOPE("stbi_load - WindowsWindow::SetIcon(path)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 4);
        }
        PYRE_CORE_ASSERT(data, "Failed to load image: '{}'", path);
        PYRE_CORE_ASSERT(channels == 4, "Window icon must be RGBA!");

        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = data;
        glfwSetWindowIcon(m_Window, 1, &image);

        stbi_image_free(data);
    }

}