#pragma once
#include "Pyre/Renderer/Buffer.hpp"

namespace Pyre {

    //////////////////////////////////////
    // VertexBuffer
    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        void SetData(const void* data, uint32_t size) override;

        const BufferLayout& GetLayout() const override { return m_Layout; }
        void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

    protected:
        friend class OpenGLVertexArray;

        uint32_t m_RendererID = 0;
        BufferLayout m_Layout;
    };


    //////////////////////////////////////
    // IndexBuffer
    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetCount() const override { return m_Count; }

    protected:
        friend class OpenGLVertexArray;

        uint32_t m_RendererID = 0;
        uint32_t m_Count;
    };

}