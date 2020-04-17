#pragma once
#include "Pyre/Renderer/Camera.hpp"
#include "Pyre/Renderer/Texture.hpp"

namespace Pyre {

    class Renderer2D {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));

        static void DrawRotatedQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));

        struct Statistics {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            uint32_t GetVetexCount() const { return QuadCount * 4; }
            uint32_t GetIndexCount() const { return QuadCount * 6; }
        };

        static Statistics GetStats();
        static void ResetStats();

    private:
        Renderer2D() = delete;

        static void StartBatch();
        static void Flush();
    };

}