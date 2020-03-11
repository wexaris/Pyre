#include "pyrepch.hpp"
#include "Pyre/Renderer/Renderer2D.hpp"
#include "Pyre/Renderer/RenderCommand.hpp"
#include "Pyre/Renderer/VertexArray.hpp"
#include "Pyre/Renderer/Shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Pyre {

    struct PrimitiveData {
        Ref<VertexArray> QuadVA;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };
    static PrimitiveData* s_Data;

    void Renderer2D::Init() {
        PYRE_PROFILE_FUNCTION();

        s_Data = new PrimitiveData();
        s_Data->QuadVA = Pyre::VertexArray::Create();

        float square_verts[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        uint32_t square_indices[6] = { 0, 1 , 2, 2, 3, 0 };

        Pyre::BufferLayout square_layout = {
            { Pyre::ShaderDataType::Float3, "aPosistion" },
            { Pyre::ShaderDataType::Float2, "aTexCoord" },
        };

        Pyre::Ref<Pyre::VertexBuffer> square_vb;
        square_vb = Pyre::VertexBuffer::Create(square_verts, sizeof(square_verts));
        square_vb->SetLayout(square_layout);
        s_Data->QuadVA->AddVertexBuffer(square_vb);

        Pyre::Ref<Pyre::IndexBuffer> square_ib;
        square_ib = Pyre::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
        s_Data->QuadVA->SetIndexBuffer(square_ib);

        uint32_t white = 0xffffffff;
        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        s_Data->WhiteTexture->SetData(&white, sizeof(uint32_t));

        s_Data->TextureShader = Pyre::Shader::Create("../../../Sandbox/assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("uTexture", 0);
    }

    void Renderer2D::Shutdown() {
        PYRE_PROFILE_FUNCTION();

        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        PYRE_PROFILE_FUNCTION();

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        PYRE_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const glm::vec4& color) {
        DrawQuad(pos, rot, size, s_Data->WhiteTexture, color);
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, texture, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint) {
        DrawQuad(pos, rot, size, texture, 1.0f, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
        DrawQuad({ pos.x, pos.y, 0.0f }, rot, size, texture, texScale, tint);
    }

    void Renderer2D::DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint) {
        PYRE_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
        if (rot != 0) {
            // Rotation is expensive
            transform = glm::rotate(transform, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
        }
        transform = glm::scale(transform, { size.x, size.y, 1.0f });

        s_Data->TextureShader->SetMat4("uTransform", transform);
        s_Data->TextureShader->SetFloat("uTexScale", texScale);
        s_Data->TextureShader->SetFloat4("uColor", tint);

        texture->Bind(0);
        s_Data->QuadVA->Bind();
        RenderCommand::DrawElement(s_Data->QuadVA);
    }

}