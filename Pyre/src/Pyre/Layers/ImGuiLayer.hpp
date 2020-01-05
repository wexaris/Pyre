#pragma once
#include "Pyre/Layers/Layer.hpp"
#include "Pyre/Events/KeyEvents.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    class PYRE_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;

    private: 
        float m_Time = 0.f;

        bool OnKeyPress(KeyPressEvent& e);
        bool OnKeyRelease(KeyReleaseEvent& e);
        bool OnKeyType(KeyTypeEvent& e);
        bool OnMouseButtonPress(MouseButtonPressEvent& e);
        bool OnMouseButtonRelease(MouseButtonReleaseEvent& e);
        bool OnMouseMove(MouseMoveEvent& e);
        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };

}