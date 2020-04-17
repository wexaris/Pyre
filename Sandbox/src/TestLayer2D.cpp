#include "TestLayer2D.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

TestLayer2D::TestLayer2D() :
    Layer("TestLayer2D"),
    m_CameraController(16.f / 9.f, true)
{}

void TestLayer2D::OnAttach() {
    PYRE_PROFILE_FUNCTION();

    m_Texture = Pyre::Texture2D::Create("assets/textures/test.png");
}

void TestLayer2D::OnDetach() {
    PYRE_PROFILE_FUNCTION();
}

void TestLayer2D::Tick(float dt) {
    PYRE_PROFILE_FUNCTION();

    m_CameraController.Tick(dt);
}

void TestLayer2D::Draw(float alpha) {
    PYRE_PROFILE_FUNCTION();

    static float rotation = 0.0f;

    Pyre::Renderer2D::ResetStats();
    Pyre::RenderCommand::Clear({ 0.1, 0.1, 0.1, 1 });

    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Pyre::Renderer2D::DrawQuad({ 0.0,  0.0, -0.5 }, { 10, 10 }, m_Texture, 10);
    Pyre::Renderer2D::DrawRotatedQuad({ 1.0,  0.0,  0.2 }, rotation, { 1, 1 }, m_SquareColor);
    Pyre::Renderer2D::DrawRotatedQuad({ -1.0,  0.0,  0.2 }, rotation, { 1, 1 }, m_Texture, m_SquareColor);
    Pyre::Renderer2D::EndScene();
    
    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
        for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
            glm::vec4 col = { (x + 5.0f) / 10.0f, 0.5f, (y + 5.0f) / 10.0f, 1.0f };
            Pyre::Renderer2D::DrawQuad({ x,  y }, { 0.5f, 0.5f }, col);
        }
    }
    Pyre::Renderer2D::EndScene();

    rotation += 0.2f;
}

void TestLayer2D::ImGuiDraw() {
    PYRE_PROFILE_FUNCTION();

    ImGui::Begin("Debug");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();

    ImGui::Begin("Statistics");
    auto stats = Pyre::Renderer2D::GetStats();
    ImGui::Text("Draw Calls: %d", stats.DrawCalls);
    ImGui::Text("Quads: %d", stats.QuadCount);
    ImGui::End();
}

void TestLayer2D::OnEvent(Pyre::Event& e) {
    m_CameraController.OnEvent(e);
}