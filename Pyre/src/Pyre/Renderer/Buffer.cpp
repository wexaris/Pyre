#include "pyrepch.hpp"
#include "Pyre/Renderer/Buffer.hpp"

#include "Pyre/Renderer/Renderer.hpp"
#include "Pyre/Renderer/OpenGLBuffer.hpp"

namespace Pyre {

    BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized) :
        Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {}

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
        m_Elements(elements)
    {
        CalcOffsetAndStride();
    }

    void BufferLayout::CalcOffsetAndStride() {
        uint32_t offset = 0;
        m_Stride = 0;
        for (auto& e : m_Elements) {
            e.Offset = offset;
            offset += e.Size;
            m_Stride += e.Size;
        }
    }

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid RendererAPI!");
        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:   PYRE_CORE_ASSERT(false, "No renderer API selected!"); break;
        case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        default: break;
        }
        return nullptr;
    }

}