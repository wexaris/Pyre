#pragma once
#include "Pyre/Input/KeyCodes.hpp"
#include "Pyre/Input/MouseCodes.hpp"
#include <variant>

namespace Pyre {
    
    struct InputKey {
        std::variant<KeyCode, MouseCode> Value;

        InputKey() = default;
        InputKey(KeyCode key) : Value(key) {}
        InputKey(MouseCode button) : Value(button) {}
    };

    class Input {
    public:
        static void PollInputs() { s_Instance->PollInputsImpl(); }

        template<typename T>
        static bool IsInputPressed(T input) {
            auto& item = s_Instance->m_InputMap.find(static_cast<uint16_t>(input));
            if (item != s_Instance->m_InputMap.end()) {
                return IsInputPressed(item->second);
            }

            PYRE_CORE_WARN("Input #{} not mapped!", static_cast<uint16_t>(input));
            return false;
        }

        static bool IsInputPressed(InputKey input) {
            if (std::holds_alternative<KeyCode>(input.Value)) {
                return IsKeyPressed(std::get<KeyCode>(input.Value));
            }
            if (std::holds_alternative<MouseCode>(input.Value)) {
                return IsMouseButtonPressed(std::get<MouseCode>(input.Value));
            }

            PYRE_CORE_ERROR("Invalid input type!");
            return false;
        }

        template<typename T>
        static void Remap(T name, InputKey input) { s_Instance->m_InputMap[static_cast<uint16_t>(name)] = input; }

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

        virtual void PollInputsImpl() = 0;

        virtual bool IsKeyPressedImpl(KeyCode key) = 0;

        virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static Scope<Input> s_Instance;
        static std::unordered_map<uint16_t, InputKey> m_InputMap;
        static std::unordered_map<KeyCode, unsigned int> s_KeyRepeatCount;
    };

}