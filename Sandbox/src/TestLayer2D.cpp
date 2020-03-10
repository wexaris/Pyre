#include "TestLayer2D.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

TextLayer2D::TextLayer2D() :
    Layer("TestLayer2D"),
    m_CameraController(16.f / 9.f, true)
{}

void TextLayer2D::OnAttach() {
    m_Texture = Pyre::Texture2D::Create("../../../Sandbox/assets/textures/test.png");
}

void TextLayer2D::OnDetach() {

}

void TextLayer2D::OnUpdate(float ts) {
    m_CameraController.OnUpdate(ts);

    Pyre::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

    Pyre::Renderer2D::BeginScene(m_CameraController.GetCamera());
    Pyre::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 0.5f, 0.2f }, m_SquareColor);
    Pyre::Renderer2D::DrawQuad({ 0.0f, 0.5f, -0.1f }, 45.0f, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Pyre::Renderer2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, { 1.0f, 1.0f }, m_Texture, m_SquareColor);
    Pyre::Renderer2D::EndScene();
}

void TextLayer2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void TextLayer2D::OnEvent(Pyre::Event& e) {
    m_CameraController.OnEvent(e);
}