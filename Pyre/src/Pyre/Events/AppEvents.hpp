#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class PYRE_API AppTickEvent : public Event {
    public:
        AppTickEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppTick)
    };

    class PYRE_API AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppUpdate)
    };

    class PYRE_API AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppRender)
    };

}