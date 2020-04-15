#include "pyrepch.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"
#include <glad/glad.h>

namespace Pyre {

    static GLenum ShaderDataTypeOpenGLType(ShaderDataType type) {
        switch (type)
        {
        case Pyre::ShaderDataType::Int:    return GL_INT;
        case Pyre::ShaderDataType::Int2:   return GL_INT;
        case Pyre::ShaderDataType::Int3:   return GL_INT;
        case Pyre::ShaderDataType::Int4:   return GL_INT;
        case Pyre::ShaderDataType::UInt:   return GL_UNSIGNED_INT;
        case Pyre::ShaderDataType::UInt2:  return GL_UNSIGNED_INT;
        case Pyre::ShaderDataType::UInt3:  return GL_UNSIGNED_INT;
        case Pyre::ShaderDataType::UInt4:  return GL_UNSIGNED_INT;
        case Pyre::ShaderDataType::Float:  return GL_FLOAT;
        case Pyre::ShaderDataType::Float2: return GL_FLOAT;
        case Pyre::ShaderDataType::Float3: return GL_FLOAT;
        case Pyre::ShaderDataType::Float4: return GL_FLOAT;
        case Pyre::ShaderDataType::Mat3:   return GL_FLOAT;
        case Pyre::ShaderDataType::Mat4:   return GL_FLOAT;
        case Pyre::ShaderDataType::Bool:   return GL_BOOL;
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        PYRE_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        PYRE_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        PYRE_PROFILE_FUNCTION();

        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        PYRE_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer missing layout!");

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& e : layout) {
            glEnableVertexArrayAttrib(m_RendererID, m_VertexBufferIndex);
            glVertexArrayVertexBuffer(m_RendererID, m_VertexBufferIndex,
                std::static_pointer_cast<OpenGLVertexBuffer>(vertexBuffer)->m_RendererID,
                e.Offset, layout.GetStride());
            glVertexArrayAttribFormat(m_RendererID, m_VertexBufferIndex,
                e.GetItemCount(),
                ShaderDataTypeOpenGLType(e.Type),
                e.Normalized ? GL_TRUE : GL_FALSE,
                0);

            glVertexArrayAttribBinding(m_RendererID, m_VertexBufferIndex, m_VertexBufferIndex);
            m_VertexBufferIndex++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        PYRE_PROFILE_FUNCTION();

        glVertexArrayElementBuffer(m_RendererID,
            std::static_pointer_cast<OpenGLIndexBuffer>(indexBuffer)->m_RendererID);

        m_IndexBuffer = indexBuffer;
    }

}