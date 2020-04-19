#include "pyrepch.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include <filesystem>
#include <thread>

namespace Pyre {

    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationProperties& properties) :
        m_BaseDirectory(properties.BaseDirectory),
        m_MinTickRate(properties.MinTickRate),
        m_MaxSubsteps(properties.MaxSubsteps)
    {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = Window::Create(properties.WindowProperties);
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

        const float maxSubstepDelta = 1.0f / m_MinTickRate;
        m_LastFrameTime = Time();

        while (m_Running) {
            PYRE_PROFILE_SCOPE("Game Loop");

            // Update frame delta time
            Time time;
            m_DeltaTime = time.AsSecondsf() - m_LastFrameTime.AsSecondsf();
            m_LastFrameTime = time;

            // Calculate the required number of substeps
            unsigned int substepCount = (int)ceil(m_DeltaTime / maxSubstepDelta);
            if (substepCount > m_MaxSubsteps) { substepCount = m_MaxSubsteps; } // Upper bound
            
            // Calculate the delta time for each substep
            double substepDelta = m_DeltaTime / substepCount;
            if (substepDelta > maxSubstepDelta) { substepDelta = maxSubstepDelta; } // Lower bound

            {
                PYRE_PROFILE_SCOPE("Logic Loop");
                for (unsigned int i = 0; i < substepCount; i++) {
                    for (auto& layer : m_LayerStack) {
                        layer->Tick((float)substepDelta);
                    }
                }
            }

            {
                PYRE_PROFILE_SCOPE("Draw Loop");
                for (auto& layer : m_LayerStack) {
                    layer->Draw();
                }
            }
            {
                PYRE_PROFILE_SCOPE("ImGuiDraw Loop");
                m_ImGuiLayer->Begin();
                for (auto& layer : m_LayerStack) {
                    layer->ImGuiDraw();
                }
                m_ImGuiLayer->End();
            }

            // Poll events and swap buffers
            m_Window->Update();
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

        for (auto iter = m_LayerStack.rbegin(); !e.Handled && iter != m_LayerStack.rend(); iter++) {
            (*iter)->OnEvent(e);
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
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
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