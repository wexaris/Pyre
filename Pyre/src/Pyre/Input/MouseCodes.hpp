#pragma once

namespace Pyre {

    enum class MouseCode {

        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,
        ButtonLast = Button7,

        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    };
    using Mouse = MouseCode;

}

#define PYRE_MOUSE_BUTTON_0      ::Pyre::Mouse::Button0
#define PYRE_MOUSE_BUTTON_1      ::Pyre::Mouse::Button1
#define PYRE_MOUSE_BUTTON_2      ::Pyre::Mouse::Button2
#define PYRE_MOUSE_BUTTON_3      ::Pyre::Mouse::Button3
#define PYRE_MOUSE_BUTTON_4      ::Pyre::Mouse::Button4
#define PYRE_MOUSE_BUTTON_5      ::Pyre::Mouse::Button5
#define PYRE_MOUSE_BUTTON_6      ::Pyre::Mouse::Button6
#define PYRE_MOUSE_BUTTON_7      ::Pyre::Mouse::Button7
#define PYRE_MOUSE_BUTTON_LAST   ::Pyre::Mouse::ButtonLast
#define PYRE_MOUSE_BUTTON_LEFT   ::Pyre::Mouse::ButtonLeft
#define PYRE_MOUSE_BUTTON_RIGHT  ::Pyre::Mouse::ButtonRight
#define PYRE_MOUSE_BUTTON_MIDDLE ::Pyre::Mouse::ButtonMiddle