#pragma once

#include <glm/glm.hpp>

namespace Pyre {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);
        void SetTransform(const glm::vec3& position, float rotation) { RecalcViewMatrix(position, rotation); }

        const glm::mat4& GetProjectionMatrix() const     { return m_ProjMatrix; }
        const glm::mat4& GetViewMatrix() const           { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrixCache; }

    private:
        glm::mat4 m_ProjMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjMatrixCache;

        void RecalcViewMatrix(const glm::vec3& position, float rotation);
    };

}