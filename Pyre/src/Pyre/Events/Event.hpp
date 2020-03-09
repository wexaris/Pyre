#pragma once
#include <functional>

namespace Pyre {

    enum class EventType {
        None = 0,
        KeyPress, KeyRelease, KeyType,
        MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
        WindowClose, WindowMove, WindowResize, WindowFocus, WindowLoseFocus, WindowMaximize, WindowMinimize, WindowRestore,
        AppTick, AppUpdate, AppRender
    };

    enum EventCategory {
        None = 0,
        EventCategoryInput       = BIT(1),
        EventCategoryKeyboard    = BIT(2),
        EventCategoryMouse       = BIT(3),
        EventCategoryMouseButton = BIT(4),
        EventCategoryApplication = BIT(5)
    };

    class Event {
    public:
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const    = 0;
        virtual int GetCategoryFlags() const   = 0;
        virtual std::string AsString() const   { return GetName(); }

        inline bool IsCategory(EventCategory category) { return GetCategoryFlags() & category; }
    };

#define EVENT_ADD_TYPE(type) \
    inline static EventType GetStaticType() { return EventType::type; } \
    EventType GetEventType() const override { return GetStaticType(); } \
    const char* GetName() const override    { return #type; }
#define EVENT_ADD_CATEGORY(category) \
    int GetCategoryFlags() const override   { return category; }

    class EventDispatcher {
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {}

        template<typename T, typename Fn, typename = typename std::enable_if<std::is_base_of<Event, T>::value>::type>
        bool Dispatch(const Fn& fn) {
            if (m_Event.Handled) {
                return false;
            }
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = fn(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.AsString();
    }

#define PYRE_BIND_EVENT_CB(fun) (std::bind(&fun, this, std::placeholders::_1))

}