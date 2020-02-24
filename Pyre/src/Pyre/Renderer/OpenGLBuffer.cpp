#pragma once
#include "Pyre/Renderer/OpenGLBuffer.hpp"

#include <glad/glad.h>

namespace Pyre {

    //////////////////////////////////////
    // VertexBuffer
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        PYRE_CORE_ASSERT(vertices, "Vertex pointer is null!");

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    //////////////////////////////////////
    // IndexBuffer
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) :
        m_Count(count)
    {
        PYRE_CORE_ASSERT(indices, "Index pointer is null!");

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}