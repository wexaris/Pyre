#pragma once
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(bool showConsole = true);
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void Tick(float) override {}
        void Draw() override {}
        void ImGuiDraw() override;
        void OnEvent(Event& event) override;

        void Begin();
        void End();

        void HandleEvents(bool handle) { m_HandleEvents = handle; }

    private:
        bool m_HandleEvents = true;
        bool m_ShowConsole;
    };

}