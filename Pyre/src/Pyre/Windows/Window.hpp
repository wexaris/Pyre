#pragma once
#include "Pyre/Core.hpp"
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    struct WindowProperties {
    public:
        std::string Title;
        unsigned int PosX, PosY;
        unsigned int Width, Height;

        WindowProperties(const std::string& title = "Pyre Engine",
                         unsigned int x = 0, unsigned int y = 0,
                         unsigned int w = 1280, unsigned int h = 720)
            : Title(title), PosX(x), PosY(y), Width(w), Height(h)
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