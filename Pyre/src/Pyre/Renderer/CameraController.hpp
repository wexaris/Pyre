#pragma once 
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void Tick(float dt);
        void OnEvent(Event& e);

        const glm::vec3& GetPosition() const   { return m_Position; }
        void SetPosition(const glm::vec3& pos) { m_Position = pos; }
        float GetMovementSpeed() const         { return m_MovementSpeed; }
        void SetMovementSpeed(float speed)     { m_MovementSpeed = speed; }

        float GetRotation() const          { return m_Rotation; }
        void SetRotaton(float rot)         { m_Rotation = rot; }
        float GetRotationSpeed() const     { return m_RotationSpeed; }
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

        float GetZoom() const          { return m_Zoom; }
        void SetZoom(float zoom);
        float GetZoomSpeed() const     { return m_ZoomSpeed; }
        void SetZoomSpeed(float speed) { m_ZoomSpeed = speed; }

        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        float m_AspectRatio;

        glm::vec3 m_Position = glm::vec3();
        float m_Rotation = 0.0f;
        float m_Zoom = 1.0f;
        bool m_EnableRotation = true;

        float m_MovementSpeed = 1.25f;
        float m_RotationSpeed = 90.0f;
        float m_ZoomSpeed = 0.3f;
        float m_MaxZoom = 10.0f;
        float m_MinZoom = 0.15f;

        OrthographicCamera m_Camera;

        void UpdateProjectionMatrix() { m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom); }

        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };

}