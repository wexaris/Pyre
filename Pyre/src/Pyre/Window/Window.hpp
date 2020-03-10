#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    struct WindowProperties {
    public:
        std::string Title;
        unsigned int Width, Height;

        WindowProperties(const std::string& title = "Pyre Engine",
                         unsigned int w = 1280, unsigned int h = 720)
            : Title(title), Width(w), Height(h)
        {}
    };

    // Abstract representation of a desktop window
    class Window {
    public:
        using EventCallbackFun = std::function<void(Event&)>;

        Window() = default;
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFun& cb) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProperties& properties = WindowProperties());
    };

}