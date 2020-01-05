#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

#define BIND_EVENT_CB(fun) (std::bind(&fun, this, std::placeholders::_1))

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
            m_Window->OnUpdate();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }
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
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(Application::OnWindowClose));
        dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_CB(Application::OnWindowMove));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(Application::OnWindowResize));

        for (auto iter = m_LayerStack.rbegin(); iter != m_LayerStack.rend(); iter++) {
            (*iter)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(Event& e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowMove(Event& e) { return true; }

    bool Application::OnWindowResize(Event& e) { return true; }

    bool Application::OnWindowFocus(Event& e) { return true; }

    bool Application::OnWindowLoseFocus(Event& e) { return true; }

    bool Application::OnWindowMaximize(Event& e) { return true; }

    bool Application::OnWindowMinimize(Event& e) { return true; }

    bool Application::OnWindowRestore(Event& e) { return true; }

}