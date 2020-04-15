#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer2D.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"
#include "Pyre/Renderer/VertexArray.hpp"
#include "Pyre/Renderer/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pyre {

    struct QuadVertex {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexID;
        float TilingFactor;
    };

    struct RenderData {
        static const uint32_t MaxQuads = 1000;
        static const uint32_t MaxVerts = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32;

        Ref<VertexArray> QuadVA;
        Ref<VertexBuffer> QuadVB;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture; 

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBeg = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 should be occupied by the white texture

        glm::vec4 QuadVertexPositions[4];
    };
    static RenderData s_Data;


    void Renderer2D::Init() {
        PYRE_PROFILE_FUNCTION();

        s_Data.QuadVA = VertexArray::Create();

        s_Data.QuadVB = VertexBuffer::Create(s_Data.MaxVerts * sizeof(QuadVertex));
        s_Data.QuadVB->SetLayout({
            { ShaderDataType::Float3, "aPosition" },
            { ShaderDataType::Float4, "aColor" },
            { ShaderDataType::Float2, "aTexCoord" },
            { ShaderDataType::Float,  "aTexID" },
            { ShaderDataType::Float,  "aTilingFactor" },
         });
        s_Data.QuadVA->AddVertexBuffer(s_Data.QuadVB);

        s_Data.QuadVertexBufferBeg = new QuadVertex[s_Data.MaxVerts];

        {
            uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

            uint32_t offset = 0;
            for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
                quadIndices[i + 0] = offset + 0;
                quadIndices[i + 1] = offset + 1;
                quadIndices[i + 2] = offset + 2;
                quadIndices[i + 3] = offset + 2;
                quadIndices[i + 4] = offset + 3;
                quadIndices[i + 5] = offset + 0;
                offset += 4;
            }

            Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
            s_Data.QuadVA->SetIndexBuffer(quadIB);

            delete[] quadIndices;
        }

        uint32_t white = 0xffffffff;
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        s_Data.WhiteTexture->SetData(&white, sizeof(uint32_t));

        int samplers[s_Data.MaxTextureSlots];
        for (int i = 0; i < s_Data.MaxTextureSlots; i++) {
            samplers[i] = i;
        }

        s_Data.TextureShader = Shader::Create("../../../Pyre/assets/shaders/Texture.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetIntArray("uTextures", samplers, s_Data.MaxTextureSlots);

        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

    void Renderer2D::Shutdown() {
        PYRE_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        PYRE_PROFILE_FUNCTION();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBeg;
        s_Data.QuadIndexCount = 0;

        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene() {
        PYRE_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBeg;
        s_Data.QuadVB->SetData(s_Data.QuadVertexBufferBeg, dataSize);

        Flush();
    }

    void Renderer2D::Flush() {
        PYRE_PROFILE_FUNCTION();

        // Bind textures
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++) {
            s_Data.TextureSlots[i]->Bind(i);
        }

        s_Data.QuadVA->Bind();
        RenderCommand::DrawElement(s_Data.QuadVA, s_Data.QuadIndexCount);
    }

    // translation * rotation * size
    glm::mat4 MakeTransformationMatrix(const glm::vec3& pos, float rot, const glm::vec2& size) {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
        if (rot != 0) {
            // Rotation is expensive
            transform = glm::rotate(transform, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        transform = glm::scale(transform, { size.x, size.y, 1.0f });
        return transform;
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const glm::vec4& color) {
        PYRE_PROFILE_FUNCTION();

        constexpr float textureIndex = 0;    // 0 - white texture
        constexpr float tilingFactor = 1.0f;

        // Handle transformations
        glm::mat4 transform = MakeTransformationMatrix(pos, rot, size);

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, texture, 1.0f, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint) {
        DrawQuad(pos, rot, size, texture, 1.0f, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, texture, tilingFactor, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tint) {
        PYRE_PROFILE_FUNCTION();

        // Handle textures
        float textureIndex = 0;
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++) {
            if (s_Data.TextureSlots[i] == texture) {
                textureIndex = (float)i;
                break;
            }
        }
        if (textureIndex == 0) {
            textureIndex = (float)s_Data.TextureSlotIndex;
            s_Data.TextureSlots[s_Data.TextureSlotIndex++] = texture;
        }

        // Handle transformations
        glm::mat4 transform = MakeTransformationMatrix(pos, rot, size);

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[0];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[1];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[2];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[3];
        s_Data.QuadVertexBufferPtr->Color = tint;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr->TexID = textureIndex;
        s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;
    }

}