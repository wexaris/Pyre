#include <Pyre.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

class TestLayer : public Pyre::Layer {
public:
    TestLayer() : Layer("Test") {

        float triangle_verts[7 * 3] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f , 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f , 0.0f, 1.0f,
        };

        uint32_t triangle_indices[3] = { 0, 1 , 2 };

        Pyre::BufferLayout triangle_layout = {
            { Pyre::ShaderDataType::Float3, "aPos" },
            { Pyre::ShaderDataType::Float4, "aColor" },
        };

        m_TriangleVA = Pyre::VertexArray::Create();
        Pyre::Ref<Pyre::VertexBuffer> triangle_vb;
        triangle_vb = Pyre::VertexBuffer::Create(triangle_verts, sizeof(triangle_verts));
        triangle_vb->SetLayout(triangle_layout);
        m_TriangleVA->AddVertexBuffer(triangle_vb);

        Pyre::Ref<Pyre::IndexBuffer> triangle_ib;
        triangle_ib = Pyre::IndexBuffer::Create(triangle_indices, sizeof(triangle_indices) / sizeof(uint32_t));
        m_TriangleVA->SetIndexBuffer(triangle_ib);

        std::string triangle_vert_src = R"(
            #version 330 core

            uniform mat4 uViewProj;
            uniform mat4 uTransform;

            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            out vec3 vPos;
            out vec4 vColor;

            void main() {
                vPos = aPos;
                vColor = aColor;
                gl_Position = uViewProj * uTransform * vec4(aPos, 1.0);
            }
        )";
        std::string triangle_frag_src = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 vPos;
            in vec4 vColor;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
                color = vColor;
            }
        )";
        m_TriangleShader = Pyre::Shader::Create(triangle_vert_src, triangle_frag_src);


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

        std::string square_vert_src = R"(
            #version 330 core

            uniform mat4 uViewProj;
            uniform mat4 uTransform;

            layout(location = 0) in vec3 aPos;
            out vec3 vPos;

            void main() {
                vPos = aPos;
                gl_Position = uViewProj * uTransform * vec4(aPos, 1.0);
            }
        )";
        std::string square_frag_src = R"(
            #version 330 core

            uniform vec3 uColor;

            layout(location = 0) out vec4 color;
            in vec3 vPos;

            void main() {
                color = vec4(uColor, 1.0);
            }
        )";
        m_SquareShader = Pyre::Shader::Create(square_vert_src, square_frag_src);


        std::string texture_vert_src = R"(
            #version 330 core

            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec2 aTexCoord;

            uniform mat4 uViewProj;
            uniform mat4 uTransform;
            
            out vec2 vTexCoord;

            void main() {
                vTexCoord = aTexCoord;
                gl_Position = uViewProj * uTransform * vec4(aPos, 1.0);
            }
        )";
        std::string texture_frag_src = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform sampler2D uTexture;

            in vec2 vTexCoord;

            void main() {
                color = texture(uTexture, vTexCoord);
            }
        )";
        m_TextureShader = Pyre::Shader::Create(texture_vert_src, texture_frag_src);

        m_Texture = Pyre::Texture2D::Create("test.png");
        
        m_TextureShader->Bind();
        m_TextureShader->UploadUniformInt("uTexture", 0);
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

        Pyre::Renderer::BeginScene(&m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

        m_SquareShader->Bind();
        m_SquareShader->UploadUniformFloat3("uColor", m_SquareColor);

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {

                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;

                Pyre::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
            }
        }

        m_SquareShader->Bind();
        Pyre::Renderer::Submit(m_SquareShader, m_SquareVA);
        m_Texture->Bind(0);
        Pyre::Renderer::Submit(m_TextureShader, m_SquareVA);

        //Pyre::Renderer::Submit(m_TriangleShader, m_TriangleVA);

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
    Pyre::Ref<Pyre::VertexArray> m_TriangleVA, m_SquareVA;
    Pyre::Ref<Pyre::Shader> m_TriangleShader, m_SquareShader, m_TextureShader;
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