#pragma once
#include "Pyre/Core.hpp"
#include "Pyre/Windows/Window.hpp"

namespace Pyre {

    class PYRE_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined by the client
    Application* CreateApplication();

}