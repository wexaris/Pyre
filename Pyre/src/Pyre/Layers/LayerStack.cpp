#include "pyrepch.hpp"
#include "Pyre/Layers/LayerStack.hpp"

namespace Pyre {

    LayerStack::LayerStack() {

    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        m_InsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
        overlay->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (iter != m_Layers.end()) {
            m_Layers.erase(iter);
            m_InsertIndex--;
            layer->OnDetach();
        }
    }

    void LayerStack::PopOverlay(Layer* overlay) {
        auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (iter != m_Layers.end()) {
            m_Layers.erase(iter);
            overlay->OnDetach();
        }
    }

}