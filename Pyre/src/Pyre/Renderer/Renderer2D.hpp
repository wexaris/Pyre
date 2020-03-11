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

        static void DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec2& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& pos, float rot, const glm::vec2& size, const Ref<Texture2D>& texture, float texScale, const glm::vec4& tint = glm::vec4(1.0f));

    private:
        Renderer2D() = delete;
    };

}