#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Log.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    Application::Application() {
        WindowResizeEvent e(1280, 720);
        PYRE_TRACE(e);
    }

    Application::~Application() {
            
    }

}