#include "pyrepch.hpp"
#include "Pyre/Core/Application.hpp"
#include "Pyre/Renderer/CameraController.hpp"
#include "Pyre/Input/Input.hpp"

#include <imgui.h>

namespace Pyre {

    enum class CameraInput : uint16_t {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        RotateClockwise,
        RotateCounterClockwise,
    };

    OrthographicCameraController::OrthographicCameraController(bool enableRotation) :
        m_AspectRatio((float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight()),
        m_EnableRotation(enableRotation),
        m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom)
    {
        Input::Remap(CameraInput::MoveLeft, Key::A);
        Input::Remap(CameraInput::MoveRight, Key::D);
        Input::Remap(CameraInput::MoveUp, Key::W);
        Input::Remap(CameraInput::MoveDown, Key::S);
        Input::Remap(CameraInput::RotateClockwise, Key::E);
        Input::Remap(CameraInput::RotateCounterClockwise, Key::Q);
    }

    void OrthographicCameraController::Tick(float dt) {
        PYRE_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        if (!io.WantCaptureKeyboard) {

            if (Input::IsInputPressed(CameraInput::MoveLeft)) {
                m_Position.x -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
                m_Position.y -= sin(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
            }
            else if (Input::IsInputPressed(CameraInput::MoveRight)) {
                m_Position.x += cos(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
                m_Position.y += sin(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
            }

            if (Input::IsInputPressed(CameraInput::MoveUp)) {
                m_Position.x += -sin(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
                m_Position.y += cos(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
            }
            else if (Input::IsInputPressed(CameraInput::MoveDown)) {
                m_Position.x -= -sin(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
                m_Position.y -= cos(glm::radians(m_Rotation)) * m_MovementSpeed * dt;
            }

            if (m_EnableRotation) {
                if (Input::IsInputPressed(CameraInput::RotateClockwise)) {
                    m_Rotation += m_RotationSpeed * dt;
                }
                else if (Input::IsInputPressed(CameraInput::RotateCounterClockwise)) {
                    m_Rotation -= m_RotationSpeed * dt;
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

        m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
        UpdateProjectionMatrix();
        return false;
    }

}