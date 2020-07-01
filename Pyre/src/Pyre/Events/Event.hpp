#pragma once
#include <functional>

namespace Pyre {

    class Event {
    public:
        enum class Type {
            None = 0,
            KeyPress, KeyRelease, KeyType,
            MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
            WindowClose, WindowMove, WindowResize, WindowFocus, WindowLoseFocus, WindowMaximize, WindowMinimize, WindowRestore,
        };
        enum Category {
            None = 0,
            Input       = BIT(1),
            Keyboard    = BIT(2),
            Mouse       = BIT(3),
            MouseButton = BIT(4),
            Window      = BIT(5)
        };

        virtual ~Event() = default;

        bool Handled = false;

        bool IsCategory(Category category) { return GetCategoryFlags() & category; }
        virtual std::string AsString() const { return GetName(); }

        virtual Event::Type GetEventType() const = 0;
        virtual const char* GetName() const    = 0;
        virtual int GetCategoryFlags() const   = 0;
    };

#define PYRE_GEN_EVENT_TYPE(type) \
    static Event::Type GetStaticType()        { return Event::Type::type; } \
    Event::Type GetEventType() const override { return GetStaticType(); } \
    const char* GetName() const override      { return #type; }
#define PYRE_GEN_EVENT_CATEGORY(category) \
    int GetCategoryFlags() const override     { return category; }

    class EventDispatcher {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {}

        template<typename T, typename Fn, std::enable_if_t<std::is_base_of<Event, T>::value, int> = 0>
        bool Dispatch(const Fn& fn) {
            if (!m_Event.Handled && m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = fn(static_cast<T&>(m_Event));
                return m_Event.Handled;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    static std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.AsString();
    }

}

#define PYRE_BIND_METHOD(fun) (std::bind(&fun, this, std::placeholders::_1))