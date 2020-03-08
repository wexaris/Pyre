#include <Pyre.hpp>

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

        m_TriangleVA.reset(Pyre::VertexArray::Create());
        std::shared_ptr<Pyre::VertexBuffer> triangle_vb;
        triangle_vb.reset(Pyre::VertexBuffer::Create(triangle_verts, sizeof(triangle_verts)));
        triangle_vb->SetLayout(triangle_layout);
        m_TriangleVA->AddVertexBuffer(triangle_vb);

        std::shared_ptr<Pyre::IndexBuffer> triangle_ib;
        triangle_ib.reset(Pyre::IndexBuffer::Create(triangle_indices, sizeof(triangle_indices) / sizeof(uint32_t)));
        m_TriangleVA->SetIndexBuffer(triangle_ib);

        std::string triangle_vert_src = R"(
            #version 330 core

            uniform mat4 uViewProj;

            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            out vec3 vPos;
            out vec4 vColor;

            void main() {
                vPos = aPos;
                vColor = aColor;
                gl_Position = uViewProj * vec4(aPos, 1.0);
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
        m_TriangleShader.reset(Pyre::Shader::Create(triangle_vert_src, triangle_frag_src));


        float square_verts[7 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };

        uint32_t square_indices[6] = { 0, 1 , 2, 2, 3, 0 };

        Pyre::BufferLayout square_layout = {
            { Pyre::ShaderDataType::Float3, "aPos" },
        };

        m_SquareVA.reset(Pyre::VertexArray::Create());
        std::shared_ptr<Pyre::VertexBuffer> square_vb;
        square_vb.reset(Pyre::VertexBuffer::Create(square_verts, sizeof(square_verts)));
        square_vb->SetLayout(square_layout);
        m_SquareVA->AddVertexBuffer(square_vb);

        std::shared_ptr<Pyre::IndexBuffer> square_ib;
        square_ib.reset(Pyre::IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(square_ib);

        std::string square_vert_src = R"(
            #version 330 core

            uniform mat4 uViewProj;

            layout(location = 0) in vec3 aPos;
            out vec3 vPos;

            void main() {
                vPos = aPos;
                gl_Position = uViewProj * vec4(aPos, 1.0);
            }
        )";
        std::string square_frag_src = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 vPos;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";
        m_SquareShader.reset(Pyre::Shader::Create(square_vert_src, square_frag_src));
    }

    void OnUpdate(float ts) override {
        PYRE_TRACE("Delta time: {}s", ts);

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

        if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_A)) {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        else if (Pyre::Input::IsKeyPressed(Pyre::input::KEY_D)) {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        Pyre::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

        m_Camera->SetPosition(m_CameraPosition);
        m_Camera->SetRotation(m_CameraRotation);

        Pyre::Renderer::BeginScene(m_Camera);

        Pyre::Renderer::Submit(m_SquareShader, m_SquareVA);
        Pyre::Renderer::Submit(m_TriangleShader, m_TriangleVA);

        Pyre::Renderer::EndScene();
    }

    void OnImGuiRender() override {

    }

    void OnEvent(Pyre::Event& event) {

    }

private:
    std::shared_ptr<Pyre::VertexArray> m_TriangleVA;
    std::shared_ptr<Pyre::VertexArray> m_SquareVA;
    std::shared_ptr<Pyre::Shader> m_TriangleShader;
    std::shared_ptr<Pyre::Shader> m_SquareShader;

    Pyre::OrthographicCamera* m_Camera = new Pyre::OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    glm::vec3 m_CameraPosition = glm::vec3();
    float m_CameraMoveSpeed = 1.f;

    float m_CameraRotation = 0.f;
    float m_CameraRotationSpeed = 30.f;
};

class Sandbox : public Pyre::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
    }
};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}