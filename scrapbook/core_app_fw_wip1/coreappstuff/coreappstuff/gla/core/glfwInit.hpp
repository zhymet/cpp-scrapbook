#pragma once
#include <vector>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "glfwError.hpp"

#include <tuple>
namespace gla{
    struct InitHint {
        int id;
        int value;
        enum class ID { // All default to true
            joystick_hat_buttons = GLFW_JOYSTICK_HAT_BUTTONS, //  specifies whether to also expose joystick hats as buttons, for compatibility with earlier versions of GLFW that did not have glfwGetJoystickHats. 
            cocoa_chdir_resources = GLFW_COCOA_CHDIR_RESOURCES, // MACOS, specifies whether to set the current directory to the application to the Contents/Resources subdirectory of the application's bundle, if present. 
            cocoa_menubar = GLFW_COCOA_MENUBAR // MACOS , specifies whether to create a basic menu bar, either from a nib or manually, when the first window is created, which is when AppKit is initialized.
        };
    };

    // Returns the version of GLFW
    static std::tuple<int, int, int> glfw_version() {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        return std::make_tuple(major, minor, rev);
    }

    static inline const char* glfw_version_string() {
        return glfwGetVersionString();
    }

    static Error init(unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0) {
        // 1. Initialize GLFW library
        if (glfwInit()) {
            // Initialize GLEW
            // Create 'dummy' Window to provide an OpenGL context for GLEW
            // Assume future OpenGL contexts use the same GPU hardware during the lifetime of this program.
            GLFWwindow* temp_window;
            glfwDefaultWindowHints();// Defaults to latest OpenGL Version Available.
            if (gl_vers_major != 0) { // If version was specified use that OpenGL instead.
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_vers_major);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_vers_minor);
            }
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
            temp_window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
            if (!temp_window) { // Window returns nullptr if creation failed.
                glfwTerminate();
                return Error(); // Failed to create window
            }

            glfwMakeContextCurrent(temp_window); // GLFW context must be current for GLEW to the detect the OpenGL context
            glewExperimental = true; // Needed in core profile
            GLenum glew_err = glewInit();
            if (glew_err != GL_NONE) {
                return Error(ErrorCode::failed_glew_init, "Failed to initialize glew with glew error code: " + glew_err);
            }

            // Clean up dummy window
            glfwDestroyWindow(temp_window);

            // Init successful
            return Error(ErrorCode::no_error, nullptr);
        }
    }

    static Error init(const std::vector<InitHint>& hints, unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0) {
        for (auto hint : hints) {
            glfwInitHint(hint.id, hint.value);
        }
        return init(gl_vers_major, gl_vers_minor);
    }
}