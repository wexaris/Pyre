#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class PYRE_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowClose)
    };

    class PYRE_API WindowMoveEvent : public Event {
    public:
        WindowMoveEvent(int posX, int posY) :
            m_PosX(posX), m_PosY(posY)
        {}

        inline int GetPosX() const { return m_PosX; }
        inline int GetPosY() const { return m_PosY; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMove)
        std::string AsString() const override {
            return FMT("WindowMove: {}, {}", m_PosX, m_PosY);
        }

    protected:
        int m_PosX;
        int m_PosY;
    };

    class PYRE_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int width, int height) :
            m_Width(width), m_Height(height)
        {}

        inline int GetWidth() const { return m_Width; }
        inline int GetHeigth() const { return m_Height; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowResize)
        std::string AsString() const override {
            return FMT("WindowResize: {}, {}", m_Width, m_Height);
        }

    protected:
        int m_Width;
        int m_Height;
    };

    class PYRE_API WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowFocus)
    };

    class PYRE_API WindowLoseFocusEvent : public Event {
    public:
        WindowLoseFocusEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowLoseFocus)
    };

    class PYRE_API WindowMaximizeEvent : public Event {
    public:
        WindowMaximizeEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMaximize)
    };

    class PYRE_API WindowMinimizeEvent : public Event {
    public:
        WindowMinimizeEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMinimize)
    };

    class PYRE_API WindowRestoreEvent : public Event {
    public:
        WindowRestoreEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowRestore)
    };

}