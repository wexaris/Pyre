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
        std::string Title;
        unsigned int Width, Height;
        WindowMode Mode;
        std::string IconPath;

        WindowProperties(const std::string& title = "Pyre Engine",
                         unsigned int width = 1280,
                         unsigned int height = 720,
                         WindowMode mode = WindowMode::Windowed,
                         const std::string& iconPath = "")
            : Title(title), Width(width), Height(height), Mode(mode), IconPath(iconPath)
        {}
    };

    // Abstract representation of a desktop window
    class Window {
    public:
        using EventCallbackFun = std::function<void(Event&)>;

        Window() = default;
        virtual ~Window() = default;

        virtual void Update() = 0;

        virtual void Resize(unsigned int width, unsigned int height) = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetWindowMode(WindowMode mode, unsigned int width = 0, unsigned int height = 0) = 0;
        virtual WindowMode GetWindowMode() const = 0;

        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void SetIcon(const std::string& path) = 0;

        virtual void SetEventCallback(const EventCallbackFun& cb) = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
    };

}