#include "pyrepch.hpp"
#include "Pyre/Core/Window.hpp"

#ifdef PYRE_PLATFORM_WINDOWS
    #include "Platform/Windows/WindowsWindow.hpp"
#endif

namespace Pyre {

    Scope<Window> Window::Create(const WindowProperties& properties) {
#ifdef PYRE_PLATFORM_WINDOWS
        return MakeScope<WindowsWindow>(properties);
#endif
        PYRE_CORE_ASSERT(false, "Invalid Platform!");
        return nullptr;
    }

}