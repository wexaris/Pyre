#pragma once
#include "Pyre/Events/Event.hpp"
#include "Pyre/Input/Input.hpp"

namespace Pyre {

    class KeyEvent : public Event {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    protected:
        KeyCode m_KeyCode;

        KeyEvent(KeyCode keycode) :
            m_KeyCode(keycode)
        {}
    };

    class KeyPressEvent : public KeyEvent {
    public:
        KeyPressEvent(KeyCode keycode, int repeatCount) :
            KeyEvent(keycode), m_RepeatCount(repeatCount)
        {}

        inline int GetRepeatCount() const { return m_RepeatCount; }
        
        EVENT_ADD_TYPE(KeyPress)
        std::string AsString() const override {
            return FMT("KeyPress: {} ({} repeats)", m_KeyCode, m_RepeatCount);
        }

    protected:
        int m_RepeatCount;
    };

    class KeyReleaseEvent : public KeyEvent {
    public:
        KeyReleaseEvent(KeyCode keycode) :
            KeyEvent(keycode)
        {}

        EVENT_ADD_TYPE(KeyRelease)
        std::string AsString() const override {
            return FMT("KeyRelease: {}", m_KeyCode);
        }
    };

    class KeyTypeEvent : public KeyEvent {
    public:
        KeyTypeEvent(KeyCode keycode) :
            KeyEvent(keycode)
        {}

        EVENT_ADD_TYPE(KeyType)
            std::string AsString() const override {
            return FMT("KeyType: {}", m_KeyCode);
        }
    };

}