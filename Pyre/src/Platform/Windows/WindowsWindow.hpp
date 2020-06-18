#pragma once
#include "Pyre/Core/Window.hpp"
#include "Pyre/Renderer/GraphicsContext.hpp"

#include <GLFW/glfw3.h>

namespace Pyre {

    struct WindowData {
        std::string Title = "Pyre Engine";
        int PosX = 0, PosY = 0;
        int Width = 0, Height = 0;
        WindowMode Mode = WindowMode::Windowed;
        bool VSyncEnabled = true;

        Window::EventCallbackFun EventCallback;
    };

    struct WindowedModeProperties {
        int PosX = 0, PosY = 0;
        int Width = 1280, Height = 720;
    };

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProperties& properties);
        ~WindowsWindow();

        void Update() override;

        virtual void SetTitle(const std::string& title) override;
        virtual const std::string& GetTitle() const override { return m_WindowData.Title; }

        void SetPosition(unsigned int posX, unsigned int posY) override;
        unsigned int GetPosX() const override { return m_WindowData.PosX; }
        unsigned int GetPosY() const override { return m_WindowData.PosY; }
        void SetSize(unsigned int width, unsigned int height) override;
        unsigned int GetWidth() const override  { return m_WindowData.Width; }
        unsigned int GetHeight() const override { return m_WindowData.Height; }

        void SetWindowMode(WindowMode mode, unsigned int width = 0, unsigned int height = 0) override;
        WindowMode GetWindowMode() const override { return m_WindowData.Mode; }

        void SetVSyncEnabled(bool enabled) override;
        bool GetVSyncEnabled() const override { return m_WindowData.VSyncEnabled; }

        void SetIcon(const std::string& path) override;

        void SetEventCallback(const EventCallbackFun& cb) override { m_WindowData.EventCallback = cb; }

        void* GetNativeWindow() const { return m_Window; }

    private:
        GLFWwindow* m_Window;
        GLFWvidmode m_VideoMode;
        Scope<GraphicsContext> m_Context;
        WindowData m_WindowData;
        WindowedModeProperties m_PrevWindowedProps;
    };

}