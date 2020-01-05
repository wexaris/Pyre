#include "pyrepch.hpp"
#include "Pyre/Layers/LayerStack.hpp"

namespace Pyre {

    LayerStack::LayerStack() {
        m_InsertPos = m_Layers.begin();
    }

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_InsertPos = m_Layers.emplace(m_InsertPos, layer);
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto iter = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if (iter != m_Layers.end()) {
            delete *iter;
            m_Layers.erase(iter);
            m_InsertPos--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay) {
        auto iter = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if (iter != m_Layers.end()) {
            delete *iter;
            m_Layers.erase(iter);
        }
    }

}