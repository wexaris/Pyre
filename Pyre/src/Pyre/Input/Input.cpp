#include "pyrepch.hpp"
#include "Pyre/Input/Input.hpp"

#ifdef PYRE_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsInput.hpp"
#endif


namespace Pyre {

    Scope<Input> Input::s_Instance = Input::Create();
    std::unordered_map<KeyCode, unsigned int> Input::s_KeyRepeatCount;

    Scope<Input> Input::Create() {
#ifdef PYRE_PLATFORM_WINDOWS
        return MakeScope<WindowsInput>();
#endif
        PYRE_CORE_ASSERT(false, "Invalid Platform!");
        return nullptr;
    }

}