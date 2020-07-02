#include "EditorLayer.hpp"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Pyre {

    EditorLayer::EditorLayer() :
        Layer("EditorLayer"),
        m_CameraController(true) {
    }

    void EditorLayer::OnAttach() {
        PYRE_PROFILE_FUNCTION();

        FramebufferProperties fbProps;
        fbProps.Width = 1280;
        fbProps.Height = 720;
        m_Framebuffer = Framebuffer::Create(fbProps);

        m_CheckerboardTexture = Texture2D::Create("assets/textures/checkerboard.png");
    }

    void EditorLayer::OnDetach() {
        PYRE_PROFILE_FUNCTION();
    }

    void EditorLayer::Tick(float dt) {
        PYRE_PROFILE_FUNCTION();

        // Update framebuffer and camera size if resized
        const FramebufferProperties& fb = m_Framebuffer->GetProperties();
        if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
            (m_ViewportSize.x != fb.Width || m_ViewportSize.y != fb.Height))
        {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_CameraController.Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
        }

        // Tick
        if (m_ViewportFocused) {
            m_CameraController.Tick(dt);
        }
    }

    void EditorLayer::Draw() {
        PYRE_PROFILE_FUNCTION();

        Renderer2D::ResetStats();

        m_Framebuffer->Bind();
        RenderCommand::Clear({ 0.1, 0.1, 0.1, 1 });

        Renderer2D::BeginScene(m_CameraController.GetCamera());
        Renderer2D::DrawQuad({ 0.0,  0.0, -0.5 }, { 10, 10 }, m_CheckerboardTexture, 10);

        for (float y = -5.0f; y <= 5.0f; y += 0.5f) {
            for (float x = -5.0f; x <= 5.0f; x += 0.5f) {
                glm::vec4 col = { (x + 5.0f) / 10.0f, 0.5f, (y + 5.0f) / 10.0f, 0.95f };
                Renderer2D::DrawQuad({ x,  y }, { 0.5f, 0.5f }, col);
            }
        }
        Renderer2D::EndScene();

        m_Framebuffer->Unbind();
    }

    void EditorLayer::ImGuiDraw() {
        PYRE_PROFILE_FUNCTION();

        static bool dockingEnabled = true;
        if (dockingEnabled) {

            static bool dockspaceOpen = true;
            static bool opt_fullscreen_persistant = true;
            bool opt_fullscreen = opt_fullscreen_persistant;
            static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

            // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
            // because it would be confusing to have two docking targets within each others.
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            if (opt_fullscreen) {
                ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->GetWorkPos());
                ImGui::SetNextWindowSize(viewport->GetWorkSize());
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }

            // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
            // and handle the pass-thru hole, so we ask Begin() to not render a background.
            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
            // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
            // all active windows docked into it will lose their parent and become undocked.
            // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
            // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
            ImGui::PopStyleVar();

            if (opt_fullscreen) {
                ImGui::PopStyleVar(2);
            }

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {

                    if (ImGui::MenuItem("Exit")) { Pyre::Application::Get().Close(); }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }
            ImGui::End();
        }

        ImGui::Begin("Statistics");
        auto stats = Renderer2D::GetStats();
        ImGui::Text("FPS: %d (%f)", Application::Get().GetFPS(), Application::Get().GetDeltaTime());
        ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");
        // Handle viewport focus
        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->HandleEvents(!m_ViewportFocused || !m_ViewportHovered);
        // Handle sizing
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportSize.x, viewportSize.y };
        // Set viewport image
        uintptr_t texID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image((void*)texID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::OnEvent(Pyre::Event& e) {
        m_CameraController.OnEvent(e);
    }

}