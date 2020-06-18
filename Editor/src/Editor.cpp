#include <Pyre/Pyre.hpp>
#include <Pyre/EntryPoint.hpp>
#include "EditorLayer.hpp"

namespace Pyre {

    class Editor : public Pyre::Application {
    public:
        Editor(const Pyre::ApplicationProperties& props) : Pyre::Application(props) {

            PushLayer(new EditorLayer());
        }

        ~Editor() = default;
    };

}

Pyre::Application* Pyre::CreateApplication() {

    Pyre::ApplicationProperties props;
    props.BaseDirectory = "Editor";
    props.Window.Title = "Editor";
    props.Window.Width = 1280;
    props.Window.Height = 720;
    props.Window.VSync = false;
    props.MinTickRate = 60;
    props.MaxSubsteps = 4;

    return new Pyre::Editor(props);
}
