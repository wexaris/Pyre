#include "pyrepch.hpp"
#include "Pyre/Core/LayerStack.hpp"

namespace Pyre {

    LayerStack::LayerStack() {

    }

    LayerStack::~LayerStack() {
        for (auto& layer : m_Layers) {
            layer->OnDetach();
            layer.reset();
        }
    }

    void LayerStack::PushLayer(const Ref<Layer>& layer) {
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        m_InsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(const Ref<Layer>& overlay) {
        m_Layers.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(const Ref<Layer>& layer) {
        auto iter = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
        if (iter != m_Layers.begin() + m_InsertIndex) {
            layer->OnDetach();
            m_Layers.erase(iter);
            m_InsertIndex--;
        }
    }

    void LayerStack::PopOverlay(const Ref<Layer>& overlay) {
        auto iter = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
        if (iter != m_Layers.end()) {
            overlay->OnDetach();
            m_Layers.erase(iter);
        }
    }

}