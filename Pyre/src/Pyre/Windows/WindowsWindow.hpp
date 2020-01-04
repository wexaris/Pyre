#pragma once
#include "Pyre/Windows/Window.hpp"
#include <GLFW/glfw3.h>

namespace Pyre {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProperties& properties);
        ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override  { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFun& cb) override { m_Data.EventCallback = cb; }
        void SetVSync(bool enabled) override;
        inline bool IsVSync() const override { return m_Data.VSync; }

    private:
        GLFWwindow* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFun EventCallback;
        };

        WindowData m_Data;
    };

}