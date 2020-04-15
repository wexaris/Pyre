#include "pyrepch.hpp"
#include "Pyre/Renderer/Buffer.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Pyre {

    uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type)
        {
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Int2:   return 4 * 2;
        case ShaderDataType::Int3:   return 4 * 3;
        case ShaderDataType::Int4:   return 4 * 4;
        case ShaderDataType::UInt:   return 4;
        case ShaderDataType::UInt2:  return 4 * 2;
        case ShaderDataType::UInt3:  return 4 * 3;
        case ShaderDataType::UInt4:  return 4 * 4;
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3:   return 4 * 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4 * 4;
        case ShaderDataType::Bool:   return 1;
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid ShaderDataType!");
        return 0;
    }

    uint32_t ShaderDataTypeItemCount(ShaderDataType type) {
        switch (type)
        {
        case ShaderDataType::Int:    return 1;
        case ShaderDataType::Int2:   return 2;
        case ShaderDataType::Int3:   return 3;
        case ShaderDataType::Int4:   return 4;
        case ShaderDataType::UInt:   return 1;
        case ShaderDataType::UInt2:  return 2;
        case ShaderDataType::UInt3:  return 3;
        case ShaderDataType::UInt4:  return 4;
        case ShaderDataType::Float:  return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Mat3:   return 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4;
        case ShaderDataType::Bool:   return 1;
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid ShaderDataType!");
        return 0;
    }

    BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized) :
        Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
    {}

    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
        m_Elements(elements)
    {
        CalcOffsetAndStride();
    }

    void BufferLayout::CalcOffsetAndStride() {
        size_t offset = 0;
        m_Stride = 0;
        for (auto& e : m_Elements) {
            e.Offset = offset;
            offset += e.Size;
            m_Stride += e.Size;
        }
    }

    //////////////////////////////////////
    // VertexBuffer
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size) {
        switch (Renderer::GetAPI()) {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(size);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }
    
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLVertexBuffer>(vertices, size);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

    //////////////////////////////////////
    // IndexBuffer
    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count) {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL: return MakeRef<OpenGLIndexBuffer>(indices, count);
        default: break;
        }
        PYRE_CORE_ASSERT(false, "Invalid Renderer API!");
        return nullptr;
    }

}