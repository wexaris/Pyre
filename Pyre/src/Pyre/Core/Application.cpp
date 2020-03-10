#include "pyrepch.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Renderer/Renderer.hpp"

namespace Pyre {

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(PYRE_BIND_METHOD(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = MakeRef<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
        Renderer::Shutdown();
    }

    void Application::Run() {
        while (m_Running) {
            auto time = Time();
            float timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                for (auto& layer : m_LayerStack) {
                    layer->OnUpdate(timestep);
                }
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
        dispatcher.Dispatch<WindowCloseEvent>(PYRE_BIND_METHOD(Application::OnWindowClose));
        dispatcher.Dispatch<WindowMoveEvent>(PYRE_BIND_METHOD(Application::OnWindowMove));
        dispatcher.Dispatch<WindowResizeEvent>(PYRE_BIND_METHOD(Application::OnWindowResize));
        dispatcher.Dispatch<WindowFocusEvent>(PYRE_BIND_METHOD(Application::OnWindowFocus));
        dispatcher.Dispatch<WindowLoseFocusEvent>(PYRE_BIND_METHOD(Application::OnWindowLoseFocus));
        dispatcher.Dispatch<WindowMaximizeEvent>(PYRE_BIND_METHOD(Application::OnWindowMaximize));
        dispatcher.Dispatch<WindowMinimizeEvent>(PYRE_BIND_METHOD(Application::OnWindowMinimize));
        dispatcher.Dispatch<WindowRestoreEvent>(PYRE_BIND_METHOD(Application::OnWindowRestore));

        for (auto iter = m_LayerStack.rbegin(); iter != m_LayerStack.rend(); iter++) {
            (*iter)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e) {
        Shutdown();
        return false;
    }

    bool Application::OnWindowMove(WindowMoveEvent& e) {
        return false;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        if (e.GetWidth() == 0 && e.GetHeigth() == 0) {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeigth());
        return false;
    }

    bool Application::OnWindowFocus(WindowFocusEvent& e) {
        return false;
    }

    bool Application::OnWindowLoseFocus(WindowLoseFocusEvent& e) {
        return false;
    }

    bool Application::OnWindowMaximize(WindowMaximizeEvent& e) {
        return false;
    }

    bool Application::OnWindowMinimize(WindowMinimizeEvent& e) {
        return false;
    }

    bool Application::OnWindowRestore(WindowRestoreEvent& e) {
        return false;
    }

}