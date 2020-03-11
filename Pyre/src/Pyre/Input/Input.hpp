#pragma once
#include "Pyre/Input/KeyCodes.hpp"
#include "Pyre/Input/MouseCodes.hpp"

namespace Pyre {
    
    class Input {
    public:
        static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
        
        static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

        static Scope<Input> Create();

    protected:
        Input() = default;

        virtual bool IsKeyPressedImpl(KeyCode key) = 0;

        virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Scope<Input> s_Instance;

    };

}