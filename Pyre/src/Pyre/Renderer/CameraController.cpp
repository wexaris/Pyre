#include "pyrepch.hpp"
#include "Pyre/Renderer/CameraController.hpp"
#include "Pyre/Input/Input.hpp"
#include "Pyre/Input/KeyCodes.hpp"

namespace Pyre {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool enableRotation) :
        m_AspectRatio(aspectRatio),
        m_EnableRotation(enableRotation),
        m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom)
    {
    }

    void OrthographicCameraController::OnUpdate(float ts) {
        PYRE_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(PYRE_KEY_A)) {
            m_Position.x -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y -= sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }
        else if (Input::IsKeyPressed(PYRE_KEY_D)) {
            m_Position.x += cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y += sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }

        if (Input::IsKeyPressed(PYRE_KEY_W)) {
            m_Position.x += -sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y += cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }
        else if (Input::IsKeyPressed(PYRE_KEY_S)) {
            m_Position.x -= -sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }

        if (m_EnableRotation) {
            if (Input::IsKeyPressed(PYRE_KEY_Q)) {
                m_Rotation += m_RotationSpeed * ts;
            }
            else if (Input::IsKeyPressed(PYRE_KEY_E)) {
                m_Rotation -= m_RotationSpeed * ts;
            }

            if (m_Rotation > 180.0f) {
                m_Rotation -= 360.0f;
            }
            else if (m_Rotation <= -180.0f) {
                m_Rotation += 360.0f;
            }

        }

        m_Camera.SetTransform(m_Position, m_Rotation);
    }

    void OrthographicCameraController::SetZoom(float zoom) {
        PYRE_CORE_ASSERT(zoom > 0.0f, "Zoom level has to be higher than 0.0f!");
        float diff = zoom / m_Zoom;
        m_MovementSpeed *= diff;
        m_Zoom = zoom;
        UpdateProjectionMatrix();
    }

    void OrthographicCameraController::OnEvent(Event& e) {
        PYRE_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(PYRE_BIND_METHOD(OrthographicCameraController::OnMouseScroll));
        dispatcher.Dispatch<WindowResizeEvent>(PYRE_BIND_METHOD(OrthographicCameraController::OnWindowResize));
    }

    bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e) {
        PYRE_PROFILE_FUNCTION();

        float zoom = m_Zoom - e.GetYOffset() * m_ZoomSpeed;
        zoom = std::clamp(zoom, m_MinZoom, m_MaxZoom);
        SetZoom(zoom);
        return false;
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e) {
        PYRE_PROFILE_FUNCTION();

        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeigth();
        UpdateProjectionMatrix();
        return false;
    }

}