#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    enum class WindowMode {
        Windowed,
        FullScreen,
        Borderless
    };

    struct WindowProperties {
    public:
        std::string Title = "Pyre Engine";
        unsigned int Width = 1280;
        unsigned int Height = 720;
        WindowMode Mode = WindowMode::Windowed;
        bool VSync = true;
        std::string IconPath;
    };

    // Abstract representation of a desktop window
    class Window {
    public:
        using EventCallbackFun = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void Update() = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual const std::string& GetTitle() const = 0;

        virtual void SetPosition(unsigned int posX, unsigned int posY) = 0;
        virtual unsigned int GetPosX() const = 0;
        virtual unsigned int GetPosY() const = 0;
        virtual void SetSize(unsigned int width, unsigned int height) = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetWindowMode(WindowMode mode, unsigned int width = 0, unsigned int height = 0) = 0;
        virtual WindowMode GetWindowMode() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool GetVSync() const = 0;

        virtual void SetIcon(const std::string& path) = 0;

        virtual void SetEventCallback(const EventCallbackFun& cb) = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
    };

}