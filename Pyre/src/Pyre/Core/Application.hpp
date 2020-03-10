#pragma once
#include "Pyre/Core/Window.hpp"
#include "Pyre/Core/LayerStack.hpp"
#include "Pyre/Core/Time.hpp"
#include "Pyre/ImGui/ImGuiLayer.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    class Application {
    public:
        Application();
        virtual ~Application() = default;

        void Run();

        void PushLayer(const Ref<Layer>& layer);
        void PushOverlay(const Ref<Layer>& overlay);

        static inline Application& Get() { return *s_Instance; }
        inline Window& GetWindow()       { return *m_Window; }

        inline void Shutdown() { m_Running = false; }

    protected:
        bool OnWindowClose(WindowCloseEvent&);
        bool OnWindowMove(WindowMoveEvent&);
        bool OnWindowResize(WindowResizeEvent&);
        bool OnWindowFocus(WindowFocusEvent&);
        bool OnWindowLoseFocus(WindowLoseFocusEvent&);
        bool OnWindowMaximize(WindowMaximizeEvent&);
        bool OnWindowMinimize(WindowMinimizeEvent&);
        bool OnWindowRestore(WindowRestoreEvent&);

    private:
        static Application* s_Instance;

        Scope<Window> m_Window;
        Ref<ImGuiLayer> m_ImGuiLayer;
        LayerStack m_LayerStack;
        Time m_LastFrameTime;
        bool m_Running = true;
        bool m_Minimized = false;

        void OnEvent(Event& e);
    };

    // To be defined by the client
    Application* CreateApplication();

}