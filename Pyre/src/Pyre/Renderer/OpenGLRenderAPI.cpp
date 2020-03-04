#include "pyrepch.hpp"
#include "Pyre/Renderer/OpenGLRenderAPI.hpp"

#include <glad/glad.h>

namespace Pyre {

    void OpenGLRenderAPI::Clear(const glm::vec4& color) {
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::DrawElement(const std::shared_ptr<VertexArray>& vertexArray) {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}