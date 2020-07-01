#pragma once

namespace Pyre {

    enum class KeyCode : uint16_t {

        Space = 32,
        Apostrophe = 39,/* ' */
        Comma = 44,     /* , */
        Minus = 45,     /* - */
        Period = 46,    /* . */
        Slash = 47,     /* / */

        D0 = 48,
        D1 = 49,
        D2 = 50,
        D3 = 51,
        D4 = 52,
        D5 = 53,
        D6 = 54,
        D7 = 55,
        D8 = 56,
        D9 = 57,

        Semicolon = 59, /* ; */
        Equal = 61,     /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftBracket = 91,  /* [ */
        Backslash = 92,    /* \ */
        RightBracket = 93, /* ] */
        GraveAccent = 96,  /* ` */

        World1 = 61,       /* non-US #1 */
        World2 = 162,      /* non-US #2 */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,

        /* Keypad */
        KP0 = 320,
        KP1 = 321,
        KP2 = 322,
        KP3 = 323,
        KP4 = 324,
        KP5 = 325,
        KP6 = 326,
        KP7 = 327,
        KP8 = 328,
        KP9 = 329,
        KPDecimal = 330,
        KPDivide = 331,
        KPMultiply = 332,
        KPSubtract = 333,
        KPAdd = 334,
        KPEnter = 335,
        KPEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    };
    using Key = KeyCode;

    static std::ostream& operator<<(std::ostream& os, KeyCode key) {
        return os << static_cast<int32_t>(key);
    }

}

#define PYRE_KEY_SPACE           ::Pyre::Key::Space
#define PYRE_KEY_APOSTROPHE      ::Pyre::Key::Apostrophe    /* ' */
#define PYRE_KEY_COMMA           ::Pyre::Key::Comma         /* , */
#define PYRE_KEY_MINUS           ::Pyre::Key::Minus         /* - */
#define PYRE_KEY_PERIOD          ::Pyre::Key::Period        /* . */
#define PYRE_KEY_SLASH           ::Pyre::Key::Slash         /* / */
#define PYRE_KEY_0               ::Pyre::Key::D0
#define PYRE_KEY_1               ::Pyre::Key::D1
#define PYRE_KEY_2               ::Pyre::Key::D2
#define PYRE_KEY_3               ::Pyre::Key::D3
#define PYRE_KEY_4               ::Pyre::Key::D4
#define PYRE_KEY_5               ::Pyre::Key::D5
#define PYRE_KEY_6               ::Pyre::Key::D6
#define PYRE_KEY_7               ::Pyre::Key::D7
#define PYRE_KEY_8               ::Pyre::Key::D8
#define PYRE_KEY_9               ::Pyre::Key::D9
#define PYRE_KEY_SEMICOLON       ::Pyre::Key::Semicolon     /* ; */
#define PYRE_KEY_EQUAL           ::Pyre::Key::Equal         /* = */
#define PYRE_KEY_A               ::Pyre::Key::A
#define PYRE_KEY_B               ::Pyre::Key::B
#define PYRE_KEY_C               ::Pyre::Key::C
#define PYRE_KEY_D               ::Pyre::Key::D
#define PYRE_KEY_E               ::Pyre::Key::E
#define PYRE_KEY_F               ::Pyre::Key::F
#define PYRE_KEY_G               ::Pyre::Key::G
#define PYRE_KEY_H               ::Pyre::Key::H
#define PYRE_KEY_I               ::Pyre::Key::I
#define PYRE_KEY_J               ::Pyre::Key::J
#define PYRE_KEY_K               ::Pyre::Key::K
#define PYRE_KEY_L               ::Pyre::Key::L
#define PYRE_KEY_M               ::Pyre::Key::M
#define PYRE_KEY_N               ::Pyre::Key::N
#define PYRE_KEY_O               ::Pyre::Key::O
#define PYRE_KEY_P               ::Pyre::Key::P
#define PYRE_KEY_Q               ::Pyre::Key::Q
#define PYRE_KEY_R               ::Pyre::Key::R
#define PYRE_KEY_S               ::Pyre::Key::S
#define PYRE_KEY_T               ::Pyre::Key::T
#define PYRE_KEY_U               ::Pyre::Key::U
#define PYRE_KEY_V               ::Pyre::Key::V
#define PYRE_KEY_W               ::Pyre::Key::W
#define PYRE_KEY_X               ::Pyre::Key::X
#define PYRE_KEY_Y               ::Pyre::Key::Y
#define PYRE_KEY_Z               ::Pyre::Key::Z
#define PYRE_KEY_LEFT_BRACKET    ::Pyre::Key::LeftBracket   /* [ */
#define PYRE_KEY_BACKSLASH       ::Pyre::Key::Backslash     /* \ */
#define PYRE_KEY_RIGHT_BRACKET   ::Pyre::Key::RightBracket  /* ] */
#define PYRE_KEY_GRAVE_ACCENT    ::Pyre::Key::GraveAccent   /* ` */
#define PYRE_KEY_WORLD_1         ::Pyre::Key::World1        /* non-US #1 */
#define PYRE_KEY_WORLD_2         ::Pyre::Key::World2        /* non-US #2 */

#define PYRE_KEY_ESCAPE          ::Pyre::Key::Escape
#define PYRE_KEY_ENTER           ::Pyre::Key::Enter
#define PYRE_KEY_TAB             ::Pyre::Key::Tab
#define PYRE_KEY_BACKSPACE       ::Pyre::Key::Backspace
#define PYRE_KEY_INSERT          ::Pyre::Key::Insert
#define PYRE_KEY_DELETE          ::Pyre::Key::Delete
#define PYRE_KEY_RIGHT           ::Pyre::Key::Right
#define PYRE_KEY_LEFT            ::Pyre::Key::Left
#define PYRE_KEY_DOWN            ::Pyre::Key::Down
#define PYRE_KEY_UP              ::Pyre::Key::Up
#define PYRE_KEY_PAGE_UP         ::Pyre::Key::PageUp
#define PYRE_KEY_PAGE_DOWN       ::Pyre::Key::PageDown
#define PYRE_KEY_HOME            ::Pyre::Key::Home
#define PYRE_KEY_END             ::Pyre::Key::End
#define PYRE_KEY_CAPS_LOCK       ::Pyre::Key::CapsLock
#define PYRE_KEY_SCROLL_LOCK     ::Pyre::Key::ScrollLock
#define PYRE_KEY_NUM_LOCK        ::Pyre::Key::NumLock
#define PYRE_KEY_PRINT_SCREEN    ::Pyre::Key::PrintScreen
#define PYRE_KEY_PAUSE           ::Pyre::Key::Pause
#define PYRE_KEY_F1              ::Pyre::Key::F1
#define PYRE_KEY_F2              ::Pyre::Key::F2
#define PYRE_KEY_F3              ::Pyre::Key::F3
#define PYRE_KEY_F4              ::Pyre::Key::F4
#define PYRE_KEY_F5              ::Pyre::Key::F5
#define PYRE_KEY_F6              ::Pyre::Key::F6
#define PYRE_KEY_F7              ::Pyre::Key::F7
#define PYRE_KEY_F8              ::Pyre::Key::F8
#define PYRE_KEY_F9              ::Pyre::Key::F9
#define PYRE_KEY_F10             ::Pyre::Key::F10
#define PYRE_KEY_F11             ::Pyre::Key::F11
#define PYRE_KEY_F12             ::Pyre::Key::F12
#define PYRE_KEY_F13             ::Pyre::Key::F13
#define PYRE_KEY_F14             ::Pyre::Key::F14
#define PYRE_KEY_F15             ::Pyre::Key::F15
#define PYRE_KEY_F16             ::Pyre::Key::F16
#define PYRE_KEY_F17             ::Pyre::Key::F17
#define PYRE_KEY_F18             ::Pyre::Key::F18
#define PYRE_KEY_F19             ::Pyre::Key::F19
#define PYRE_KEY_F20             ::Pyre::Key::F20
#define PYRE_KEY_F21             ::Pyre::Key::F21
#define PYRE_KEY_F22             ::Pyre::Key::F22
#define PYRE_KEY_F23             ::Pyre::Key::F23
#define PYRE_KEY_F24             ::Pyre::Key::F24
#define PYRE_KEY_F25             ::Pyre::Key::F25

#define PYRE_KEY_KP_0            ::Pyre::Key::KP0
#define PYRE_KEY_KP_1            ::Pyre::Key::KP1
#define PYRE_KEY_KP_2            ::Pyre::Key::KP2
#define PYRE_KEY_KP_3            ::Pyre::Key::KP3
#define PYRE_KEY_KP_4            ::Pyre::Key::KP4
#define PYRE_KEY_KP_5            ::Pyre::Key::KP5
#define PYRE_KEY_KP_6            ::Pyre::Key::KP6
#define PYRE_KEY_KP_7            ::Pyre::Key::KP7
#define PYRE_KEY_KP_8            ::Pyre::Key::KP8
#define PYRE_KEY_KP_9            ::Pyre::Key::KP9
#define PYRE_KEY_KP_DECIMAL      ::Pyre::Key::KPDecimal
#define PYRE_KEY_KP_DIVIDE       ::Pyre::Key::KPDivide
#define PYRE_KEY_KP_MULTIPLY     ::Pyre::Key::KPMultiply
#define PYRE_KEY_KP_SUBTRACT     ::Pyre::Key::KPSubtract
#define PYRE_KEY_KP_ADD          ::Pyre::Key::KPAdd
#define PYRE_KEY_KP_ENTER        ::Pyre::Key::KPEnter
#define PYRE_KEY_KP_EQUAL        ::Pyre::Key::KPEqual

#define PYRE_KEY_LEFT_SHIFT      ::Pyre::Key::LeftShift
#define PYRE_KEY_LEFT_CONTROL    ::Pyre::Key::LeftControl
#define PYRE_KEY_LEFT_ALT        ::Pyre::Key::LeftAlt
#define PYRE_KEY_LEFT_SUPER      ::Pyre::Key::LeftSuper
#define PYRE_KEY_RIGHT_SHIFT     ::Pyre::Key::RightShift
#define PYRE_KEY_RIGHT_CONTROL   ::Pyre::Key::RightControl
#define PYRE_KEY_RIGHT_ALT       ::Pyre::Key::RightAlt
#define PYRE_KEY_RIGHT_SUPER     ::Pyre::Key::RightSuper
#define PYRE_KEY_MENU            ::Pyre::Key::Menu