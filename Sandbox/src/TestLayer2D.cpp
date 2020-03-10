#include "TestLayer2D.hpp"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

TextLayer2D::TextLayer2D() :
    Layer("TestLayer2D"),
    m_CameraController(16.f / 9.f, true)
{}

void TextLayer2D::OnAttach() {

    float square_verts[4 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
    };

    uint32_t square_indices[6] = { 0, 1 , 2, 2, 3, 0 };

    Pyre::BufferLayout square_layout = {
        { Pyre::ShaderDataType::Float3, "aPos" },
    };

    m_SquareVA = Pyre::VertexArray::Create();

    Pyre::Ref<Pyre::VertexBuffer> square_vb;
    square_vb = Pyre::VertexBuffer::Create(square_verts, sizeof(square_verts));
    square_vb->SetLayout(square_layout);
    m_SquareVA->AddVertexBuffer(square_vb);

    Pyre::Ref<Pyre::IndexBuffer> square_ib;
    square_ib = Pyre::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(square_ib);

    m_Shader = Pyre::Shader::Create("../../../Sandbox/assets/shaders/FlatColor.glsl");
}

void TextLayer2D::OnDetach() {

}

void TextLayer2D::OnUpdate(float ts) {
    m_CameraController.OnUpdate(ts);

    Pyre::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });
    Pyre::Renderer::BeginScene(m_CameraController.GetCamera());

    glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

    m_Shader->Bind();
    m_Shader->SetFloat4("uColor", m_SquareColor);
    Pyre::Renderer::Submit(m_Shader, m_SquareVA, glm::mat4(1.f));

    Pyre::Renderer::EndScene();
}

void TextLayer2D::OnImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void TextLayer2D::OnEvent(Pyre::Event& e) {
    m_CameraController.OnEvent(e);
}