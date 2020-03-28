#include <Pyre.hpp>
#include <EntryPoint.hpp>
#include "TestLayer2D.hpp"

class Sandbox : public Pyre::Application {
public:
    Sandbox() : Pyre::Application({ "Sandbox" }) {
        PushLayer(new TestLayer2D());
    }

    ~Sandbox() {

    }
};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}