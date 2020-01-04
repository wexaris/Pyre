#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class PYRE_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowClose)
    };

    class PYRE_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(int sizeX, int sizeY) :
            m_SizeX(sizeX), m_SizeY(sizeY)
        {}

        inline int getSizeX() const { return m_SizeX; }
        inline int getSizeY() const { return m_SizeY; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowResize)
        virtual std::string AsString() const override {
            return FMT("WindowResize: {}, {}", m_SizeX, m_SizeY);
        }

    protected:
        int m_SizeX;
        int m_SizeY;
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

    class PYRE_API WindowMoveEvent : public Event {
    public:
        WindowMoveEvent(int posX, int posY) :
            m_PosX(posX), m_PosY(posY)
        {}

        inline int getPosX() const { return m_PosX; }
        inline int getPosY() const { return m_PosY; }

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(WindowMove)
        virtual std::string AsString() const override {
            return FMT("WindowMove: {}, {}", m_PosX, m_PosY);
        }

    protected:
        int m_PosX;
        int m_PosY;
    };

}