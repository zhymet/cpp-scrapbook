//
// Created by zbook15 on 9/23/2020.
//

#ifndef NTONESDK_WINDOW_HPP
#define NTONESDK_WINDOW_HPP

#include <stdexcept>
#include <exception>
#include <charconv>
#include <vector>
#include <array>
#include <sstream>

#include "Code.hpp"
#include "Engine.hpp"
#include <memory>

namespace caf {

    struct ContextHint {
        int id;
        int value;

        enum ID : std::size_t {
            FOCUSED = 0x00020001,

            // GLFW_ICONIFIED indicates whether the specified window is iconified.
            ICONIFIED = 0x00020002,

            // GLFW_RESIZABLE indicates whether the specified window is resizable by the user. 
            // This can be set before creation with the GLFW_RESIZABLE window hint or after with glfwSetWindowAttrib.
            RESIZABLE = 0x00020003,

            VISIBLE = 0x00020004,
            DECORATED,
            AUTO_ICONIFY,
            FLOATING,
            MAXIMIZED,
            CENTER_CURSOR,
            TRANSPARENT_FRAMEBUFFER,
            HOVERED,
            FOCUS_ON_SHOW,
            RED_BITS,
            GREEN_BITS,
            BLUE_BITS,
            ALPHA_BITS,
            DEPTH_BITS,
            STENCIL_BITS,
            ACCUM_RED_BITS,
            ACCUM_GREEN_BITS,
            ACCUM_BLUE_BITS,
            ACCUM_ALPHA_BITS,
            AUX_BUFFERS,
            STEREO,
            SAMPLES,
            SRGB_CAPABLE,
            REFRESH_RATE,
            DOUBLEBUFFER,
            CLIENT_API,
            CONTEXT_VERSION_MAJOR,
            CONTEXT_VERSION_MINOR,
            CONTEXT_REVISION,
            CONTEXT_ROBUSTNESS,
            OPENGL_FORWARD_COMPAT,
            OPENGL_DEBUG_CONTEXT,
            PROFILE,
            RELEASE_BEHAVIOUR,
            CONTEXT_NO_ERROR,
            CONTEXT_CREATION_API,
            SCALE_TO_MONITOR,
            COCOA_RETINA_FRAMEBUFFER,
            COCOA_FRAME_NAME,
            COCOA_GRAPHICS_SWITCHING,
            X11_CLASS_NAME,
            X11_INSTANCE_NAME,
        };
    };

    //class ContextParameters {

    //    // GLFW_FOCUSED : Specifies whether the windowed mode window will be given input focus when created.
    //    // Possible values are GLFW_TRUE and GLFW_FALSE. This hint is ignored for full screen and initially hidden windows.
    //    //bool is_focused() { glfwGetWindowAttrib(window, GLFW_FOCUSED) };
    //    bool is_resizable;
    //    bool is_visible;
    //    bool is_decorated;
    //    bool auto_iconify;
    //    bool is_floating;
    //    bool is_maximized;
    //    bool center_cursor;
    //    bool transparent_framebuffer;
    //    bool focus_on_show;
    //    bool scale_to_monitor;
    //    bool is_hovered;
    //    bool focus_on_show;
    //    int red_bits;
    //    int green_bits;
    //    int blue_bits;
    //    int alpha_bits;
    //    int depth_bits;
    //    int stencil_bits;
    //    int accum_red_bits;
    //    int accum_green_bits;
    //    int accum_blue_bits;
    //    int accum_alpha_bits;
    //    int aux_buffers;
    //    int is_stereo;
    //    int n_samples;
    //    bool is_srgb_capable;
    //    int referesh_rate;
    //    bool is_double_buffer;
    //    int client_api;
    //    int context_version_major;
    //    int context_version_minor;
    //    int context_revision;
    //    int context_robustness;
    //    bool opengl_forward_compatible;
    //    bool opengl_debug_context;
    //    bool is_profile;
    //    bool release_behaviour;
    //    bool context_no_error;
    //};

    class Context {

    public:
        Context(int width, int height, const char* name, const std::vector<ContextHint>& hints);
        Context(int width, int height, const char* name);
        cafCode::Error makeCurrent();
        bool shouldClose();
    private:
        std::unique_ptr<gla::Window> window_;
    public:
        bool isResizable();
        bool isIconified();
        bool isVisible();
        bool isDecorated();
        bool isFocused();
        bool isAutoIconify();
        bool isFloating();
        bool isMaximized();
        bool isCursorCentered();
        bool isFramebufferTransparent();
        bool isFocusOnShow();
        bool isScaleToMonitor();
        bool isStereo();
        bool isSRGBCapable();
        bool isDoublebuffer();
        bool isOpenGlForwardCompat();
        bool isOpenGlDebugContext();

        int nRedBits();
        int nGreenBits();
        int nBlueBits();
        int nAlphaBits();
        int nDepthBits();
        int nStencilBits();
        int nAccumRedBits();
        int nAccumBlueBits();
        int nAccumAlphaBits();
        int nAuxBuffers();
        int nSamples();
        int refreshRate();

        int contextClientApi();
        int contextCreationApi();
        int openGlVersionMajor();
        int openGlVersionMinor();
        int openGlProfile();
        int contextRobustness();
        int contextReleaseBehaviour();
    };
}

#endif //NTONESDK_WINDOW_HPP
