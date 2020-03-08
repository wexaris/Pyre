#pragma once

#include <glm/glm.hpp>

namespace Pyre {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera() = default;

        const glm::vec3& GetPostition() const { return m_Position; }
        float GetRotation() const { return m_Rotation; }

        void SetPosition(const glm::vec3& pos) { m_Position = pos; RecalcViewMatrix(); }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalcViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrixCache; }

    private:
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjMatrixCache;

        glm::vec3 m_Position = glm::vec3();
        float m_Rotation = 0.f;

        void RecalcViewMatrix();
    };

}