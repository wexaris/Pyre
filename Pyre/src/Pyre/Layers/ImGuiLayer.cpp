#include "pyrepch.hpp"
#include "Pyre/Application.hpp"
#include "Pyre/Layers/ImGuiLayer.hpp"
#include "Pyre/Layers/ImGuiRenderer.hpp"
#include "Pyre/Input/KeyCodes.hpp"

#include <GLFW/glfw3.h> // for glfwGetTime()
#include <glad/glad.h>  // for glViewport();

namespace Pyre {

    ImGuiLayer::ImGuiLayer() :
        Layer("ImGuiLayer")
    {}

    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = input::KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = input::KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = input::KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = input::KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = input::KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = input::KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = input::KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = input::KEY_HOME;
        io.KeyMap[ImGuiKey_End] = input::KEY_END;
        io.KeyMap[ImGuiKey_Insert] = input::KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = input::KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = input::KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = input::KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = input::KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = input::KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = input::KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = input::KEY_A;
        io.KeyMap[ImGuiKey_C] = input::KEY_C;
        io.KeyMap[ImGuiKey_V] = input::KEY_V;
        io.KeyMap[ImGuiKey_X] = input::KEY_X;
        io.KeyMap[ImGuiKey_Y] = input::KEY_Y;
        io.KeyMap[ImGuiKey_Z] = input::KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach() {

    }

    void ImGuiLayer::OnUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.f / 60.f);
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressEvent>(BIND_EVENT_CB(ImGuiLayer::OnKeyPress));
        dispatcher.Dispatch<KeyReleaseEvent>(BIND_EVENT_CB(ImGuiLayer::OnKeyRelease));
        dispatcher.Dispatch<KeyTypeEvent>(BIND_EVENT_CB(ImGuiLayer::OnKeyType));
        dispatcher.Dispatch<MouseButtonPressEvent>(BIND_EVENT_CB(ImGuiLayer::OnMouseButtonPress));
        dispatcher.Dispatch<MouseButtonReleaseEvent>(BIND_EVENT_CB(ImGuiLayer::OnMouseButtonRelease));
        dispatcher.Dispatch<MouseMoveEvent>(BIND_EVENT_CB(ImGuiLayer::OnMouseMove));
        dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT_CB(ImGuiLayer::OnMouseScroll));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CB(ImGuiLayer::OnWindowResize));
    }

    bool ImGuiLayer::OnKeyPress(KeyPressEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[input::KEY_LEFT_CONTROL] || io.KeysDown[input::KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[input::KEY_LEFT_SHIFT] || io.KeysDown[input::KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[input::KEY_LEFT_ALT] || io.KeysDown[input::KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[input::KEY_LEFT_SUPER] || io.KeysDown[input::KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::OnKeyRelease(KeyReleaseEvent& event) {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;

        io.KeyCtrl = io.KeysDown[input::KEY_LEFT_CONTROL] || io.KeysDown[input::KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[input::KEY_LEFT_SHIFT] || io.KeysDown[input::KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[input::KEY_LEFT_ALT] || io.KeysDown[input::KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[input::KEY_LEFT_SUPER] || io.KeysDown[input::KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::OnKeyType(KeyTypeEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        if (e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000) {
            io.AddInputCharacter((unsigned short)e.GetKeyCode());
        }
        return false;
    }

    bool ImGuiLayer::OnMouseButtonPress(MouseButtonPressEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonRelease(MouseButtonReleaseEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::OnMouseMove(MouseMoveEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScroll(MouseScrollEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheel += e.GetYOffset();
        io.MouseWheelH += e.GetXOffset();
        return false;
    }

    bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e) {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeigth());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0, 0, e.GetWidth(), e.GetHeigth());
        return false;
    }

}