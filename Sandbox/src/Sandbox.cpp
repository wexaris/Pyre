#include <Pyre.hpp>

class Sandbox : public Pyre::Application {
public:
    Sandbox() = default;
    ~Sandbox() = default;

    void Run() override {
        while(true) {
            PYRE_INFO("Hello!");
        }
    }

};

Pyre::Application* Pyre::CreateApplication() {
    return new Sandbox();
}