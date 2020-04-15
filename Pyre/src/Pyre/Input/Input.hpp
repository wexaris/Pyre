#pragma once
#include "Pyre/Input/KeyCodes.hpp"
#include "Pyre/Input/MouseCodes.hpp"

namespace Pyre {
    
    class Input {
    public:
        static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }
        
        static uint16_t GetKeyRepeatCount(KeyCode key) { return s_KeyRepeatCount.count(key) ? s_KeyRepeatCount[key] : 0; }
        static uint16_t IncrementKeyRepeatCount(KeyCode key) { return s_KeyRepeatCount[key]++; }
        static void ResetKeyRepeatCount(KeyCode key) { s_KeyRepeatCount.erase(key); }

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
        static std::unordered_map<KeyCode, unsigned int> s_KeyRepeatCount;

    };

}