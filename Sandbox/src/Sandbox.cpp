#include <Pyre.hpp>
#include <EntryPoint.hpp>
#include "TestLayer2D.hpp"

class Sandbox : public Pyre::Application {
public:
    Sandbox() {
        PushLayer(new TextLayer2D());
    }

    ~Sandbox() {

    }
};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}