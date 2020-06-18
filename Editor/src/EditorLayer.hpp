#pragma once
#include <Pyre/Pyre.hpp>

namespace Pyre {

    class EditorLayer : public Layer {
    public:
        EditorLayer();

        void OnAttach() override;
        void OnDetach() override;

        void Tick(float dt) override;
        void Draw() override;
        void ImGuiDraw() override;
        void OnEvent(Event& e) override;

    private:
        Ref<Framebuffer> m_Framebuffer;
        OrthographicCameraController m_CameraController;

        glm::vec2 m_ViewportSize = { 0, 0 };

        Ref<Texture2D> m_CheckerboardTexture;
    };

}