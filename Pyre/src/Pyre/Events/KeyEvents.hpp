#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class PYRE_API KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_ADD_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

    protected:
        int m_KeyCode;

        KeyEvent(int keycode) :
            m_KeyCode(keycode)
        {}
    };

    class PYRE_API KeyPressEvent : public KeyEvent {
    public:
        KeyPressEvent(int keycode, int repeatCount) :
            KeyEvent(keycode), m_RepeatCount(repeatCount)
        {}

        inline int GetRepeatCount() const { return m_RepeatCount; }
        
        EVENT_ADD_TYPE(KeyPress)
        virtual std::string AsString() const override {
            return FMT("KeyPress: {} ({} repeats)", m_KeyCode, m_RepeatCount);
        }

    protected:
        int m_RepeatCount;
    };

    class PYRE_API KeyReleaseEvent : public KeyEvent {
    public:
        KeyReleaseEvent(int keycode) :
            KeyEvent(keycode)
        {}

        EVENT_ADD_TYPE(KeyRelease)
        virtual std::string AsString() const override {
            return FMT("KeyRelease: {}", m_KeyCode);
        }
    };

}