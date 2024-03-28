//#pragma once
//
//// Include STD
//#include <vector>
//#include <string_view>
//#include <tuple>
//#include <type_traits>
//#include <bitset>
//#include <tuple>
//#include <memory>
//#include <iostream>
//#include <array>
//#include <algorithm>
//#include <map>
//// Include GTL
//#include "vec2.hpp"
//#include "timer.hpp"
//// Include GLEW.
//#   include <GL/glew.h>
//
//// Include GLFW3.
//#   include <GLFW/glfw3.h>
//
//namespace gla {
//
//
//
//    /* Number of keys defined in the Key::Id enumerator */
//    constexpr inline size_t GLA_EVENT_KEY_COUNT() {
//        return 124;
//    }
//    /* Number of mouse buttons defined in MoueKeyId */
//    constexpr inline size_t GLA_EVENT_BUTTON_COUNT() {
//        return  8;
//    }
//    /* Number of modifier bitfields defined in ModifierKeyBitfield */
//    constexpr inline size_t GLA_EVENT_MODIFIER_COUNT() {
//        return  7;
//    }
//
//    /* Type of input callbacks GLA can receive from GLFW. */
//    enum class InputType : int {
//        MOUSE_BUTTON,
//        CURSOR_POSITION,
//        CURSOR_ENTER,
//        SCROLL_MOVE,
//        KEYBOARD_KEY,
//        ENTERED_CHAR,
//        ENTERED_CHAR_WITH_MODS,
//        FILE_DROP,
//        JOYSTICK_CONFIG,
//        GAMEPAD_STATE
//    };
//
//    /* Key or button state. */
//    enum class KeyState : int {
//        RELEASED = GLFW_RELEASE,
//        PRESSED = GLFW_PRESS,
//        REPEATED = GLFW_REPEAT,
//    };
//
//    /* Keyboard key. */
//    enum class KeyboardKeyId : int {
//        UNKNOWN = GLFW_KEY_UNKNOWN,
//        SPACE = GLFW_KEY_SPACE,
//        APOSTROPHE = GLFW_KEY_APOSTROPHE,
//        COMMA = GLFW_KEY_COMMA,
//        MINUS = GLFW_KEY_MINUS,
//        PERIOD = GLFW_KEY_PERIOD,
//        SLASH = GLFW_KEY_SLASH,
//        NUM0 = GLFW_KEY_0,
//        NUM1 = GLFW_KEY_1,
//        NUM2 = GLFW_KEY_2,
//        NUM3 = GLFW_KEY_3,
//        NUM4 = GLFW_KEY_4,
//        NUM5 = GLFW_KEY_5,
//        NUM6 = GLFW_KEY_6,
//        NUM7 = GLFW_KEY_7,
//        NUM8 = GLFW_KEY_8,
//        NUM9 = GLFW_KEY_9,
//        SEMICOLON = GLFW_KEY_SEMICOLON,
//        EQUAL = GLFW_KEY_EQUAL,
//        A = GLFW_KEY_A,
//        B = GLFW_KEY_B,
//        C = GLFW_KEY_C,
//        D = GLFW_KEY_D,
//        E = GLFW_KEY_E,
//        F = GLFW_KEY_F,
//        G = GLFW_KEY_G,
//        H = GLFW_KEY_G,
//        I = GLFW_KEY_I,
//        J = GLFW_KEY_J,
//        K = GLFW_KEY_K,
//        L = GLFW_KEY_L,
//        M = GLFW_KEY_M,
//        N = GLFW_KEY_N,
//        O = GLFW_KEY_O,
//        P = GLFW_KEY_P,
//        Q = GLFW_KEY_Q,
//        R = GLFW_KEY_R,
//        S = GLFW_KEY_S,
//        T = GLFW_KEY_T,
//        U = GLFW_KEY_U,
//        V = GLFW_KEY_V,
//        W = GLFW_KEY_W,
//        X = GLFW_KEY_X,
//        Y = GLFW_KEY_Y,
//        Z = GLFW_KEY_Z,
//        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
//        BACKSLASH = GLFW_KEY_BACKSLASH,
//        BRACKET = GLFW_KEY_RIGHT_BRACKET,
//        ACCENT = GLFW_KEY_GRAVE_ACCENT,
//        WORLD_1 = GLFW_KEY_WORLD_1,
//        WORLD_2 = GLFW_KEY_WORLD_2,
//        ESCAPE = GLFW_KEY_ESCAPE,
//        ENTER = GLFW_KEY_ENTER,
//        TAB = GLFW_KEY_TAB,
//        BACKSPACE = GLFW_KEY_BACKSPACE,
//        INSERT = GLFW_KEY_INSERT,
//        DELETE = GLFW_KEY_DELETE,
//        RIGHT = GLFW_KEY_RIGHT,
//        LEFT = GLFW_KEY_LEFT,
//        DOWN = GLFW_KEY_DOWN,
//        UP = GLFW_KEY_UP,
//        PAGE_UP = GLFW_KEY_PAGE_UP,
//        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
//        HOME = GLFW_KEY_HOME,
//        END = GLFW_KEY_END,
//        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
//        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
//        NUM_LOCK = GLFW_KEY_NUM_LOCK,
//        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
//        PAUSE = GLFW_KEY_PAUSE,
//        F1 = GLFW_KEY_F1,
//        F2 = GLFW_KEY_F2,
//        F3 = GLFW_KEY_F3,
//        F4 = GLFW_KEY_F4,
//        F5 = GLFW_KEY_F5,
//        F6 = GLFW_KEY_F6,
//        F7 = GLFW_KEY_F7,
//        F8 = GLFW_KEY_F8,
//        F9 = GLFW_KEY_F9,
//        F10 = GLFW_KEY_F10,
//        F11 = GLFW_KEY_F11,
//        F12 = GLFW_KEY_F12,
//        F13 = GLFW_KEY_F13,
//        F14 = GLFW_KEY_F14,
//        F15 = GLFW_KEY_F15,
//        F16 = GLFW_KEY_F16,
//        F17 = GLFW_KEY_F17,
//        F18 = GLFW_KEY_F18,
//        F19 = GLFW_KEY_F19,
//        F20 = GLFW_KEY_F20,
//        F21 = GLFW_KEY_F21,
//        F22 = GLFW_KEY_F22,
//        F23 = GLFW_KEY_F23,
//        F24 = GLFW_KEY_F24,
//        F25 = GLFW_KEY_F25,
//        KP_0 = GLFW_KEY_KP_0,
//        KP_1 = GLFW_KEY_KP_1,
//        KP_2 = GLFW_KEY_KP_2,
//        KP_3 = GLFW_KEY_KP_3,
//        KP_4 = GLFW_KEY_KP_4,
//        KP_5 = GLFW_KEY_KP_5,
//        KP_6 = GLFW_KEY_KP_6,
//        KP_7 = GLFW_KEY_KP_7,
//        KP_8 = GLFW_KEY_KP_8,
//        KP_9 = GLFW_KEY_KP_9,
//        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
//        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
//        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
//        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
//        KP_ADD = GLFW_KEY_KP_ADD,
//        KP_ENTER = GLFW_KEY_KP_ENTER,
//        KP_EQUAL = GLFW_KEY_KP_EQUAL,
//        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
//        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
//        LEFT_ALT = GLFW_KEY_LEFT_ALT,
//        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
//        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
//        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
//        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
//        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
//        MENU = GLFW_KEY_MENU
//    }; // end enum class KeyboardKeyId : int
//
//    /* Keyboard key modifier bitfield. */
//    enum class ModifierKeyFlag : int {
//        SHIFT = GLFW_MOD_SHIFT,           /// 0x0001
//        CONTROL = GLFW_MOD_CONTROL,       /// 0x0002
//        ALT = GLFW_MOD_ALT,               /// 0x0004
//        SUPER = GLFW_MOD_SUPER,           /// 0x0008
//        CAPS_LOCK = GLFW_MOD_CAPS_LOCK,   /// 0x0010
//        NUM_LOCK = GLFW_MOD_NUM_LOCK,     /// 0x0020
//        NONE = -1
//    };
//
//    enum class MouseKeyId : int {
//        UNKNOWN = -1,
//        MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,  /// 0
//        MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,  /// 1
//        MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,  /// 2
//        MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,  /// 3
//        MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,  /// 4
//        MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,  /// 5
//        MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,  /// 6
//        MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,  /// 7
//        MOUSE_LEFT = GLFW_MOUSE_BUTTON_LEFT,   /// GLFW_MOUSE_BUTTON_1
//        MOUSE_RIGHT = GLFW_MOUSE_BUTTON_RIGHT, /// GLFW_MOUSE_BUTTON_2
//    };
//
//    // Map of indices for KeyboardKeyId enum
//    static std::map<KeyboardKeyId, int> KeyboardKeyIdIdxMap = {
//        {KeyboardKeyId::UNKNOWN, 0},
//        {KeyboardKeyId::SPACE, 1},
//        {KeyboardKeyId::APOSTROPHE, 2},
//        {KeyboardKeyId::COMMA, 3},
//        {KeyboardKeyId::MINUS, 4},
//        {KeyboardKeyId::PERIOD, 5},
//        {KeyboardKeyId::SLASH, 6},
//        {KeyboardKeyId::NUM0, 7},
//        {KeyboardKeyId::NUM1, 8},
//        {KeyboardKeyId::NUM2, 9},
//        {KeyboardKeyId::NUM3, 10},
//        {KeyboardKeyId::NUM4, 11},
//        {KeyboardKeyId::NUM5, 12},
//        {KeyboardKeyId::NUM6, 13},
//        {KeyboardKeyId::NUM7, 14},
//        {KeyboardKeyId::NUM8, 15},
//        {KeyboardKeyId::NUM9, 16},
//        {KeyboardKeyId::SEMICOLON, 17},
//        {KeyboardKeyId::EQUAL, 18},
//        {KeyboardKeyId::A, 19},
//        {KeyboardKeyId::B, 20},
//        {KeyboardKeyId::C, 21},
//        {KeyboardKeyId::D, 22},
//        {KeyboardKeyId::E, 23},
//        {KeyboardKeyId::F, 24},
//        {KeyboardKeyId::G, 25},
//        {KeyboardKeyId::H, 26},
//        {KeyboardKeyId::I, 27},
//        {KeyboardKeyId::J, 28},
//        {KeyboardKeyId::K, 29},
//        {KeyboardKeyId::L, 30},
//        {KeyboardKeyId::M, 31},
//        {KeyboardKeyId::N, 32},
//        {KeyboardKeyId::O, 33},
//        {KeyboardKeyId::P, 34},
//        {KeyboardKeyId::Q, 35},
//        {KeyboardKeyId::R, 36},
//        {KeyboardKeyId::S, 37},
//        {KeyboardKeyId::T, 38},
//        {KeyboardKeyId::U, 39},
//        {KeyboardKeyId::V, 40},
//        {KeyboardKeyId::W, 41},
//        {KeyboardKeyId::X, 42},
//        {KeyboardKeyId::Y, 43},
//        {KeyboardKeyId::Z, 44},
//        {KeyboardKeyId::LEFT_BRACKET, 45},
//        {KeyboardKeyId::BACKSLASH, 46},
//        {KeyboardKeyId::BRACKET, 47},
//        {KeyboardKeyId::ACCENT, 48},
//        {KeyboardKeyId::WORLD_1, 49},
//        {KeyboardKeyId::WORLD_2, 50},
//        {KeyboardKeyId::ESCAPE, 51},
//        {KeyboardKeyId::ENTER, 52},
//        {KeyboardKeyId::TAB, 53},
//        {KeyboardKeyId::BACKSPACE, 54},
//        {KeyboardKeyId::INSERT, 55},
//        {KeyboardKeyId::DELETE, 56},
//        {KeyboardKeyId::RIGHT, 57},
//        {KeyboardKeyId::LEFT, 58},
//        {KeyboardKeyId::DOWN, 59},
//        {KeyboardKeyId::UP, 60},
//        {KeyboardKeyId::PAGE_UP, 61},
//        {KeyboardKeyId::PAGE_DOWN, 62},
//        {KeyboardKeyId::HOME, 63},
//        {KeyboardKeyId::END, 64},
//        {KeyboardKeyId::CAPS_LOCK, 65},
//        {KeyboardKeyId::SCROLL_LOCK, 66},
//        {KeyboardKeyId::NUM_LOCK, 67},
//        {KeyboardKeyId::PRINT_SCREEN, 68},
//        {KeyboardKeyId::PAUSE, 69},
//        {KeyboardKeyId::F1, 70},
//        {KeyboardKeyId::F2, 71},
//        {KeyboardKeyId::F3, 72},
//        {KeyboardKeyId::F4, 73},
//        {KeyboardKeyId::F5, 74},
//        {KeyboardKeyId::F6, 75},
//        {KeyboardKeyId::F7, 76},
//        {KeyboardKeyId::F8, 77},
//        {KeyboardKeyId::F9, 78},
//        {KeyboardKeyId::F10, 79},
//        {KeyboardKeyId::F11, 80},
//        {KeyboardKeyId::F12, 81},
//        {KeyboardKeyId::F13, 82},
//        {KeyboardKeyId::F14, 83},
//        {KeyboardKeyId::F15, 84},
//        {KeyboardKeyId::F16, 85},
//        {KeyboardKeyId::F17, 86},
//        {KeyboardKeyId::F18, 87},
//        {KeyboardKeyId::F19, 88},
//        {KeyboardKeyId::F20, 89},
//        {KeyboardKeyId::F21, 90},
//        {KeyboardKeyId::F22, 91},
//        {KeyboardKeyId::F23, 92},
//        {KeyboardKeyId::F24, 93},
//        {KeyboardKeyId::F25, 94},
//        {KeyboardKeyId::KP_0, 95},
//        {KeyboardKeyId::KP_1, 96},
//        {KeyboardKeyId::KP_2, 97},
//        {KeyboardKeyId::KP_3, 98},
//        {KeyboardKeyId::KP_4, 99},
//        {KeyboardKeyId::KP_5, 100},
//        {KeyboardKeyId::KP_6, 101},
//        {KeyboardKeyId::KP_7, 102},
//        {KeyboardKeyId::KP_8, 103},
//        {KeyboardKeyId::KP_9, 104},
//        {KeyboardKeyId::KP_DECIMAL, 105},
//        {KeyboardKeyId::KP_DIVIDE, 106},
//        {KeyboardKeyId::KP_MULTIPLY, 107},
//        {KeyboardKeyId::KP_SUBTRACT, 108},
//        {KeyboardKeyId::KP_ADD, 109},
//        {KeyboardKeyId::KP_ENTER, 110},
//        {KeyboardKeyId::KP_EQUAL, 111},
//        {KeyboardKeyId::LEFT_SHIFT, 112},
//        {KeyboardKeyId::LEFT_CONTROL, 113},
//        {KeyboardKeyId::LEFT_ALT, 114},
//        {KeyboardKeyId::LEFT_SUPER, 115},
//        {KeyboardKeyId::RIGHT_SHIFT, 116},
//        {KeyboardKeyId::RIGHT_CONTROL, 117},
//        {KeyboardKeyId::RIGHT_ALT, 118},
//        {KeyboardKeyId::RIGHT_SUPER, 119},
//        {KeyboardKeyId::MENU, 120}
//    };
//
//    // Manually enter every index for every enum entry into a map
//    static std::map<ModifierKeyFlag, int> ModifierKeyFlagIdxMap = {
//        {ModifierKeyFlag::SHIFT, 0},
//        {ModifierKeyFlag::CONTROL, 1},
//        {ModifierKeyFlag::ALT, 2},
//        {ModifierKeyFlag::SUPER, 3},
//        {ModifierKeyFlag::CAPS_LOCK, 4},
//        {ModifierKeyFlag::NUM_LOCK, 5},
//        {ModifierKeyFlag::NONE, 6}
//        // ... (add more entries if needed)
//    };
//    /* Mouse button. */
//
//        // Manually enter every index for every enum entry into a map
//    static std::map<MouseKeyId, int> MouseKeyIdIdxMap = {
//        {MouseKeyId::UNKNOWN, 0},
//        {MouseKeyId::MOUSE_BUTTON_1, 1},
//        {MouseKeyId::MOUSE_BUTTON_2, 2},
//        {MouseKeyId::MOUSE_BUTTON_3, 3},
//        {MouseKeyId::MOUSE_BUTTON_4, 4},
//        {MouseKeyId::MOUSE_BUTTON_5, 5},
//        {MouseKeyId::MOUSE_BUTTON_6, 6},
//        {MouseKeyId::MOUSE_BUTTON_7, 7},
//        {MouseKeyId::MOUSE_BUTTON_8, 8},
//        {MouseKeyId::MOUSE_LEFT, 9},
//        {MouseKeyId::MOUSE_RIGHT, 10}
//        // ... (add more entries as needed)
//    };
//
//    enum class MouseWindowState {
//        ENTERED = GLFW_TRUE,
//        EXITED = GLFW_FALSE
//    };
//    enum class JoystickConfigState : int {
//        CONNECTED = GLFW_CONNECTED,
//        DISCONNECTED = GLFW_DISCONNECTED
//    };
//
//    /* Joystick input identifier. */
//    enum class JoystickId : int {
//        IN_1 = GLFW_JOYSTICK_1, /// 0
//        IN_2 = GLFW_JOYSTICK_2, /// 1
//        IN_3 = GLFW_JOYSTICK_3, /// 2
//        IN_4 = GLFW_JOYSTICK_4, /// 3
//        IN_5 = GLFW_JOYSTICK_5, /// 4
//        IN_6 = GLFW_JOYSTICK_6, /// 5
//        IN_7 = GLFW_JOYSTICK_7, /// 6
//        IN_8 = GLFW_JOYSTICK_8, /// 7
//        IN_9 = GLFW_JOYSTICK_9, /// 8
//        IN_10 = GLFW_JOYSTICK_10, /// 9
//        IN_11 = GLFW_JOYSTICK_11, /// 10
//        IN_12 = GLFW_JOYSTICK_12, /// 11
//        IN_13 = GLFW_JOYSTICK_13, /// 12
//        IN_14 = GLFW_JOYSTICK_14, /// 13
//        IN_15 = GLFW_JOYSTICK_15, /// 14
//        IN_16 = GLFW_JOYSTICK_16, /// 15
//    };
//
//    /* Joystick input hat state. */
//    enum class JoystickHatState : int {
//        CENTERED = GLFW_HAT_CENTERED, /// 0
//        UP = GLFW_HAT_UP, /// 1
//        RIGHT = GLFW_HAT_RIGHT, /// 2
//        DOWN = GLFW_HAT_DOWN, /// 3
//        LEFT = GLFW_HAT_LEFT, /// 4
//        RIGHT_UP = GLFW_HAT_RIGHT_UP, /// (GLFW_HAT_RIGHT | GLFW_HAT_UP)
//        RIGHT_DOWN = GLFW_HAT_RIGHT_DOWN, ///  (GLFW_HAT_RIGHT | GLFW_HAT_DOWN)
//        LEFT_UP = GLFW_HAT_LEFT_UP, /// (GLFW_HAT_LEFT | GLFW_HAT_UP)
//        LEFT_DOWN = GLFW_HAT_LEFT_DOWN, /// (GLFW_HAT_LEFT | GLFW_HAT_DOWN)
//    };
//    enum class GamepadButtonId : int {
//
//    };
//    enum class GamepadAxis : int {};
//
//    //
//    //    struct KeyboardState {
//    //        using state_bitset = std::bitset<124>;
//    //        std::vector<unsigned int> char_entered;
//    //        state_bitset state; /// True if pressed, false if released.
//    //        state_bitset fired_state; /// True if key was triggered, false otherwise.
//    //        state_bitset repeated_state; /// True if repeated, false otherwise.
//    //        state_bitset pressed_state; /// True if pressed, false otherwise.
//    //        state_bitset released_state; /// True if released, false otherwise.
//    //        state_bitset clicked_state; /// True if pressed then released, false otherwise.
//    //
//    //        /// <method:wasFired>
//    //        /// Returns true if the passed key was fired this frame.
//    //        [[nodiscard]] bool wasFired(KeyboardKeyId id) const {
//    //            return fired_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasPressed>
//    //        /// Returns true if the passed key was pressed this frame.
//    //        [[nodiscard]] bool wasPressed(KeyboardKeyId id) const {
//    //            return pressed_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasPressed>
//    //        /// Returns true if the passed key was pressed this frame.
//    //        [[nodiscard]] bool wasReleased(KeyboardKeyId id) const {
//    //            return released_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasClicked>
//    //        /// Returns true if the passed key was clicked this frame.
//    //        [[nodiscard]] bool wasClicked(KeyboardKeyId id) const {
//    //            return clicked_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasClicked>
//    //        /// Returns true if the passed key was held down until repeated this frame.
//    //        [[nodiscard]] bool wasRepeated(KeyboardKeyId id) const {
//    //            return repeated_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:isReleased>
//    //        /// Returns true if the final state of the passed key is released.
//    //        [[nodiscard]] bool isReleased(KeyboardKeyId id) const {
//    //            return !state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:isPressed>
//    //        /// Returns true if the final state of the passed key is pressed.
//    //        [[nodiscard]] bool isPressed(KeyboardKeyId id) const {
//    //            return state[static_cast<int>(id)];
//    //        }
//    //
//    //        KeyboardState& reset() {
//    //            // Clear previous state
//    //            state.reset();
//    //            fired_state.reset();
//    //            pressed_state.reset();
//    //            released_state.reset();
//    //            clicked_state.reset();
//    //            repeated_state.reset();
//    //
//    //            // Return reference to the new state
//    //            return *this;
//    //        }
//    //
//    //    };
//    //    struct MouseState {
//    //        using state_bitset = std::bitset<GLA_EVENT_BUTTON_COUNT()>;
//    //        double x_position{}; /// Last knows x position of the mouse.
//    //        double y_position{}; /// Last known y position of the mouse.
//    //        double x_scroll{}; /// Scroll wheel offset on x axis.
//    //        double y_scroll{}; /// Scroll wheel offset on y axis.
//    //        bool is_inside{}; /// True if mouse is inside a window.
//    //        state_bitset state; /// True if pressed, false if released.
//    //        state_bitset fired_state; /// True if key was triggered, false otherwise.
//    //        state_bitset repeated_state; /// True if repeated, false otherwise.
//    //        state_bitset pressed_state; /// True if pressed, false otherwise.
//    //        state_bitset released_state; /// True if released, false otherwise.
//    //        state_bitset clicked_state; /// True if pressed then released, false otherwise.
//    //
//    //        /// <method:wasFired>
//    //        /// Returns true if the passed key was fired this frame.
//    //        [[nodiscard]] bool wasFired(MouseKeyId id) const {
//    //            return fired_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasPressed>
//    //        /// Returns true if the passed key was pressed this frame.
//    //        [[nodiscard]] bool wasPressed(MouseKeyId id) const {
//    //            return pressed_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasReleased>
//    //        /// Returns true if the passed key was pressed this frame.
//    //        [[nodiscard]] bool wasReleased(MouseKeyId id) const {
//    //            return released_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasClicked>
//    //        /// Returns true if the passed key was clicked this frame.
//    //        [[nodiscard]] bool wasClicked(MouseKeyId id) const {
//    //            return clicked_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:wasClicked>
//    //        /// Returns true if the passed key was held down until repeated this frame.
//    //        [[nodiscard]] bool wasRepeated(MouseKeyId id) const {
//    //            return repeated_state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:isInside>
//    //        /// Returns true if the mouse is within the window.
//    //        [[nodiscard]] bool isInside(MouseKeyId id) const {
//    //            return is_inside;
//    //        }
//    //
//    //        /// <method:isReleased>
//    //        /// Returns true if the final state of the passed key is released.
//    //        [[nodiscard]] bool isReleased(MouseKeyId id) const {
//    //            return !state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:isPressed>
//    //        /// Returns true if the final state of the passed key is pressed.
//    //        [[nodiscard]] bool isPressed(MouseKeyId id) const {
//    //            return state[static_cast<int>(id)];
//    //        }
//    //
//    //        /// <method:lastMousePos>
//    //        /// Returns the last known mouse cursor position.
//    //        [[nodiscard]] std::pair<double, double> lastMousePosition() {
//    //            return std::make_pair(x_position, y_position);
//    //        }
//    //
//    //        /// <method:lastWheelDelta>
//    //        /// Returns the last scroll wheel offset.
//    //        [[nodiscard]] std::pair<double, double> lastWheelDelta() {
//    //            return std::make_pair(x_position, y_position);
//    //        }
//    //
//    //        MouseState& reset() {
//    //            // Clear previous state
//    //            x_position = 0.0;
//    //            y_position = 0.0;
//    //            x_scroll = 0.0;
//    //            y_scroll = 0.0;
//    //            is_inside = false;
//    //            state.reset();
//    //            fired_state.reset();
//    //            pressed_state.reset();
//    //            released_state.reset();
//    //            clicked_state.reset();
//    //            repeated_state.reset();
//    //
//    //            // Return reference to the new state
//    //            return *this;
//    //        }
//    //    };
//    //    struct ModifierState {
//    //        using state_bitset = std::bitset<GLA_EVENT_MODIFIER_COUNT()>;
//    //        state_bitset state; /// True if is activated, false if deactivated.
//    //
//    //        [[nodiscard]] bool isOn(ModifierKeyFlag mod) {
//    //            return state[static_cast<int>(mod)];
//    //        }
//    //
//    //        void set(ModifierKeyFlag mod, bool value) {
//    //            state[static_cast<int>(mod)] = value;
//    //        }
//    // 
//    // 
//    //
//    //        ModifierState& reset() {
//    //            // Clear previous state
//    //            state.reset();
//    //
//    //            // Return reference to the new state
//    //            return *this;
//    //        }
//    //    };
//    //    struct State {
//    //        std::vector<std::string> paths;
//    //        KeyboardState keyboard_state;
//    //        MouseState mouse_state;
//    //        ModifierState modifier_state;
//    //
//    //        State& reset() {
//    //            keyboard_state.reset();
//    //            mouse_state.reset();
//    //            modifier_state.reset();
//    //            return *this;
//    //        };
//    //    };
//    //
//        /* Event Slice Class */
//    struct Slice {
//         virtual InputType type() = 0;
//    };
//    struct Slice_keyboard_key : public Slice {
//        KeyState state;
//        KeyboardKeyId id;
//        ModifierKeyFlag mods;
//        int scancode;
//
//        explicit constexpr Slice_keyboard_key(
//            KeyState state = KeyState::RELEASED,
//            KeyboardKeyId id = KeyboardKeyId::UNKNOWN,
//            ModifierKeyFlag mods = ModifierKeyFlag::NONE, int scancode = -1)
//            : state(state)
//            , id(id)
//            , mods(mods)
//            , scancode(scancode) {
//        }
//        constexpr Slice_keyboard_key()
//            : state(KeyState::RELEASED)
//            , id(KeyboardKeyId::UNKNOWN)
//            , mods(ModifierKeyFlag::NONE)
//            , scancode(-1) {
//        }
//
//        InputType type() {
//            return InputType::KEYBOARD_KEY;
//        }
//    };
//    struct SliceENTERED_CHAR :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::ENTERED_CHAR>;
//        unsigned int unicode;
//        constexpr SliceENTERED_CHAR() = default;
//        explicit constexpr SliceENTERED_CHAR(unsigned int unicode)
//            : unicode(unicode) {
//        }
//
//        InputType type() {
//            return InputType::ENTERED_CHAR;
//        }
//    };
//    struct SliceENTERED_CHAR_WITH_MODS :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::ENTERED_CHAR_WITH_MODS>;
//        unsigned int unicode;
//        ModifierKeyFlag mods;
//        constexpr SliceENTERED_CHAR_WITH_MODS() = default;
//        explicit constexpr SliceENTERED_CHAR_WITH_MODS(unsigned int unicode, ModifierKeyFlag mods)
//            : unicode(unicode)
//            , mods(mods) {
//        }
//        InputType type() override {
//            return InputType::ENTERED_CHAR_WITH_MODS;
//        }
//    };
//    struct Slice_MOUSE_BUTTON :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::MOUSE_BUTTON>;
//        KeyState state;
//        MouseKeyId id;
//        ModifierKeyFlag mods;
//
//        explicit constexpr Slice_MOUSE_BUTTON(KeyState state, MouseKeyId id, ModifierKeyFlag mods)
//            : state(state)
//            , id(id)
//            , mods(mods) {
//        }
//        constexpr Slice_MOUSE_BUTTON()
//            : state(KeyState::RELEASED)
//            , id(MouseKeyId::UNKNOWN)
//            , mods(ModifierKeyFlag::NONE) {
//        }
//        InputType type() override {
//            return InputType::MOUSE_BUTTON;
//        }
//    };
//    struct Slice_CURSOR_POSITION :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::CURSOR_POSITION>;
//        double x_pos;
//        double y_pos;
//        explicit constexpr Slice_CURSOR_POSITION(double x_pos, double y_pos)
//            : x_pos(x_pos)
//            , y_pos(y_pos) {
//        }
//        constexpr Slice_CURSOR_POSITION() = default;
//        InputType type() override {
//            return InputType::CURSOR_POSITION;
//        }
//    };
//    struct Slice_CURSOR_ENTER :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::CURSOR_ENTER>;
//        MouseWindowState state;
//        explicit constexpr Slice_CURSOR_ENTER(MouseWindowState state) : state(state) {}
//        constexpr Slice_CURSOR_ENTER() = default;
//        InputType type() override {
//            return InputType::CURSOR_ENTER;
//        }
//    };
//    struct SliceSCROLL_MOVE :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::SCROLL_MOVE>;
//        double x_offset;
//        double y_offset;
//        constexpr SliceSCROLL_MOVE() = default;
//        explicit constexpr SliceSCROLL_MOVE(double x_offset, double y_offset)
//            : x_offset(x_offset)
//            , y_offset(y_offset) {
//        }
//        InputType type() override {
//            return InputType::SCROLL_MOVE;
//        }
//    };
//    struct SliceFILE_DROP :public  Slice {
//        using input_type = std::integral_constant<InputType, InputType::FILE_DROP>;
//        int path_count;
//        const char** paths[];
//        constexpr SliceFILE_DROP() = default;
//        constexpr SliceFILE_DROP(int path_count, const char** paths)
//            : path_count(path_count)
//            , paths{ paths } {
//        }
//        InputType type() override {
//            return InputType::FILE_DROP;
//        }
//    };
//    struct SliceJOYSTICK_CONFIG : Slice {
//        using input_type = std::integral_constant<InputType, InputType::JOYSTICK_CONFIG>;
//        JoystickId jid;
//        JoystickConfigState state;
//        constexpr SliceJOYSTICK_CONFIG() = default;
//        constexpr SliceJOYSTICK_CONFIG(JoystickId jid, JoystickConfigState state)
//            : jid(jid)
//            , state(state) {
//        }
//        InputType type() override {
//            return InputType::JOYSTICK_CONFIG;
//        }
//    };
//    //TODO: Add Gamepad slice
//
//    struct SlicePtr {
//        size_t index;
//        gtl::StdMicrosecondsD time_from_last_slice;
//        InputType type;
//        Slice* ptr;
//    };
//
//    class slice_buffer {
//        gtl::Timer slice_timer_;
//        std::vector<SlicePtr> slices_;
//
//    public:
//        std::vector<SlicePtr*> keyboard_key_slices_;
//        std::vector<SlicePtr*> keyboard_char_slices_;
//        std::vector<SlicePtr*> keyboard_modded_char_slices_;
//        std::vector<SlicePtr*> mouse_button_slices_;
//        std::vector<SlicePtr* > mouse_position_slices_;
//        std::vector<SlicePtr*> mouse_enter_slices_;
//        std::vector<SlicePtr*> mouse_scroll_slices_;
//        std::vector<SlicePtr*> file_drop_slices_;
//        std::vector<SlicePtr*> joystick_config_slices_;
//
//    public:
//        void printSizes() const {
//            //std::cout << "Size of slice vectors:" << std::endl;
//
//            if (!keyboard_key_slices_.empty()) {
//                auto slicePtr = dynamic_cast<Slice_keyboard_key*>(keyboard_key_slices_.front()->ptr);
//                if (slicePtr) {
//                    std::cout << "keyboard_key_slices_: " << keyboard_key_slices_.size() << static_cast<int>(slicePtr->id) << std::endl;
//                }
//                else {
//                    std::cout << "keyboard_key_slices_: Dynamic cast failed" << std::endl;
//                }
//            }
//            if (!keyboard_char_slices_.empty())
//                std::cout << "keyboard_char_slices_: " << keyboard_char_slices_.size() << std::endl;
//
//            if (!keyboard_modded_char_slices_.empty())
//                std::cout << "keyboard_modded_char_slices_: " << keyboard_modded_char_slices_.size() << std::endl;
//
//            if (!mouse_button_slices_.empty())
//                std::cout << "mouse_button_slices_: " << mouse_button_slices_.size() << std::endl;
//
//            if (!mouse_position_slices_.empty())
//                std::cout << "mouse_position_slices_: " << mouse_position_slices_.size() << std::endl;
//
//            if (!mouse_enter_slices_.empty())
//                std::cout << "mouse_enter_slices_: " << mouse_enter_slices_.size() << std::endl;
//
//            if (!mouse_scroll_slices_.empty())
//                std::cout << "mouse_scroll_slices_: " << mouse_scroll_slices_.size() << std::endl;
//
//            if (!file_drop_slices_.empty())
//                std::cout << "file_drop_slices_: " << file_drop_slices_.size() << std::endl;
//
//            if (!joystick_config_slices_.empty())
//                std::cout << "joystick_config_slices_: " << joystick_config_slices_.size() << std::endl;
//
//            // Add other vectors if necessary
//        }
//
//        void resetTimer() { slice_timer_.reset(); }
//        void clear() {
//            // Clear the slices_ vector
//            slices_.clear();
//
//            // Clear each vector that stores pointers to UniqueSlicePtr
//            keyboard_key_slices_.clear();
//            keyboard_char_slices_.clear();
//            keyboard_modded_char_slices_.clear();
//            mouse_button_slices_.clear();
//            mouse_position_slices_.clear();
//            mouse_enter_slices_.clear();
//            mouse_scroll_slices_.clear();
//            file_drop_slices_.clear();
//            joystick_config_slices_.clear();
//            // Add other vectors if necessary
//        }
//        template<typename SliceT>
//        void push(SliceT slice) requires gtl::req::DerivedFrom_<SliceT, Slice>{
//            pushSlice(slice);
//        }
//
//        // Retrieve slice by index and type
//        const SlicePtr& get(size_t index, InputType type) {
//            std::vector<SlicePtr*>* target_slices = nullptr;
//
//            switch (type) {
//            case InputType::KEYBOARD_KEY:
//                target_slices = &keyboard_key_slices_;
//                break;
//            case InputType::ENTERED_CHAR:
//                target_slices = &keyboard_char_slices_;
//                break;
//            case InputType::ENTERED_CHAR_WITH_MODS:
//                target_slices = &keyboard_modded_char_slices_;
//                break;
//            case InputType::MOUSE_BUTTON:
//                target_slices = &mouse_button_slices_;
//                break;
//            case InputType::CURSOR_POSITION:
//                target_slices = &mouse_position_slices_;
//                break;
//            case InputType::CURSOR_ENTER:
//                target_slices = &mouse_enter_slices_;
//                break;
//            case InputType::SCROLL_MOVE:
//                target_slices = &mouse_scroll_slices_;
//                break;
//            case InputType::FILE_DROP:
//                target_slices = &file_drop_slices_;
//                break;
//            case InputType::JOYSTICK_CONFIG:
//                target_slices = &joystick_config_slices_;
//                break;
//                // Add other cases for new slice types if necessary
//            }
//
//            if (target_slices) {
//                for (auto& slicePtr : *target_slices) {
//                    if (slicePtr->index == index) {
//                        return *slicePtr;
//                    }
//                }
//            }
//
//            // If the slice is not found, return a default-constructed UniqueSlicePtr
//            static SlicePtr defaultSlice;
//            return defaultSlice;
//        }
//
//    private:
//        // Helper method to store a pointer to UniqueSlicePtr in the appropriate vector
//        SlicePtr& storeAndPush(SlicePtr& slicePtr, std::vector<SlicePtr*>& target_slices) {
//            slices_.push_back(std::move(slicePtr)); // Move the SlicePtr object into the slices vector
//            target_slices.push_back(&slices_.back()); // Get pointer to the new SlicePtr object, store it in target_slices
//            return slices_.back();
//        }
//        template <typename T>
//        void pushSlice(const T & slice) {
//            SlicePtr slicePtr;
//            slicePtr.index = slices_.size();
//            slicePtr.time_from_last_slice = slice_timer_.reset();
//            slicePtr.type = slice.type();
//
//
//            // Check slice type at runtime
//            InputType sliceType = slice.type();
//            // Handle each slice type separately
//            switch (sliceType) {
//            case InputType::KEYBOARD_KEY:
//                storeAndPush(slicePtr, keyboard_key_slices_)  //
//                    .ptr = new Slice_keyboard_key(slice.state, slice,id, slice.mods, slice.scancode);
//                break;
//            case InputType::ENTERED_CHAR:
//                storeAndPush(slicePtr, keyboard_char_slices_);
//                break;
//            case InputType::ENTERED_CHAR_WITH_MODS:
//                storeAndPush(slicePtr, keyboard_modded_char_slices_);
//                break;
//            case InputType::MOUSE_BUTTON:
//                storeAndPush(slicePtr, mouse_button_slices_);
//                break;
//            case InputType::CURSOR_POSITION:
//                storeAndPush(slicePtr, mouse_position_slices_);
//                break;
//            case InputType::CURSOR_ENTER:
//                storeAndPush(slicePtr, mouse_enter_slices_);
//                break;
//            case InputType::SCROLL_MOVE:
//                storeAndPush(slicePtr, mouse_scroll_slices_);
//                break;
//            case InputType::FILE_DROP:
//                storeAndPush(slicePtr, file_drop_slices_);
//                break;
//            case InputType::JOYSTICK_CONFIG:
//                storeAndPush(slicePtr, joystick_config_slices_);
//                break;
//            default:
//                std::cerr << "Error: Unrecognized slice type" << std::endl;
//                delete slicePtr.ptr; // Release memory in case of error
//            }
//        
//        }
//
//    };
//};
////    class slice_pointer_buffer {
////    public:
////        void read_buffer(const slice_buffer& buffer_) {
////            // Read the slice buffer
////            //...1.
////                // For each keyboard key  slice in buffer_.keyboard_key_slices_;
////                // 1. store UniqueSlicePtr* into the matching std::vector<TimedUniqueSlicePtr*>
////                // 2. validate a key was clicked check if this key was previously pressed in 
////                //    this slice_pointer_buffer std::vector<TimedUniqueSlicePtr> keyboard_key_clicked, if so then store it into keyboard_key_clicked
////               // Iterate over the keyboard key slices in the buffer
////            if (!buffer_.keyboard_key_slices_.empty()) {
////                for (auto& slicePtr : buffer_.keyboard_key_slices_) {
////                    auto& slice = *dynamic_cast<Slice_keyboard_key*>(slicePtr->uptr.get());
////
////                    // Check if mods are activated in the keyboard key slice
////                    if (slice.mods != ModifierKeyFlag::NONE) {
////                        // Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                        keyboard_mod_activated.push_back(slicePtr);
////                    }
////
////                    // Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                    switch (slice.state) {
////                    case KeyState::PRESSED:
////                        keyboard_key_pressed.push_back(slicePtr);
////                        break;
////                    case KeyState::RELEASED:
////                        keyboard_key_released.push_back(slicePtr);
////                        break;
////                    case KeyState::REPEATED:
////                        keyboard_key_repeated.push_back(slicePtr);
////                        break;
////                    }
////
////                    // Validate if the key was previously pressed in the keyboard_key_clicked vector
////                    auto it = std::find_if(keyboard_key_clicked.begin(), keyboard_key_clicked.end(), [&](const UniqueSlicePtr* ptr) {
////                        const auto& clickedSlice = dynamic_cast<const Slice_keyboard_key&>(*ptr->uptr);
////                        return clickedSlice.id == slice.id;
////                    });
////
////                    if (it != keyboard_key_clicked.end()) {
////                        keyboard_key_clicked.push_back(slicePtr);
////                    }
////                }
////            }
////            // 2. Iterate over the std::vector<UniqueSlicePtr*> keyboard_char_slices_;
////            for (auto& slicePtr : buffer_.keyboard_char_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                accumulated_text.push_back(slicePtr);
////
////                // 2. (Optional) If needed, you can perform additional processing for keyboard_char_slices_
////                // For example, check if the character is a specific one and take some action
////            }
////
////            // 3. Iterate over the std::vector<UniqueSlicePtr*> keyboard_modded_char_slices_;
////            for (auto& slicePtr : buffer_.keyboard_modded_char_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                modded_accumulated_text.push_back(slicePtr);
////
////                // 2. (Optional) Also push keyboard_modded_char_slices_ into accumulated_text vector
////                accumulated_text.push_back(slicePtr);
////            }
////
////            //4.
////                // For each mouse button  slice in buffer_.mouse_button_slices;
////                // 1. store UniqueSlicePtr* into the matching std::vector<TimedUniqueSlicePtr*>
////                // 2. validate a button was clicked check if this button was previously pressed in 
////                //    this slice_pointer_buffer  if so then store it into mouse button clicked vector
////                       // 4. Iterate over the mouse button slices in the buffer
////            for (auto& slicePtr : buffer_.mouse_button_slices_) {
////                auto& slice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*slicePtr->uptr);
////
////                // Check if mods are activated in the keyboard key slice
////                if (slice.mods != ModifierKeyFlag::NONE) {
////                    // Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                    keyboard_mod_activated.push_back(slicePtr);
////                }
////
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                switch (slice.state) {
////                case KeyState::PRESSED:
////                    mouse_button_pressed.push_back(slicePtr);
////                    break;
////                case KeyState::RELEASED:
////                    mouse_button_released.push_back(slicePtr);
////                    break;
////                case KeyState::REPEATED:
////                    mouse_button_repeated.push_back(slicePtr);
////                    break;
////                }
////
////                // 2. Validate if the button was previously pressed in the mouse_button_clicked vector
////                auto it = std::find_if(mouse_button_clicked.begin(), mouse_button_clicked.end(), [&](const UniqueSlicePtr* ptr) {
////                    const auto& clickedSlice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*ptr->uptr);
////                    return clickedSlice.id == slice.id;
////                });
////
////                if (it != mouse_button_clicked.end()) {
////                    mouse_button_clicked.push_back(slicePtr);
////                }
////            }
////
////            // 5. Iterate over the mouse position slices in the buffer
////            for (auto& slicePtr : buffer_.mouse_position_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                mouse_position_path.push_back(slicePtr);
////            }
////
////            // 6. Iterate over the mouse scroll slices in the buffer
////            for (auto& slicePtr : buffer_.mouse_scroll_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                mouse_scroll_path.push_back(slicePtr);
////            }
////
////            // 7. Iterate over the mouse enter slices in the buffer
////            for (auto& slicePtr : buffer_.mouse_enter_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                mouse_entered_path.push_back(slicePtr);
////            }
////
////
////            // 8. Iterate over the joystick configured slices in the buffer
////            for (auto& slicePtr : buffer_.joystick_config_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                joystick_configured.push_back(slicePtr);
////            }
////
////            // 9. Iterate over the file path slices in the buffer
////            for (auto& slicePtr : buffer_.file_drop_slices_) {
////                // 1. Store UniqueSlicePtr* into the matching std::vector<UniqueSlicePtr*>
////                file_paths_dropped.push_back(slicePtr);
////            }
////        }
////        void clear() {
////            // Keyboard
////            keyboard_key_repeated.clear();
////            keyboard_key_pressed.clear();
////            keyboard_key_released.clear();
////            keyboard_key_clicked.clear();
////
////            accumulated_text.clear();
////            modded_accumulated_text.clear();
////
////            keyboard_mod_activated.clear();
////
////            // Mouse
////            mouse_button_repeated.clear();
////            mouse_button_pressed.clear();
////            mouse_button_released.clear();
////            mouse_button_clicked.clear();
////
////            mouse_position_path.clear();
////            mouse_scroll_path.clear();
////            mouse_entered_path.clear();
////
////            // Joystick
////            joystick_configured.clear();
////
////            // Other
////            file_paths_dropped.clear();
////        }
////        // Keyboard
////        std::vector<UniqueSlicePtr*> keyboard_key_repeated;
////        std::vector<UniqueSlicePtr*> keyboard_key_pressed;
////        std::vector<UniqueSlicePtr*> keyboard_key_released;
////        std::vector<UniqueSlicePtr*> keyboard_key_clicked;
////
////        std::vector<UniqueSlicePtr*> accumulated_text;
////        std::vector<UniqueSlicePtr*> modded_accumulated_text;
////
////        std::vector<UniqueSlicePtr*> keyboard_mod_activated;
////        ///// Mouse
////        std::vector<UniqueSlicePtr*> mouse_button_repeated;
////        std::vector<UniqueSlicePtr*> mouse_button_pressed;
////        std::vector<UniqueSlicePtr*> mouse_button_released;
////        std::vector<UniqueSlicePtr*> mouse_button_clicked;
////
////        std::vector<UniqueSlicePtr*> mouse_position_path;
////        std::vector<UniqueSlicePtr*> mouse_scroll_path;
////        std::vector<UniqueSlicePtr*> mouse_entered_path;
////
////        /// Joystick
////        std::vector<UniqueSlicePtr*> joystick_configured;
////        /// Other
////        std::vector<UniqueSlicePtr*> file_paths_dropped;
////    };
////
////    class Frame {
////        const slice_buffer& buffer;
////        slice_pointer_buffer ptr_buffer;
////    public:
////        State previous_state;
////        State current_state;
////
////        Frame(const slice_buffer& buffer) :buffer(buffer) {}
////        // Update the current state using data from the source buffer.
////        const Frame & update() {
////            // Assume the buffer has been reset and all pointers in the ptr_buffer are now invalid
////            previous_state = current_state;     // Set the previous state to be the current state
////            current_state.reset();              // Reset the current state
////            ptr_buffer.read_buffer(buffer);     // Read the buffer into the ptr buffer
////
////
////            // Query data in the ptr_buffer and buffer to most efficiently update the current state
////// 1. Update the keyboard state
////            for (auto& slicePtr : ptr_buffer.keyboard_key_pressed) {
////                auto& slice = *dynamic_cast<Slice_keyboard_key*>(slicePtr->uptr.get());
////                current_state.keyboard_state.state[KeyboardKeyIdIdxMap[slice.id]] = true;
////                current_state.keyboard_state.pressed_state[KeyboardKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.keyboard_key_released) {
////                auto& slice = dynamic_cast<const Slice_keyboard_key&>(*slicePtr->uptr);
////                current_state.keyboard_state.state[KeyboardKeyIdIdxMap[slice.id]] = false;
////                current_state.keyboard_state.released_state[KeyboardKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.keyboard_key_repeated) {
////                auto& slice = dynamic_cast<const Slice_keyboard_key&>(*slicePtr->uptr);
////                current_state.keyboard_state.repeated_state[KeyboardKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.keyboard_key_clicked) {
////                auto& slice = dynamic_cast<const Slice_keyboard_key&>(*slicePtr->uptr);
////                current_state.keyboard_state.clicked_state[KeyboardKeyIdIdxMap[slice.id]] = true;
////            }
////
////            // 2. Update the mouse state
////            for (auto& slicePtr : ptr_buffer.mouse_button_pressed) {
////                auto& slice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*slicePtr->uptr);
////                current_state.mouse_state.state[MouseKeyIdIdxMap[slice.id]] = true;
////                current_state.mouse_state.pressed_state[MouseKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.mouse_button_released) {
////                auto& slice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*slicePtr->uptr);
////                current_state.mouse_state.state[MouseKeyIdIdxMap[slice.id]] = false;
////                current_state.mouse_state.released_state[MouseKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.mouse_button_repeated) {
////                auto& slice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*slicePtr->uptr);
////                current_state.mouse_state.repeated_state[MouseKeyIdIdxMap[slice.id]] = true;
////            }
////
////            for (auto& slicePtr : ptr_buffer.mouse_button_clicked) {
////                auto& slice = dynamic_cast<const Slice_MOUSE_BUTTON&>(*slicePtr->uptr);
////                current_state.mouse_state.clicked_state[MouseKeyIdIdxMap[slice.id]] = true;
////            }
////            //3. Fill the char_entered vector in the keyboard_state with the accumulated_text from the ptr_buffer
////            // 3. Fill the char_entered vector in the keyboard_state with the accumulated_text from the ptr_buffer
////            for (auto& slicePtr : ptr_buffer.accumulated_text) {
////                auto& slice = dynamic_cast<const SliceENTERED_CHAR&>(*slicePtr->uptr);
////                current_state.keyboard_state.char_entered.push_back(slice.unicode);
////            }
////
////            // 4. Last known position of the mouse from mouse_position_path;
////            if (!ptr_buffer.mouse_position_path.empty()) {
////                auto& lastMousePosSlice = dynamic_cast<const Slice_CURSOR_POSITION&>(*ptr_buffer.mouse_position_path.back()->uptr);
////                current_state.mouse_state.x_position = lastMousePosSlice.x_pos;
////                current_state.mouse_state.y_position = lastMousePosSlice.y_pos;
////            }
////
////            // 5. Scroll wheel offset from mouse_scroll_path
////            if (!ptr_buffer.mouse_scroll_path.empty()) {
////                auto& lastScrollSlice = dynamic_cast<const SliceSCROLL_MOVE&>(*ptr_buffer.mouse_scroll_path.back()->uptr);
////                current_state.mouse_state.x_scroll = lastScrollSlice.x_offset;
////                current_state.mouse_state.y_scroll = lastScrollSlice.y_offset;
////            }
////
////            // 6. True if the mouse is inside a window from mouse_entered_path
////            if (!ptr_buffer.mouse_entered_path.empty()) {
////                auto& lastEnteredSlice = dynamic_cast<const Slice_CURSOR_ENTER&>(*ptr_buffer.mouse_entered_path.back()->uptr);
////                current_state.mouse_state.is_inside = (lastEnteredSlice.state == MouseWindowState::ENTERED);
////            }
////
////            //// 7. Update paths from file_paths_dropped if there are any.
////            //if (!ptr_buffer.file_paths_dropped.empty()) {
////            //    // Iterate over each file drop slice in the buffer
////            //    for (auto& slicePtr : ptr_buffer.file_paths_dropped) {
////            //        auto& slice = dynamic_cast<const SliceFILE_DROP&>(*slicePtr->uptr);
////
////            //        for (int i = 0; i < slice.path_count; ++i) {
////            //            // Assuming words[i] is a null-terminated C-style string
////            //            current_state.paths.emplace_back(slice.paths[i]);
////            //        }
////            //    }
////            //}
////
////// 8. Update the modifier state
////            for (auto& slicePtr : ptr_buffer.keyboard_mod_activated) {
////                auto& slice = dynamic_cast<const Slice_keyboard_key&>(*slicePtr->uptr);
////
////                // Check which modifier key is activated and update the state accordingly
////                switch (slice.mods) {
////                case ModifierKeyFlag::SHIFT:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::SHIFT]] = true;
////                    break;
////                case ModifierKeyFlag::CONTROL:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::CONTROL]] = true;
////                    break;
////                case ModifierKeyFlag::ALT:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::ALT]] = true;
////                    break;
////                case ModifierKeyFlag::SUPER:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::SUPER]] = true;
////                    break;
////                case ModifierKeyFlag::CAPS_LOCK:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::CAPS_LOCK]] = true;
////                    break;
////                case ModifierKeyFlag::NUM_LOCK:
////                    current_state.modifier_state.state[ModifierKeyFlagIdxMap[ModifierKeyFlag::NUM_LOCK]] = true;
////                    break;
////                case ModifierKeyFlag::NONE:
////                    // Do nothing if no modifier key is activated
////                    break;
////                }
////            }
////            return *this;
////            //// Optional: If you also want to handle modded characters, you can iterate over modded_accumulated_text
////            //// and process them in a similar way.
////            //for (auto& slicePtr : ptr_buffer.modded_accumulated_text) {
////            //    auto& slice = dynamic_cast<const SliceENTERED_CHAR_WITH_MODS&>(*slicePtr->uptr);
////            //    current_state.keyboard_state.char_entered.push_back(slice.unicode);
////            //}
////
////        }
////    };
////
////
////    //use with glfw
////    //glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int scancode, int action, int mods) {
////    //    keyboardKeyCallback(w, key, scancode, action, mods, your_slice_buffer);
////    //});
////    // Similarly, set other callbacks using the corresponding lambdas
////
////    enum class KeyEvent : int {
////        PRESSED,
////        RELEASED,
////        REPEATED,
////        CLICKED,
////        FIRED,
////        NONE
////    };
////
////
////    class Events {
////        const Frame & frame;
////    public:
////        Events(const Frame& frame) :frame(frame) {}
////        bool onEvent(KeyboardKeyId key, KeyEvent anevent) {
////            switch (anevent) {
////            case KeyEvent::PRESSED:
////                return frame.current_state.keyboard_state.pressed_state[static_cast<int>(key)];
////            case KeyEvent::RELEASED:
////                return frame.current_state.keyboard_state.released_state[static_cast<int>(key)];
////            case KeyEvent::REPEATED:
////                return frame.current_state.keyboard_state.repeated_state[static_cast<int>(key)];
////            case KeyEvent::CLICKED:
////                return frame.current_state.keyboard_state.clicked_state[static_cast<int>(key)];
////            case KeyEvent::FIRED:
////                return frame.current_state.keyboard_state.fired_state[static_cast<int>(key)];
////                break;
////            case KeyEvent::NONE:
////                // Add logic to handle NONE event if needed
////                if(frame.current_state.keyboard_state.fired_state.none())
////                break;
////            }
////
////            // Default case: return false
////            return false;
////        }
////    };
////
////    // Sample Use
////    // onEvent(Key,Event)
////    // onEvent([KEY_A,PRESSED] && [MOD,SHIFT], dostuff()) // if key a pressed and shift mod is on
////    // onEvent([MOUSE_R,PRESSED], drawMousePath([PATH, N_OF_INDICIES]));
////};
////
