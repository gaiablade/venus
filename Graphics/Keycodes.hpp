#pragma once

namespace ga {
    enum class key {
        SPACE = 32,
        APOSTROPHE = 39  /* ' */,
        COMMA =  44  /* , */,
        MINUS =  45  /* - */,
        PERIOD = 46  /* . */,
        SLASH =  47,  /* / */
        NUM_0 =  48,
        NUM_1 =  49,
        NUM_2 =  50,
        NUM_3 =  51,
        NUM_4 =  52,
        NUM_5 =  53,
        NUM_6 =  54,
        NUM_7 =  55,
        NUM_8 =  56,
        NUM_9 =  57,
        SEMICOLON = 59,  /* ; */
        EQUAL = 61,  /* = */
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
        LEFT_BRACKET = 91 ,
        BACKSLASH = 92 ,
        RIGHT_BRACKET = 93 ,
        GRAVE_ACCENT = 96 ,
        WORLD_1 = 161,
        WORLD_2 = 162,

        /* Function keys */
        ESCAPE = 256,
        ENTER = 257,
        TAB = 258,
        BACKSPACE = 259,
        INSERT = 260,
        DELETE = 261,
        RIGHT = 262,
        LEFT = 263,
        DOWN = 264,
        UP = 265,
        PAGE_UP = 266,
        PAGE_DOWN = 267,
        HOME = 268,
        END = 269,
        CAPS_LOCK = 280,
        SCROLL_LOCK = 281,
        NUM_LOCK = 282,
        PRINT_SCREEN = 283,
        PAUSE = 284,
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
        KP_0 = 320,
        KP_1 = 321,
        KP_2 = 322,
        KP_3 = 323,
        KP_4 = 324,
        KP_5 = 325,
        KP_6 = 326,
        KP_7 = 327,
        KP_8 = 328,
        KP_9 = 329,
        KP_DECIMAL = 330,
        KP_DIVIDE = 331,
        KP_MULTIPLY = 332,
        KP_SUBTRACT = 333,
        KP_ADD = 334,
        KP_ENTER = 335,
        KP_EQUAL = 336,
        LEFT_SHIFT = 340,
        LEFT_CONTROL = 341,
        LEFT_ALT = 342,
        LEFT_SUPER = 343,
        RIGHT_SHIFT = 344,
        RIGHT_CONTROL = 345,
        RIGHT_ALT = 346,
        RIGHT_SUPER = 347,
        MENU = 348,

        LAST = MENU,

        SHIFT = 0x0001,

        CONTROL = 0x0002,

        ALT = 0x0004,

        SUPER = 0x0008,

        MOD_CAPS_LOCK = 0x0010,
        MOD_NUM_LOCK = 0x0020,

        MOUSE_1 = 0,
        MOUSE_2 = 1,
        MOUSE_3 = 2,
        MOUSE_4 = 3,
        MOUSE_5 = 4,
        MOUSE_6 = 5,
        MOUSE_7 = 6,
        MOUSE_8 = 7,
        MOUSE_LAST = MOUSE_8,
        MOUSE_LEFT = MOUSE_1,
        MOUSE_RIGHT = MOUSE_2,
        MOUSE_MIDDLE = MOUSE_3,

        JOYSTICK_1  = 0,
        JOYSTICK_2  = 1,
        JOYSTICK_3  = 2,
        JOYSTICK_4  = 3,
        JOYSTICK_5  = 4,
        JOYSTICK_6  = 5,
        JOYSTICK_7  = 6,
        JOYSTICK_8  = 7,
        JOYSTICK_9  = 8,
        JOYSTICK_10 = 9,
        JOYSTICK_11 = 10,
        JOYSTICK_12 = 11,
        JOYSTICK_13 = 12,
        JOYSTICK_14 = 13,
        JOYSTICK_15 = 14,
        JOYSTICK_16 = 15,
        JOYSTICK_LAST = JOYSTICK_16,
        GAMEPAD_BUTTON_A             = 0,
        GAMEPAD_BUTTON_B             = 1,
        GAMEPAD_BUTTON_X             = 2,
        GAMEPAD_BUTTON_Y             = 3,
        GAMEPAD_BUTTON_LEFT_BUMPER   = 4,
        GAMEPAD_BUTTON_RIGHT_BUMPER  = 5,
        GAMEPAD_BUTTON_BACK          = 6,
        GAMEPAD_BUTTON_START         = 7,
        GAMEPAD_BUTTON_GUIDE         = 8,
        GAMEPAD_BUTTON_LEFT_THUMB    = 9,
        GAMEPAD_BUTTON_RIGHT_THUMB   = 10,
        GAMEPAD_BUTTON_DPAD_UP       = 11,
        GAMEPAD_BUTTON_DPAD_RIGHT    = 12,
        GAMEPAD_BUTTON_DPAD_DOWN     = 13,
        GAMEPAD_BUTTON_DPAD_LEFT     = 14,
        GAMEPAD_BUTTON_LAST          = GAMEPAD_BUTTON_DPAD_LEFT,

        GAMEPAD_BUTTON_CROSS    =  GAMEPAD_BUTTON_A,
        GAMEPAD_BUTTON_CIRCLE   =  GAMEPAD_BUTTON_B,
        GAMEPAD_BUTTON_SQUARE   =  GAMEPAD_BUTTON_X,
        GAMEPAD_BUTTON_TRIANGLE =  GAMEPAD_BUTTON_Y,

        GAMEPAD_AXIS_LEFT_X        = 0,
        GAMEPAD_AXIS_LEFT_Y        = 1,
        GAMEPAD_AXIS_RIGHT_X       = 2,
        GAMEPAD_AXIS_RIGHT_Y       = 3,
        GAMEPAD_AXIS_LEFT_TRIGGER  = 4,
        GAMEPAD_AXIS_RIGHT_TRIGGER = 5,
        GAMEPAD_AXIS_LAST          = GAMEPAD_AXIS_RIGHT_TRIGGER
    };
}