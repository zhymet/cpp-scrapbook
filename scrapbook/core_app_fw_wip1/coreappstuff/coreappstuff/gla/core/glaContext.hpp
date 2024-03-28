#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <vector>
#include "glfwError.hpp"
#include "glaMonitor.hpp"

namespace gla {
    struct ContextHint {
        int id;
        int value;

        enum ID : std::size_t {
            // Window Related attributes
            focused = GLFW_FOCUSED,// indicates whether the specified window has input focus.
            iconified = GLFW_ICONIFIED, // indicates whether the specified window is iconified
            resizable = GLFW_RESIZABLE,
            visible = GLFW_VISIBLE,
            decorated = GLFW_DECORATED,
            auto_iconify = GLFW_AUTO_ICONIFY,
            floating = GLFW_FLOATING,
            maximized = GLFW_MAXIMIZED,
            center_cursor = GLFW_CENTER_CURSOR,
            transparent_framebuffer = GLFW_TRANSPARENT_FRAMEBUFFER,
            hovered = GLFW_HOVERED,
            focus_on_show = GLFW_FOCUS_ON_SHOW,
            scale_to_monitor = GLFW_SCALE_TO_MONITOR,
            // Framebuffer related attributes
            red_bits = GLFW_RED_BITS,
            green_bits = GLFW_GREEN_BITS,
            blue_bits = GLFW_BLUE_BITS,
            alpha_bits = GLFW_ALPHA_BITS,
            depth_bits = GLFW_DEPTH_BITS,
            stencil_bits = GLFW_STENCIL_BITS,
            accum_red_bits = GLFW_ACCUM_RED_BITS,
            accum_green_bits = GLFW_ACCUM_GREEN_BITS,
            accum_blue_bits = GLFW_ACCUM_BLUE_BITS,
            accum_alpha_bits = GLFW_ACCUM_ALPHA_BITS,
            aux_buffers = GLFW_AUX_BUFFERS,
            stereo = GLFW_STEREO,
            samples = GLFW_SAMPLES,
            srgb_capable = GLFW_SRGB_CAPABLE,
            doublebuffer = GLFW_DOUBLEBUFFER,
            // Monitor Related Hints
            refresh_rate = GLFW_REFRESH_RATE,
            // Context related attributes
            client_api = GLFW_CLIENT_API,
            context_creation_api = GLFW_CONTEXT_CREATION_API,
            context_version_major = GLFW_CONTEXT_VERSION_MAJOR,
            context_version_minor = GLFW_CONTEXT_VERSION_MINOR,
            context_revision,
            context_robustness = GLFW_CONTEXT_ROBUSTNESS,
            opengl_forward_compat = GLFW_OPENGL_FORWARD_COMPAT,
            opengl_debug_context = GLFW_OPENGL_DEBUG_CONTEXT,
            profile = GLFW_OPENGL_PROFILE,
            release_behaviour = GLFW_CONTEXT_RELEASE_BEHAVIOR,
            context_no_error = GLFW_CONTEXT_NO_ERROR,
            // MacOs specific attributes
            //cocoa_retina_framebuffer = GLFW_COCOA_RETINA_FRAMEBUFFER,
            //cocoa_frame_name = GLFW_COCOA_FRAME_NAME,
            //cocoa_graphics_switching = GLFW_COCOA_GRAPHICS_SWITCHING,
            // directx11 specific attributes
            //x11_class_name = GLFW_X11_CLASS_NAME,
            //x11_instance_name = GLFW_X11_INSTANCE_NAME,
        };
    };

    class Window {

    };

    class Context {
        std::vector<GLFWwindow*> windows_;
        
        Error makeWindow(int width, int height, const char* name) {
            windows_.push_back(glfwCreateWindow(width, height, name,NULL,NULL));
        }

        std::pair<Error, std::vector<GLFWwindow*>::iterator> makeFullscreenWindow(int width, int height, const char* name,Monitor & monitor) {
            windows_.push_back(glfwCreateWindow(width, height, name, monitor.getGLFWMonitorPointer(), NULL));
            return std::make_pair(Error(),windows_.end()-1);
        }

        //Windowed mode windows can be made full screen by setting a monitor with glfwSetWindowMonitor, 
        //and full screen ones can be made windowed by unsetting it with the same function.
        std::pair<Error, std::vector<GLFWwindow*>::iterator> setWindowFullscreen(std::vector<GLFWwindow*>::iterator it, int width, int height, int refreshrate, Monitor& monitor) {
            glfwSetWindowMonitor(*it,monitor.getGLFWMonitorPointer(),0,0,width,height,refreshrate);
        }

        std::pair<Error, std::vector<GLFWwindow*>::iterator> setWindowFullscreen(std::vector<GLFWwindow*>::iterator it, int width, int height, int refreshrate, Monitor& monitor) {
            const auto & mode = monitor.getCurrentVideoMode();
            glfwWindowHint(GLFW_RED_BITS, mode.redBits);
            glfwWindowHint(GLFW_GREEN_BITS, mode.greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, mode.blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, mode.refreshRate);
            glfwSetWindowMonitor(*it, monitor.getGLFWMonitorPointer(), 0, 0, mode.width, mode.height, mode.refreshRate);
        }
    };
}