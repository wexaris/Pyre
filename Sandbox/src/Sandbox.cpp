#include <Pyre.hpp>
#include <imgui/imgui.h>

class TestLayer : public Pyre::Layer {
public:
    TestLayer() : Layer("Test") {}

    void OnUpdate() override {
        
    }

    void OnImGuiRender() override {
        ImGui::Begin("Test");
        ImGui::Text("Hello, World!");
        ImGui::End();
    }

    void OnEvent(Pyre::Event& event) {
        //PYRE_TRACE(event);
    }
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