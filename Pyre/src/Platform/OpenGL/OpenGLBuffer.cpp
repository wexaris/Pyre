#pragma once
#include "Platform/OpenGL/OpenGLBuffer.hpp"

#include <glad/glad.h>

namespace Pyre {

    //////////////////////////////////////
    // VertexBuffer
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(vertices, "Vertex pointer is null!");

        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        PYRE_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const {
        PYRE_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const {
        PYRE_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    //////////////////////////////////////
    // IndexBuffer
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) :
        m_Count(count)
    {
        PYRE_PROFILE_FUNCTION();

        PYRE_CORE_ASSERT(indices, "Index pointer is null!");

        glCreateBuffers(1, &m_RendererID);
        glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        PYRE_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const {
        PYRE_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const {
        PYRE_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}