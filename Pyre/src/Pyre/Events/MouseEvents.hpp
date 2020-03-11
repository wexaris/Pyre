#pragma once
#include "Pyre/Events/Event.hpp"
#include "Pyre/Input/Input.hpp"

namespace Pyre {

    class MouseButtonEvent : public Event {
    public:
        inline MouseCode GetMouseButton() const { return m_MouseButton; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

    protected:
        MouseCode m_MouseButton;

        MouseButtonEvent(MouseCode button) :
            m_MouseButton(button)
        {}
    };

    class MouseButtonPressEvent : public MouseButtonEvent {
    public:
        MouseButtonPressEvent(MouseCode keycode) :
            MouseButtonEvent(keycode)
        {}

        EVENT_ADD_TYPE(MouseButtonPress)
        std::string AsString() const override {
            return FMT("MouseButtonPress: {}", m_MouseButton);
        }
    };

    class MouseButtonReleaseEvent : public MouseButtonEvent {
    public:
        MouseButtonReleaseEvent(MouseCode keycode) :
            MouseButtonEvent(keycode)
        {}

        EVENT_ADD_TYPE(MouseButtonRelease)
        std::string AsString() const override {
            return FMT("MouseButtonRelease: {}", m_MouseButton);
        }
    };

    class MouseMoveEvent : public Event {
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

    class MouseScrollEvent : public Event {
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