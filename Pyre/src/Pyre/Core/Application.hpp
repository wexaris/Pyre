#pragma once
#include "Pyre/Core/Window.hpp"
#include "Pyre/Core/LayerStack.hpp"
#include "Pyre/Core/Time.hpp"
#include "Pyre/ImGui/ImGuiLayer.hpp"
#include "Pyre/Events/WindowEvents.hpp"

int main(int argc, char* argv[]);

namespace Pyre {

    class Application {
    public:
        Application(const std::string& baseDirectory, const WindowProperties& windowProperties = WindowProperties());
        virtual ~Application();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        std::string CorrectFilePath(const std::string& path);

        static Application& Get() { return *s_Instance; }
        Window& GetWindow()       { return *m_Window; }

    private:
        friend int ::main(int argc, char* argv[]);

        static Application* s_Instance;
        std::string m_BaseDirectory;

        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        Time m_LastFrameTime;
        int m_MaxTickCount = 60;
        bool m_Running = true;

        void Run();
        float GetDeltaTime() {
            Time time;
            float dt = time - m_LastFrameTime;
            m_LastFrameTime = time;
            return dt;
        }

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