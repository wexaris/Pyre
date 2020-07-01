#pragma once 
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Events/MouseEvents.hpp"
#include "Pyre/Events/WindowEvents.hpp"

namespace Pyre {

    struct OrthographicCameraBounds {
        float Left, Right;
        float Bottom, Top;

        float GetWidth() const { return Right - Left; }
        float GetHeight() const { return Top - Bottom; }
    };

    class OrthographicCameraController {
    public:
        OrthographicCameraController(bool rotation = false);

        void Tick(float dt);
        void OnEvent(Event& e);

        void Resize(uint32_t width, uint32_t height);

        void SetTransform(const glm::vec3& pos, float rot);

        void SetPosition(const glm::vec3& pos);
        const glm::vec3& GetPosition() const   { return m_Position; }
        void SetMovementSpeed(float speed)     { m_MovementSpeed = speed; }
        float GetMovementSpeed() const         { return m_MovementSpeed; }

        void SetRotaton(float rot);
        float GetRotation() const          { return m_Rotation; }
        void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }
        float GetRotationSpeed() const     { return m_RotationSpeed; }

        void SetZoom(float zoom);
        float GetZoom() const          { return m_Zoom; }
        void SetZoomSpeed(float speed) { m_ZoomSpeed = speed; }
        float GetZoomSpeed() const     { return m_ZoomSpeed; }

        const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

        OrthographicCamera& GetCamera()             { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

    private:
        glm::vec3 m_Position = glm::vec3();
        float m_Rotation = 0.0f;
        float m_Zoom = 1.0f;
        bool m_EnableRotation = true;

        float m_MovementSpeed = 1.25f;
        float m_RotationSpeed = 90.0f;
        float m_ZoomSpeed = 0.3f;
        float m_MaxZoom = 10.0f;
        float m_MinZoom = 0.15f;

        float m_AspectRatio;
        OrthographicCameraBounds m_Bounds;
        OrthographicCamera m_Camera;

        void UpdateProjectionMatrix();

        bool OnMouseScroll(MouseScrollEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
    };

}