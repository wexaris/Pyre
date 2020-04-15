#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLRenderAPI.hpp"

#include <glad/glad.h>

namespace Pyre {

    void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam) {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:         PYRE_CORE_CRITICAL(message); return;
        case GL_DEBUG_SEVERITY_MEDIUM:       PYRE_CORE_CRITICAL(message); return;
        case GL_DEBUG_SEVERITY_LOW:          PYRE_CORE_CRITICAL(message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: PYRE_CORE_CRITICAL(message); return;
        default: break;
        }

        PYRE_CORE_ASSERT(false, "Unknown OpenGL message severity level!");
    }

    void OpenGLRenderAPI::Init() {
        PYRE_PROFILE_FUNCTION();

#ifdef PYRE_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        glViewport(x, y, width, height);
    }

    void OpenGLRenderAPI::Clear(const glm::vec4& color) {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::DrawElement(const Ref<VertexArray>& vertexArray, uint32_t indexCount) {
        uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}