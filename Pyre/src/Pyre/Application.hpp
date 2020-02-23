#pragma once
#include "Pyre/Window/Window.hpp"
#include "Pyre/Layers/LayerStack.hpp"
#include "Pyre/Layers/ImGuiLayer.hpp"

namespace Pyre {

    class WindowCloseEvent;
    class WindowMoveEvent;
    class WindowResizeEvent;
    class WindowFocusEvent;
    class WindowLoseFocusEvent;
    class WindowMaximizeEvent;
    class WindowMinimizeEvent;
    class WindowRestoreEvent;

    class Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnWindowClose(WindowCloseEvent&) {}
        virtual void OnWindowMove(WindowMoveEvent&) {}
        virtual void OnWindowResize(WindowResizeEvent&) {}
        virtual void OnWindowFocus(WindowFocusEvent&) {}
        virtual void OnWindowLoseFocus(WindowLoseFocusEvent&) {}
        virtual void OnWindowMaximize(WindowMaximizeEvent&) {}
        virtual void OnWindowMinimize(WindowMinimizeEvent&) {}
        virtual void OnWindowRestore(WindowRestoreEvent&) {}

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow()       { return *m_Window; }

        inline void Shutdown() { m_Running = false; }

    private:
        static Application* s_Instance;

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        LayerStack m_LayerStack;
        bool m_Running = true;

        void OnEvent(Event& e);
        bool _OnWindowClose(WindowCloseEvent& e);
        bool _OnWindowMove(WindowMoveEvent& e);
        bool _OnWindowResize(WindowResizeEvent& e);
        bool _OnWindowFocus(WindowFocusEvent& e);
        bool _OnWindowLoseFocus(WindowLoseFocusEvent& e);
        bool _OnWindowMaximize(WindowMaximizeEvent& e);
        bool _OnWindowMinimize(WindowMinimizeEvent& e);
        bool _OnWindowRestore(WindowRestoreEvent& e);
    };

    // To be defined by the client
    Application* CreateApplication();

}