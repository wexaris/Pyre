#pragma once
#include "Pyre/Core/Window.hpp"
#include "Pyre/Core/LayerStack.hpp"
#include "Pyre/Core/Time.hpp"
#include "Pyre/ImGui/ImGuiLayer.hpp"
#include "Pyre/Events/WindowEvents.hpp"

int main(int argc, char* argv[]);

namespace Pyre {

    struct ApplicationProperties {
        std::string BaseDirectory;
        WindowProperties WindowProperties;
        unsigned int MaxTickRate = 60;
    };

    class Application {
    public:
        Application(const ApplicationProperties& properties);
        virtual ~Application();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        std::string CorrectFilePath(const std::string& path);

        static Application& Get() { return *s_Instance; }
        Window& GetWindow() { return *m_Window; }

        int GetFPS() const          { return (int)(1.0 / m_DeltaTime); }
        double GetDeltaTime() const { return m_DeltaTime; }

    private:
        friend int ::main(int argc, char* argv[]);

        static Application* s_Instance;
        const std::string m_BaseDirectory;
        const unsigned int m_MaxTickRate = 60;
        bool m_Running = true;

        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        Time m_LastFrameTime;
        double m_DeltaTime;

        void Run();

        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent&);
        bool OnWindowMove(WindowMoveEvent&);
        bool OnWindowResize(WindowResizeEvent&);
        bool OnWindowFocus(WindowFocusEvent&);
        bool OnWindowLoseFocus(WindowLoseFocusEvent&);
        bool OnWindowMaximize(WindowMaximizeEvent&);
        bool OnWindowMinimize(WindowMinimizeEvent&);
        bool OnWindowRestore(WindowRestoreEvent&);
    };

    // To be defined by the client
    Application* CreateApplication();

}