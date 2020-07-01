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

        void AllowEvents(bool allow) { m_AllowEvents = allow; }

    private:
        bool m_AllowEvents = true;
        bool m_ShowConsole;
    };

}