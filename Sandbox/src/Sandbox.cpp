#include <Pyre.hpp>
#include <EntryPoint.hpp>
#include "TestLayer2D.hpp"

class Sandbox : public Pyre::Application {
public:
    Sandbox(const Pyre::WindowProperties& props) :
        Pyre::Application("Sandbox", props)
    {
        PushLayer(new TestLayer2D());
    }

    ~Sandbox() = default;
};

Pyre::Application* Pyre::CreateApplication() {

    Pyre::WindowProperties windowProperties;
    windowProperties.Title = "Sandbox";
    windowProperties.Width = 1080;
    windowProperties.Height = 720;

    return new Sandbox(windowProperties);
}