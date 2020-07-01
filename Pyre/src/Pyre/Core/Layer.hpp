#pragma once
#include "Pyre/Core/Drawable.hpp"
#include "Pyre/Events/Event.hpp"

namespace Pyre {

    class Layer : public Drawable, public ImGuiDrawable {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void Tick(float dt) = 0;
        virtual void Draw() override = 0;
        virtual void ImGuiDraw() override {}
        virtual void OnEvent(Event&) {}

        const std::string& GetName() const { return m_Name; }
        bool IsEnabled() const   { return m_Enabled; }
        void Enable(bool enable) { m_Enabled = enable; }

    protected:
        std::string m_Name;
        bool m_Enabled;
    };

}