#pragma once
#include "Pyre/Core.hpp"

namespace Pyre {

    class PYRE_API Application {
    public:
        Application();
        virtual ~Application();
        virtual void Run() = 0;
    };

    // To be defined by the client
    Application* CreateApplication();

}