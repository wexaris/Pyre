#include "pyrepch.hpp"
#include "Pyre/Renderer/CameraController.hpp"
#include "Pyre/Input/Input.hpp"
#include "Pyre/Input/KeyCodes.hpp"

namespace Pyre {

    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) :
        m_AspecRatio(aspectRatio),
        m_RotationEnable(rotation),
        m_Camera(-m_AspecRatio * m_Zoom, m_AspecRatio * m_Zoom, -m_Zoom, m_Zoom)
    {

    }

    void OrthographicCameraController::OnUpdate(float ts) {
        if (Input::IsKeyPressed(input::KEY_A)) {
            m_Position.x -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y -= sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }
        else if (Input::IsKeyPressed(input::KEY_D)) {
            m_Position.x += cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y += sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }

        if (Input::IsKeyPressed(input::KEY_W)) {
            m_Position.x += -sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y += cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }
        else if (Input::IsKeyPressed(input::KEY_S)) {
            m_Position.x -= -sin(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
            m_Position.y -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * ts;
        }

        if (m_RotationEnable) {
            if (Input::IsKeyPressed(input::KEY_Q)) {
                m_Rotation += m_RotationSpeed * ts;
            }
            else if (Input::IsKeyPressed(input::KEY_E)) {
                m_Rotation -= m_RotationSpeed * ts;
            }

            if (m_Rotation > 180.0f) {
                m_Rotation -= 360.0f;
            }
            else if (m_Rotation <= -180.0f) {
                m_Rotation += 360.0f;
            }

            m_Camera.SetRotation(m_Rotation);
        }

        m_Camera.SetPosition(m_Position);
    }

    void OrthographicCameraController::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrollEvent>(PYRE_BIND_METHOD(OrthographicCameraController::OnMouseScroll));
        dispatcher.Dispatch<WindowResizeEvent>(PYRE_BIND_METHOD(OrthographicCameraController::OnWindowResize));
    }

    bool OrthographicCameraController::OnMouseScroll(MouseScrollEvent& e) {
        m_Zoom -= e.GetYOffset() * 0.25f;
        m_Zoom = std::max(m_Zoom, 0.25f);
        m_Camera.SetProjection(-m_AspecRatio * m_Zoom, m_AspecRatio * m_Zoom, -m_Zoom, m_Zoom);
        return false;
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e) {
        m_AspecRatio = (float)e.GetWidth() / (float)e.GetHeigth();
        m_Camera.SetProjection(-m_AspecRatio * m_Zoom, m_AspecRatio * m_Zoom, -m_Zoom, m_Zoom);
        return false;
    }

}