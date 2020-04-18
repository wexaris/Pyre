#include <Pyre.hpp>
#include <EntryPoint.hpp>
#include "TestLayer2D.hpp"

class Sandbox : public Pyre::Application {
public:
    Sandbox(const Pyre::ApplicationProperties& props) : Pyre::Application(props) {

        PushLayer(new TestLayer2D());
    }

    ~Sandbox() = default;
};

Pyre::Application* Pyre::CreateApplication() {

    Pyre::ApplicationProperties props;
    props.BaseDirectory = "Sandbox";
    props.WindowProperties.Title = "Sandbox";
    props.WindowProperties.Width = 1080;
    props.WindowProperties.Height = 720;
    props.WindowProperties.VSync = false;

    return new Sandbox(props);
}