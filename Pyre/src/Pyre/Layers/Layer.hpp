#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event&) {}

        inline const std::string& GetName() const { return m_Name; }
        inline void Enable(bool enable) { m_Enabled = enable; }
        inline bool IsEnabled() const   { return m_Enabled; }

    protected:
        std::string m_Name;
        bool m_Enabled;
    };

}