#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowClose);
    };

    class WindowMoveEvent : public Event {
    public:
        WindowMoveEvent(int posX, int posY) :
            m_PosX(posX), m_PosY(posY)
        {}

        int GetPosX() const { return m_PosX; }
        int GetPosY() const { return m_PosY; }

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowMove);
        std::string AsString() const override {
            return FMT("WindowMove: {}, {}", m_PosX, m_PosY);
        }

    protected:
        int m_PosX;
        int m_PosY;
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int width, int height) :
            m_Width(width), m_Height(height)
        {}

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowResize);
        std::string AsString() const override {
            return FMT("WindowResize: {}, {}", m_Width, m_Height);
        }

    protected:
        int m_Width;
        int m_Height;
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowFocus);
    };

    class WindowLoseFocusEvent : public Event {
    public:
        WindowLoseFocusEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowLoseFocus);
    };

    class WindowMaximizeEvent : public Event {
    public:
        WindowMaximizeEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowMaximize);
    };

    class WindowMinimizeEvent : public Event {
    public:
        WindowMinimizeEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowMinimize);
    };

    class WindowRestoreEvent : public Event {
    public:
        WindowRestoreEvent() = default;

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Window);
        PYRE_GEN_EVENT_TYPE(WindowRestore);
    };

}