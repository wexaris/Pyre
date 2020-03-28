#pragma once 
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(float timestep);
        void OnEvent(Event& e);

        float GetZoom() const           { return m_Zoom; }
        void SetZoom(float zoom)        { m_Zoom = zoom; }
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        float m_AspecRatio;
        float m_Zoom = 1.f;
        OrthographicCamera m_Camera;

        bool m_RotationEnable;
        glm::vec3 m_Position = glm::vec3();
        float m_Rotation = 0.f;
        float m_MovementSpeed;
        float m_RotationSpeed = 60.f;

        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };

}