#include <Pyre.hpp>

class Sandbox : public Pyre::Application {
public:
    Sandbox() = default;
    ~Sandbox() = default;

};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}