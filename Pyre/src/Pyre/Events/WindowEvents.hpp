#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowClose)
    };

    class WindowMoveEvent : public Event {
    public:
        WindowMoveEvent(int posX, int posY) :
            m_PosX(posX), m_PosY(posY)
        {}

        int GetPosX() const { return m_PosX; }
        int GetPosY() const { return m_PosY; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMove)
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
        int GetHeigth() const { return m_Height; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowResize)
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

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowFocus)
    };

    class WindowLoseFocusEvent : public Event {
    public:
        WindowLoseFocusEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowLoseFocus)
    };

    class WindowMaximizeEvent : public Event {
    public:
        WindowMaximizeEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMaximize)
    };

    class WindowMinimizeEvent : public Event {
    public:
        WindowMinimizeEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMinimize)
    };

    class WindowRestoreEvent : public Event {
    public:
        WindowRestoreEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowRestore)
    };

}