#include "TestLayer2D.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

TestLayer2D::TestLayer2D() :
    Layer("TestLayer2D"),
    m_CameraController(true)
{}

void TestLayer2D::OnAttach() {
    PYRE_PROFILE_FUNCTION();

    m_CheckerboardTexture = Pyre::Texture2D::Create("assets/textures/checkerboard.png");
    m_SpriteSheet = Pyre::Texture2D::Create("assets/textures/sheet_grass.png");
    m_Sprite = Pyre::SubTexture2D::Create(m_SpriteSheet, { 70, 70 }, { 1, 1 }, { 1, 2 });

    m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
    m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
    m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
    m_Particle.LifeTime = 1.0f;
    m_Particle.Velocity = { 0.0f, 0.0f };
    m_Particle.VelocityVariation = { 3.0f, 1.0f };
    m_Particle.Position = { 0.0f, 0.0f };
}

void TestLayer2D::OnDetach() {
    PYRE_PROFILE_FUNCTION();
}

static float s_Rotation = 0.0f;

void TestLayer2D::Tick(float dt) {
    PYRE_PROFILE_FUNCTION();

    if (Pyre::Input::IsKeyPressed(Pyre::Key::Escape)) {
        Pyre::Application::Get().Close();
    }

    m_CameraController.Tick(dt);
    s_Rotation += 45.0f * dt;

    if (Pyre::Input::IsMouseButtonPressed(Pyre::Mouse::ButtonLeft)) {
        auto [x, y] = Pyre::Input::GetMousePos();
        auto width = Pyre::Application::Get().GetWindow().GetWidth();
        auto height = Pyre::Application::Get().GetWindow().GetHeight();

        auto bounds = m_CameraController.GetBounds();
        auto pos = m_CameraController.GetPosition();
        x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
        y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
        m_Particle.Position = { x + pos.x, y + pos.y };
        for (int i = 0; i < 5; i++)
            m_ParticleSystem.Emit(m_Particle);
    }

    m_ParticleSystem.Tick(dt);
}

void TestLayer2D::Draw() {
    PYRE_PROFILE_FUNCTION();

    Pyre::Renderer2D::ResetStats();

    Pyre::RenderCommand::Clear({ 0.1, 0.1, 0.1, 1 });

    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Pyre::Renderer2D::DrawQuad({ 0.0,  0.0, -0.5 }, { 10, 10 }, m_CheckerboardTexture, 10);
    Pyre::Renderer2D::DrawRotatedQuad({ 1.0,  0.0,  0.2 }, glm::radians(s_Rotation), { 1, 1 }, m_SquareColor);
    Pyre::Renderer2D::DrawRotatedQuad({ -1.0,  0.0,  0.2 }, glm::radians(s_Rotation), { 1, 1 }, m_CheckerboardTexture, m_SquareColor);
    Pyre::Renderer2D::EndScene();
    
    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
        for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
            glm::vec4 col = { (x + 5.0f) / 10.0f, 0.5f, (y + 5.0f) / 10.0f, 0.95f };
            Pyre::Renderer2D::DrawQuad({ x,  y }, { 0.5f, 0.5f }, col);
        }
    }
    Pyre::Renderer2D::EndScene();

    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Pyre::Renderer2D::DrawQuad({ 0.0,  0.0, 0.9 }, { 5, 5 }, m_Sprite);
    Pyre::Renderer2D::EndScene();

    m_ParticleSystem.Draw(m_CameraController.GetCamera());
}

void TestLayer2D::ImGuiDraw() {
    PYRE_PROFILE_FUNCTION();

    ImGui::Begin("Statistics");

    auto stats = Pyre::Renderer2D::GetStats();
    ImGui::Text("FPS: %d (%f)", Pyre::Application::Get().GetFPS(), Pyre::Application::Get().GetDeltaTime());
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);

    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

    ImGui::End();
}

void TestLayer2D::OnEvent(Pyre::Event& e) {
    m_CameraController.OnEvent(e);
}