#include "pyrepch.hpp"
#include "Pyre/Renderer/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Pyre {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) :
        m_ProjMatrix(glm::ortho(left, right, bottom, top, -1.f, 1.0f)),
        m_ViewMatrix(1.f)
    {
        m_ViewProjMatrixCache = m_ProjMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
        m_ProjMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.0f);
        m_ViewProjMatrixCache = m_ProjMatrix * m_ViewMatrix;
    }

    void OrthographicCamera::RecalcViewMatrix() {
        glm::mat4 transform =
            glm::translate(glm::mat4(1.f), m_Position) *
            glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjMatrixCache = m_ProjMatrix * m_ViewMatrix;
    }

}