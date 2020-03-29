#include "pyrepch.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include <filesystem>

namespace Pyre {

    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& baseDirectory, const WindowProperties& windowProperties) {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_BaseDirectory = baseDirectory;

        m_Window = Window::Create(windowProperties);
        m_Window->SetEventCallback(PYRE_BIND_METHOD(Application::OnEvent));

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
        PYRE_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Application::Run() {
        PYRE_PROFILE_FUNCTION();

        while (m_Running) {
            PYRE_PROFILE_SCOPE("Run Loop - Application::Run()");

            Time time;
            float timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if (!m_Minimized) {
                PYRE_PROFILE_SCOPE("LayerStack OnUpdate - Application::Run()");
                for (auto& layer : m_LayerStack) {
                    layer->OnUpdate(timestep);
                }
            }

            {
                PYRE_PROFILE_SCOPE("LayerStack OnImGuiRender - Application::Run()");
                m_ImGuiLayer->Begin();
                for (auto& layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
                m_ImGuiLayer->End();
            }


            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        PYRE_PROFILE_FUNCTION();

        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay) {
        PYRE_PROFILE_FUNCTION();

        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e) {
        PYRE_PROFILE_FUNCTION();

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
        PYRE_PROFILE_FUNCTION();

        m_Running = false;
        return false;
    }

    bool Application::OnWindowMove(WindowMoveEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e) {
        PYRE_PROFILE_FUNCTION();

        if (e.GetWidth() == 0 && e.GetHeigth() == 0) {
            m_Minimized = true;
            return false;
        }
        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeigth());
        return false;
    }

    bool Application::OnWindowFocus(WindowFocusEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    bool Application::OnWindowLoseFocus(WindowLoseFocusEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    bool Application::OnWindowMaximize(WindowMaximizeEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    bool Application::OnWindowMinimize(WindowMinimizeEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    bool Application::OnWindowRestore(WindowRestoreEvent& e) {
        PYRE_PROFILE_FUNCTION();

        return false;
    }

    std::string Application::CorrectFilePath(const std::string& path) {
#ifndef PYRE_DISTRIB
        if (std::filesystem::exists(path)) {
            return path;
        }

        auto newPath = std::filesystem::path(".") / m_BaseDirectory / path;
        if (std::filesystem::exists(newPath)) {
            return newPath.string();
        }

        newPath = std::filesystem::path("../../..") / m_BaseDirectory / path;
        if (std::filesystem::exists(newPath)) {
            return newPath.string();
        }
#endif
        return path;
    }

}