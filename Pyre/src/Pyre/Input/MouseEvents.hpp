#pragma once
#include "Pyre/Input/Input.hpp"
#include "Pyre/Input/Event.hpp"

namespace Pyre {

    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return m_MouseButton; }

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Input | Event::Category::MouseButton);

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

        PYRE_GEN_EVENT_TYPE(MouseButtonPress);
        std::string AsString() const override {
            return FMT("MouseButtonPress: {}", m_MouseButton);
        }
    };

    class MouseButtonReleaseEvent : public MouseButtonEvent {
    public:
        MouseButtonReleaseEvent(MouseCode keycode) :
            MouseButtonEvent(keycode)
        {}

        PYRE_GEN_EVENT_TYPE(MouseButtonRelease);
        std::string AsString() const override {
            return FMT("MouseButtonRelease: {}", m_MouseButton);
        }
    };

    class MouseMoveEvent : public Event {
    public:
        MouseMoveEvent(float x, float y) :
            m_MouseX(x), m_MouseY(y)
        {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Input | Event::Category::Mouse);
        PYRE_GEN_EVENT_TYPE(MouseMove);
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

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        PYRE_GEN_EVENT_CATEGORY(Event::Category::Input | Event::Category::Mouse);
        PYRE_GEN_EVENT_TYPE(MouseScroll);
        std::string AsString() const override {
            return FMT("MouseScroll: {}, {}", m_XOffset, m_YOffset);
        }

    protected:
        float m_XOffset;
        float m_YOffset;
    };

}