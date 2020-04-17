#pragma once
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(bool showConsole = true);
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void Draw(float alpha) override {}
        void ImGuiDraw() override;
        void OnEvent(Event& event) override;

        void Begin();
        void End();

    private:
        bool m_ShowConsole;
    };

}