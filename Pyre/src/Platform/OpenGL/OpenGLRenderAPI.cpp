#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLRenderAPI.hpp"

#include <glad/glad.h>

namespace Pyre {

    void OpenGLRenderAPI::Clear(const glm::vec4& color) {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::DrawElement(const Ref<VertexArray>& vertexArray) {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}