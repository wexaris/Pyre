#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Events/WindowEvents.hpp"
#include "Pyre/Renderer/Renderer.hpp"

#include "Pyre/Renderer/OpenGLVertexArray.hpp"
#include "Pyre/Renderer/OpenGLBuffer.hpp"
#include "Pyre/Renderer/OpenGLShader.hpp"

namespace Pyre {

    std::shared_ptr<VertexArray> va;
    std::shared_ptr<VertexArray> square_va;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Shader> square_shader;

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        PYRE_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_CB(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);


        float verts[7 * 3] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f , 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 0.0f , 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 1.0f , 0.0f, 1.0f,
        };

        uint32_t indices[3] = { 0, 1 , 2 };

        BufferLayout layout = {
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float4, "aColor" },
        };

        va.reset(VertexArray::Create());
        std::shared_ptr<VertexBuffer> vb;
        vb.reset(VertexBuffer::Create(verts, sizeof(verts)));
        vb->SetLayout(layout);
        va->AddVertexBuffer(vb);

        std::shared_ptr<IndexBuffer> ib;
        ib.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        va->SetIndexBuffer(ib);

        std::string vert_src = R"(
            #version 330 core

            layout(location = 0) in vec3 aPos;
            layout(location = 1) in vec4 aColor;
            out vec3 vPos;
            out vec4 vColor;

            void main() {
                vPos = aPos;
                vColor = aColor;
                gl_Position = vec4(aPos, 1.0);
            }
        )";
        std::string frag_src = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 vPos;
            in vec4 vColor;

            void main() {
                color = vec4(0.2, 0.3, 0.8, 1.0);
                color = vColor;
            }
        )";
        shader = std::make_unique<OpenGLShader>(vert_src, frag_src);


        float square_verts[7 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
        };

        uint32_t square_indices[6] = { 0, 1 , 2, 2, 3, 0 };

        BufferLayout square_layout = {
            { ShaderDataType::Float3, "aPos" },
        };

        square_va.reset(VertexArray::Create());
        std::shared_ptr<VertexBuffer> square_vb;
        square_vb.reset(VertexBuffer::Create(square_verts, sizeof(square_verts)));
        square_vb->SetLayout(square_layout);
        square_va->AddVertexBuffer(square_vb);

        std::shared_ptr<IndexBuffer> square_ib;
        square_ib.reset(IndexBuffer::Create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
        square_va->SetIndexBuffer(square_ib);

        std::string square_vert_src = R"(
            #version 330 core

            layout(location = 0) in vec3 aPos;
            out vec3 vPos;

            void main() {
                vPos = aPos;
                gl_Position = vec4(aPos, 1.0);
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
        square_shader = std::make_unique<OpenGLShader>(square_vert_src, square_frag_src);
    }

    Application::~Application() {
            
    }

    void Application::Run() {
        while (m_Running) {
            RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });

            Renderer::BeginScene();
            square_shader->Bind();
            Renderer::Submit(square_va);
            shader->Bind();
            Renderer::Submit(va);
            Renderer::EndScene();

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }

            // ImGui render calls
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay) {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CB(Application::_OnWindowClose));
        dispatcher.Dispatch<WindowMoveEvent>(BIND_EVENT_CB(Application::_OnWindowMove));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(Application::_OnWindowResize));
        dispatcher.Dispatch<WindowFocusEvent>(BIND_EVENT_CB(Application::_OnWindowFocus));
        dispatcher.Dispatch<WindowLoseFocusEvent>(BIND_EVENT_CB(Application::_OnWindowLoseFocus));
        dispatcher.Dispatch<WindowMaximizeEvent>(BIND_EVENT_CB(Application::_OnWindowMaximize));
        dispatcher.Dispatch<WindowMinimizeEvent>(BIND_EVENT_CB(Application::_OnWindowMinimize));
        dispatcher.Dispatch<WindowRestoreEvent>(BIND_EVENT_CB(Application::_OnWindowRestore));

        for (auto iter = m_LayerStack.rbegin(); iter != m_LayerStack.rend(); iter++) {
            (*iter)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::_OnWindowClose(WindowCloseEvent& e) {
        Shutdown();
        OnWindowClose(e);
        return false;
    }

    bool Application::_OnWindowMove(WindowMoveEvent& e) {
        OnWindowMove(e);
        return false;
    }

    bool Application::_OnWindowResize(WindowResizeEvent& e) {
        OnWindowResize(e);
        return false;
    }

    bool Application::_OnWindowFocus(WindowFocusEvent& e) {
        OnWindowFocus(e);
        return false;
    }

    bool Application::_OnWindowLoseFocus(WindowLoseFocusEvent& e) {
        OnWindowLoseFocus(e);
        return false;
    }

    bool Application::_OnWindowMaximize(WindowMaximizeEvent& e) {
        OnWindowMaximize(e);
        return false;
    }

    bool Application::_OnWindowMinimize(WindowMinimizeEvent& e) {
        OnWindowMinimize(e);
        return false;
    }

    bool Application::_OnWindowRestore(WindowRestoreEvent& e) {
        OnWindowRestore(e);
        return false;
    }

}