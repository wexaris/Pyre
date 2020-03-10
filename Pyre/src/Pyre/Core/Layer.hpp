#pragma once
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float timestep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event&) {}

        inline const std::string& GetName() const { return m_Name; }
        inline bool IsEnabled() const   { return m_Enabled; }
        inline void Enable(bool enable) { m_Enabled = enable; }

    protected:
        std::string m_Name;
        bool m_Enabled;
    };

}