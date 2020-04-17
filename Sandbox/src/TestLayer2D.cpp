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

    Pyre::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Pyre::Renderer2D::DrawQuad({ 0.0f,  0.0f, -0.5f }, rotation, { 1.0f, 1.0f }, m_Texture, 10.0f, m_SquareColor);
    Pyre::Renderer2D::DrawQuad({ 0.5f,  0.0f,  0.1f }, 0.0f, { 0.5f, 0.2f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Pyre::Renderer2D::DrawQuad({ -1.0f,  0.0f,  0.2f }, 90.0f, { 0.3f, 0.2f }, m_SquareColor);
    Pyre::Renderer2D::EndScene();

    rotation += 0.1f;
}

void TestLayer2D::ImGuiDraw() {
    PYRE_PROFILE_FUNCTION();

    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void TestLayer2D::OnEvent(Pyre::Event& e) {
    m_CameraController.OnEvent(e);
}