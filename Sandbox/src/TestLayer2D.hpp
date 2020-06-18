#pragma once
#include <Pyre/Pyre.hpp>
#include <glm/glm.hpp>
#include "ParticleSystem.hpp"

class TestLayer2D : public Pyre::Layer {
public:
    TestLayer2D();

    void OnAttach() override;
    void OnDetach() override;

    void Tick(float dt) override;
    void Draw() override;
    void ImGuiDraw() override;
    void OnEvent(Pyre::Event& e) override;

private:
    Pyre::OrthographicCameraController m_CameraController;

    Pyre::Ref<Pyre::Texture2D> m_CheckerboardTexture;
    Pyre::Ref<Pyre::Texture2D> m_SpriteSheet;
    Pyre::Ref<Pyre::SubTexture2D> m_Sprite;

    glm::vec4 m_SquareColor = { 0.8f, 0.3f, 0.6f, 1.0f };

    ParticleSystem m_ParticleSystem;
    ParticleProps m_Particle;
};