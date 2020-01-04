#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    Application::Application() :
        m_Window(Window::Create())
    {    
    }

    Application::~Application() {
            
    }

    void Application::Run() {
        while (m_Running) {
            m_Window->OnUpdate();
        }
    }

}