#pragma once
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer(bool showConsole = true);
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;

        void Begin();
        void End();

        void OnImGuiRender() override;

    private:
        bool m_ShowConsole;
    };

}