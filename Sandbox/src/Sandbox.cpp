#include <Pyre.hpp>

class TestLayer : public Pyre::Layer {
public:
    TestLayer() : Layer("Test") {}

    void OnUpdate() override {

    }

    void OnEvent(Pyre::Event& event) {
        //PYRE_TRACE(event);
    }
};

class Sandbox : public Pyre::Application {
public:
    Sandbox() {
        PushLayer(new TestLayer());
        PushOverlay(new Pyre::ImGuiLayer());
    }
};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}