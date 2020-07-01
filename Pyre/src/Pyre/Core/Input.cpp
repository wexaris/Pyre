#include "pyrepch.hpp"
#include "Pyre/Core/Input.hpp"

namespace Pyre {

    std::unordered_map<uint16_t, InputKey> Input::s_InputMap;
    std::unordered_map<KeyCode, unsigned int> Input::s_KeyRepeatCount;

}