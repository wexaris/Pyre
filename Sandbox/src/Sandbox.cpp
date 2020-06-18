#include <Pyre/Pyre.hpp>
#include <Pyre/EntryPoint.hpp>
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
    props.Window.Title = "Sandbox";
    props.Window.Width = 1280;
    props.Window.Height = 720;
    props.Window.VSync = false;
    props.MinTickRate = 60;
    props.MaxSubsteps = 4;

    return new Sandbox(props);
}
