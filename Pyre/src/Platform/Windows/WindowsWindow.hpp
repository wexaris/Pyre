#pragma once
#include "Pyre/Core/Window.hpp"
#include "Pyre/Renderer/GraphicsContext.hpp"

#include <GLFW/glfw3.h>

namespace Pyre {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProperties& properties);
        ~WindowsWindow();

        void OnUpdate() override;

        void SetIcon(const std::string& path) override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFun& cb) override { m_Data.EventCallback = cb; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override { return m_Data.VSync; }

        void* GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData {
            std::string Title;
            unsigned int PosX = 0,  PosY = 0;
            unsigned int Width = 0, Height = 0;
            bool VSync = true;
            EventCallbackFun EventCallback;
        };

        WindowData m_Data;
    };

}