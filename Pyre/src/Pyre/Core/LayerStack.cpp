#include "pyrepch.hpp"
#include "Pyre/Core/LayerStack.hpp"

namespace Pyre {

    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_InsertIndex, layer);
        m_InsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay) {
        m_Layers.emplace_back(overlay);
    }

    Layer* LayerStack::PopLayer(Layer* layer) {
        auto iter = std::find(m_Layers.begin(), m_Layers.begin() + m_InsertIndex, layer);
        if (iter != m_Layers.begin() + m_InsertIndex) {
            layer->OnDetach();
            m_Layers.erase(iter);
            m_InsertIndex--;
        }
        else {
            PYRE_CORE_WARN("Failed to pop layer '{}'; Layer not found in layer stack!", layer->GetName());
        }
        return layer;
    }

    Layer* LayerStack::PopOverlay(Layer* overlay) {
        auto iter = std::find(m_Layers.begin() + m_InsertIndex, m_Layers.end(), overlay);
        if (iter != m_Layers.end()) {
            overlay->OnDetach();
            m_Layers.erase(iter);
        }
        else {
            PYRE_CORE_WARN("Failed to pop layer '{}'; Layer not found in layer stack!", overlay->GetName());
        }
        return overlay;
    }

}