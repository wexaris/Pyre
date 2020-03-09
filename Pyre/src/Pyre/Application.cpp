#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(PYRE_BIND_EVENT_CB(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = MakeRef<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
            
    }

    void Application::Run() {
        while (m_Running) {
            auto time = Time();
            float timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            // Layer updates
            for (auto& layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }

            // ImGui layer render
            m_ImGuiLayer->Begin();
            for (auto& layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(const Ref<Layer>& layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(const Ref<Layer>& overlay) {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowClose));
        dispatcher.Dispatch<WindowMoveEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowMove));
        dispatcher.Dispatch<WindowResizeEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowResize));
        dispatcher.Dispatch<WindowFocusEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowFocus));
        dispatcher.Dispatch<WindowLoseFocusEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowLoseFocus));
        dispatcher.Dispatch<WindowMaximizeEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowMaximize));
        dispatcher.Dispatch<WindowMinimizeEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowMinimize));
        dispatcher.Dispatch<WindowRestoreEvent>(PYRE_BIND_EVENT_CB(Application::_OnWindowRestore));

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