#include "pyrepch.hpp"
#include "Platform/Windows/WindowsInput.hpp"
#include "Pyre/Core/Application.hpp"

#include <GLFW/glfw3.h>

namespace Pyre {

    void WindowsInput::PollInputsImpl() {
        glfwPollEvents();
    }

    bool WindowsInput::IsKeyPressedImpl(KeyCode key) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button) {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl() {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float WindowsInput::GetMouseXImpl() {
        auto [x, y] = GetMousePosImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl() {
        auto [x, y] = GetMousePosImpl();
        return y;
    }

}