#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class AppTickEvent : public Event {
    public:
        AppTickEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppTick)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppUpdate)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;

        EVENT_ADD_CATEGORY(EventCategoryApplication)
        EVENT_ADD_TYPE(AppRender)
    };

}