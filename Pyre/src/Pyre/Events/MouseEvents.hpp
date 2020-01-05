#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class PYRE_API MouseButtonEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    protected:
        int m_KeyCode;

        MouseButtonEvent(int keycode) :
            m_KeyCode(keycode)
        {}
    };

    class PYRE_API MouseButtonPressEvent : public MouseButtonEvent {
    public:
        MouseButtonPressEvent(int keycode) :
            MouseButtonEvent(keycode)
        {}

        EVENT_ADD_TYPE(MouseButtonPress)
        std::string AsString() const override {
            return FMT("MouseButtonPress: {}", m_KeyCode);
        }
    };

    class PYRE_API MouseButtonReleaseEvent : public MouseButtonEvent {
    public:
        MouseButtonReleaseEvent(int keycode) :
            MouseButtonEvent(keycode)
        {}

        EVENT_ADD_TYPE(MouseButtonRelease)
        std::string AsString() const override {
            return FMT("MouseButtonRelease: {}", m_KeyCode);
        }
    };

    class PYRE_API MouseMoveEvent : public Event {
    public:
        MouseMoveEvent(float x, float y) :
            m_MouseX(x), m_MouseY(y)
        {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryMouse)
        EVENT_ADD_TYPE(MouseMove)
        std::string AsString() const override {
            return FMT("MouseMove: {}, {}", m_MouseX, m_MouseY);
        }

    protected:
        float m_MouseX;
        float m_MouseY;
    };

    class PYRE_API MouseScrollEvent : public Event {
    public:
        MouseScrollEvent(float xOffset, float yOffset) :
            m_XOffset(xOffset), m_YOffset(yOffset)
        {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryMouse)
        EVENT_ADD_TYPE(MouseScroll)
        std::string AsString() const override {
            return FMT("MouseScroll: {}, {}", m_XOffset, m_YOffset);
        }

    protected:
        float m_XOffset;
        float m_YOffset;
    };

}