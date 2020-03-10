#pragma once
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

    private: 
        float m_Time = 0.f;
    };

}