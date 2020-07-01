#pragma once
#include "Pyre/Events/KeyCodes.hpp"
#include "Pyre/Events/MouseCodes.hpp"
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
        static void PollInputs();

        template<typename T>
        static bool IsInputPressed(T input) {
            auto item = s_InputMap.find(static_cast<uint16_t>(input));
            if (item != s_InputMap.end())
                return IsInputPressed(item->second);

            PYRE_CORE_WARN("Input #{} not mapped!", static_cast<uint16_t>(input));
            return false;
        }

        static bool IsInputPressed(InputKey input) {
            if (std::holds_alternative<KeyCode>(input.Value))
                return IsKeyPressed(std::get<KeyCode>(input.Value));
            if (std::holds_alternative<MouseCode>(input.Value))
                return IsMouseButtonPressed(std::get<MouseCode>(input.Value));

            PYRE_CORE_ERROR("Invalid input type!");
            return false;
        }

        template<typename T>
        static void Remap(T name, InputKey input) { s_InputMap[static_cast<uint16_t>(name)] = input; }

        static bool IsKeyPressed(KeyCode key);
        static uint16_t GetKeyRepeatCount(KeyCode key) { return s_KeyRepeatCount.count(key) ? s_KeyRepeatCount[key] : 0; }
        static uint16_t IncrementKeyRepeatCount(KeyCode key) { return s_KeyRepeatCount[key]++; }
        static void ResetKeyRepeatCount(KeyCode key) { s_KeyRepeatCount.erase(key); }

        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetMousePos();
        static float GetMouseX();
        static float GetMouseY();

    private:
        static std::unordered_map<uint16_t, InputKey> s_InputMap;
        static std::unordered_map<KeyCode, unsigned int> s_KeyRepeatCount;
    };

}