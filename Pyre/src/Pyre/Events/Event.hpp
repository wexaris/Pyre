#pragma once
#include "Pyre/Core.hpp"

namespace Pyre {

    enum class EventType {
        None = 0,
        KeyPress, KeyRelease,
        MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll,
        WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
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

    class PYRE_API Event {

        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const    = 0;
        virtual int GetCategoryFlags() const   = 0;
        virtual std::string AsString() const   { return GetName(); }

        inline bool IsCategory(EventCategory category) { return GetCategoryFlags() & category; }

    private:
        bool m_handled = false;
    };

#define EVENT_ADD_TYPE(type) \
    inline static EventType GetStaticType()         { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override    { return #type; }
#define EVENT_ADD_CATEGORY(category) \
    virtual int GetCategoryFlags() const override   { return category; }

    class EventDispatcher {

        template<typename T>
        using EventFun = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event)
        {}

        template<typename T, typename = typename std::enable_if<std::is_base_of<Event, T>::value>::type>
        bool Dispatch(EventFun<T> fun) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_handled = fun(*(T*)&m_Event);
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

}