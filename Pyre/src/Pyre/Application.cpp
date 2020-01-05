#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Events/WindowEvents.hpp"

#include <glad/glad.h>

namespace Pyre {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_CB(Application::OnEvent));
    }

    Application::~Application() {
            
    }

    void Application::Run() {
        while (m_Running) {
            glClearColor(0, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(Application::_OnWindowClose));
        dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_CB(Application::_OnWindowMove));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(Application::_OnWindowResize));
        dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_CB(Application::_OnWindowFocus));
        dispatcher.Dispatch<WindowLoseFocusEvent>(BIND_EVENT_CB(Application::_OnWindowLoseFocus));
        dispatcher.Dispatch<WindowMaximizeEvent>(BIND_EVENT_CB(Application::_OnWindowMaximize));
        dispatcher.Dispatch<WindowMinimizeEvent>(BIND_EVENT_CB(Application::_OnWindowMinimize));
        dispatcher.Dispatch<WindowRestoreEvent>(BIND_EVENT_CB(Application::_OnWindowRestore));

        for (auto iter = m_LayerStack.rbegin(); iter != m_LayerStack.rend(); iter++) {
            (*iter)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::_OnWindowClose(WindowCloseEvent& e) {
        Shutdown();
        OnWindowClose(e);
        return false;
    }

    bool Application::_OnWindowMove(WindowMoveEvent& e) {
        OnWindowMove(e);
        return false;
    }

    bool Application::_OnWindowResize(WindowResizeEvent& e) {
        OnWindowResize(e);
        return false;
    }

    bool Application::_OnWindowFocus(WindowFocusEvent& e) {
        OnWindowFocus(e);
        return false;
    }

    bool Application::_OnWindowLoseFocus(WindowLoseFocusEvent& e) {
        OnWindowLoseFocus(e);
        return false;
    }

    bool Application::_OnWindowMaximize(WindowMaximizeEvent& e) {
        OnWindowMaximize(e);
        return false;
    }

    bool Application::_OnWindowMinimize(WindowMinimizeEvent& e) {
        OnWindowMinimize(e);
        return false;
    }

    bool Application::_OnWindowRestore(WindowRestoreEvent& e) {
        OnWindowRestore(e);
        return false;
    }

}