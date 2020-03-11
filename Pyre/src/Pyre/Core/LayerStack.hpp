#pragma once
#include "Pyre/Core/Layer.hpp"

namespace Pyre {

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(const Ref<Layer>& layer);
        void PushOverlay(const Ref<Layer>& overlay);
        void PopLayer(const Ref<Layer>& layer);
        void PopOverlay(const Ref<Layer>& overlay);

        std::vector<Ref<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<Ref<Layer>>::iterator end()   { return m_Layers.end(); }
        std::vector<Ref<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Ref<Layer>>::reverse_iterator rend()   { return m_Layers.rend(); }

    private:
        std::vector<Ref<Layer>> m_Layers;
        unsigned int m_InsertIndex = 0;
    };

}