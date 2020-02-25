#pragma once

namespace Pyre {

    enum class ShaderDataType {
        None = 0,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Bool
    };

    uint32_t ShaderDataTypeSize(ShaderDataType type);
    uint32_t ShaderDataTypeItemCount(ShaderDataType type);

    struct BufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() = default;
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

        inline uint32_t GetItemCount() const { return ShaderDataTypeItemCount(Type); }
    };

    class BufferLayout {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements);

        inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
        inline uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end()   { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const   { return m_Elements.end(); }
        std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
        std::vector<BufferElement>::reverse_iterator rend()   { return m_Elements.rend(); }
        std::vector<BufferElement>::const_reverse_iterator rbegin() const { return m_Elements.rbegin(); }
        std::vector<BufferElement>::const_reverse_iterator rend() const   { return m_Elements.rend(); }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;

        void CalcOffsetAndStride();
    };


    //////////////////////////////////////
    // VertexBuffer
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);

    protected:
        VertexBuffer() = default;
    };


    //////////////////////////////////////
    // IndexBuffer
    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t count);

    protected:
        IndexBuffer() = default;
    };

}