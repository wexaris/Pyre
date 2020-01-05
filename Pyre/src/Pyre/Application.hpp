#pragma once
#include "Pyre/Core.hpp"
#include "Pyre/Windows/Window.hpp"
#include "Pyre/Layers/LayerStack.hpp"

namespace Pyre {

    class PYRE_API Application {
    public:
        Application();
        virtual ~Application();

        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        virtual void OnEvent(Event& e);
        virtual bool OnWindowClose(Event& e);
        virtual bool OnWindowMove(Event& e);
        virtual bool OnWindowResize(Event& e);
        virtual bool OnWindowFocus(Event& e);
        virtual bool OnWindowLoseFocus(Event& e);
        virtual bool OnWindowMaximize(Event& e);
        virtual bool OnWindowMinimize(Event& e);
        virtual bool OnWindowRestore(Event& e);

    private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;
    };

    // To be defined by the client
    Application* CreateApplication();

}