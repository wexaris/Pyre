#include <Pyre.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

class TestLayer : public Pyre::Layer {
public:
    TestLayer() : Layer("Test") {

        float square_verts[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        uint32_t square_indices[6] = { 0, 1 , 2, 2, 3, 0 };

        Pyre::BufferLayout square_layout = {
            { Pyre::ShaderDataType::Float3, "aPos" },
            { Pyre::ShaderDataType::Float2, "aTexCoord" }
        };

        m_SquareVA = Pyre::VertexArray::Create();
        Pyre::Ref<Pyre::VertexBuffer> square_vb;
        square_vb = Pyre::VertexBuffer::Create(square_verts, sizeof(square_verts));
        square_vb->SetLayout(square_layout);
        m_SquareVA->AddVertexBuffer(square_vb);

        Pyre::Ref<Pyre::IndexBuffer> square_ib;
        square_ib = Pyre::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
        m_SquareVA->SetIndexBuffer(square_ib);

        m_FlatColorShader = Pyre::Shader::Create("../../../Sandbox/assets/shaders/FlatColor.glsl");

        m_Texture = Pyre::Texture2D::Create("../../../Sandbox/assets/textures/test.png");
        auto textureShader = m_ShaderLib.Load("../../../Sandbox/assets/shaders/Texture.glsl");
        textureShader->Bind();
        textureShader->UploadUniformInt("uTexture", 0);
    }

    void OnUpdate(float ts) override {
        PYRE_TRACE("Delta time: {}s", ts);

        // Camera move
        if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        }
        else if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }

        if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        }
        else if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }

        // Camera rotate
        if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        else if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        // Render
        Pyre::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Pyre::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

        m_FlatColorShader->Bind();
        m_FlatColorShader->UploadUniformFloat3("uColor", m_SquareColor);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {

                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;

                Pyre::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }

        m_Texture->Bind(0);
        Pyre::Renderer::Submit(m_ShaderLib.Get("Texture"), m_SquareVA);

        Pyre::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    void OnEvent(Pyre::Event& event) {

    }

private:
    Pyre::ShaderLibrary m_ShaderLib;
    Pyre::Ref<Pyre::VertexArray> m_SquareVA;
    Pyre::Ref<Pyre::Shader> m_FlatColorShader;
    Pyre::Ref<Pyre::Texture2D> m_Texture;

    Pyre::OrthographicCamera m_Camera = Pyre::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    
    glm::vec3 m_CameraPosition = glm::vec3();
    float m_CameraMoveSpeed = 1.f;

    float m_CameraRotation = 0.f;
    float m_CameraRotationSpeed = 30.f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Pyre::Application {
public:
    Sandbox() {
        PushLayer(Pyre::MakeRef<TestLayer>());
    }
};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}