#pragma once
#include "pyrepch.hpp"
#include "Pyre/Core.hpp"
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    struct WindowProperties {
    public:
        std::string Title;
        unsigned int Width, Height;

        WindowProperties(const std::string& title = "Pyre Engine",
                         unsigned int width = 1280,
                         unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {}
    };

    // Abstract representation of a desktop window
    class PYRE_API Window {
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

        static Window* Create(const WindowProperties& properties = WindowProperties());
    };

}