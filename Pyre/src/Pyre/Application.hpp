#pragma once
#include "Pyre/Core.hpp"
#include "Pyre/Windows/Window.hpp"
#include "Pyre/Layers/LayerStack.hpp"

namespace Pyre {

    class WindowCloseEvent;
    class WindowMoveEvent;
    class WindowResizeEvent;
    class WindowFocusEvent;
    class WindowLoseFocusEvent;
    class WindowMaximizeEvent;
    class WindowMinimizeEvent;
    class WindowRestoreEvent;

    class PYRE_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnWindowClose(WindowCloseEvent& e) {}
        virtual void OnWindowMove(WindowMoveEvent& e) {}
        virtual void OnWindowResize(WindowResizeEvent& e) {}
        virtual void OnWindowFocus(WindowFocusEvent& e) {}
        virtual void OnWindowLoseFocus(WindowLoseFocusEvent& e) {}
        virtual void OnWindowMaximize(WindowMaximizeEvent& e) {}
        virtual void OnWindowMinimize(WindowMinimizeEvent& e) {}
        virtual void OnWindowRestore(WindowRestoreEvent& e) {}

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow()       { return *m_Window; }

        inline void Shutdown() { m_Running = false; }

    private:
        static Application* s_Instance;

        std::unique_ptr<Window> m_Window;
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