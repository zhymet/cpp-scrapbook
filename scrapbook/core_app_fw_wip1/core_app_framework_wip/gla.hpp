#pragma once

#include "external.hpp"

// Include STD
#include <vector>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <bitset>
#include <tuple>
#include <memory>

// Include GTL
#include "vec2.hpp"
#include "timer.hpp"

#include "gla_event.hpp"
//#include "gla_globject.hpp"

namespace gla {
    /* 
    * Library: GLA - Graphics Layer Access
    * Purpose: Provide a C++17 style interface to GLFW and OPENGL to build applications in modern C++ style
    */
    
    /*
    * Method: glfw_version()
    * Returns: std::tuple<int, int, int>
    * Purpose: Returns the version of GLFW
    */
    inline std::tuple<int, int, int> glfw_version() {
        int major, minor, rev;
        glfwGetVersion(&major, &minor, &rev);
        return std::make_tuple(major, minor, rev);
    }

    /*
    * Method: glfw_version()
    * Returns: const char*
    * Purpose: Returns the string version of GLFW
    */
    inline const char* glfw_version_string() {
        return glfwGetVersionString();
    }

    // GLFW Error Handling
    // The last error code for the calling thread can be queried at any time with glfwGetError.
    // If no error has occurred since the last call, GLFW_NO_ERROR (zero) is returned. The error is cleared before the function returns.
    // GLFW often has more information about an error than its general category. 
    // You can retrieve a UTF-8 encoded human-readable description along with the error code.
    // If no error has occurred since the last call, the description is set to NULL.
    // Reported errors are never fatal.
    // As long as GLFW was successfully initialized, it will remain initialized and in a safe state until terminated regardless of how many errors occur.
    // If an error occurs during initialization that causes glfwInit to fail, any part of the library that was initialized will be safely terminated.
    enum class ErrorCode : int {
        no_error = GLFW_NO_ERROR,                       //No error has occurred
        not_initialized = GLFW_NOT_INITIALIZED,         //GLFW has not been initialized.
        no_current_context = GLFW_NO_CURRENT_CONTEXT,   //No context is current for this thread
        invalid_enum = GLFW_INVALID_ENUM,               //One of the arguments to the function was an invalid enum value.More...
        invalid_value = GLFW_INVALID_VALUE,             // One of the arguments to the function was an invalid value. 
        out_of_memory = GLFW_OUT_OF_MEMORY,             // 	A memory allocation failed
        api_unavailable = GLFW_API_UNAVAILABLE,         // GLFW could not find support for the requested API on the system. 
        version_unavailable = GLFW_VERSION_UNAVAILABLE, // 	The requested OpenGL or OpenGL ES version is not available.
        platform_error = GLFW_PLATFORM_ERROR,           // 	A platform-specific error occurred that does not match any of the more specific categories.
        format_unavailable = GLFW_FORMAT_UNAVAILABLE,   // The requested format is not supported or available
        no_window_context = GLFW_NO_WINDOW_CONTEXT,      // The specified window does not have an OpenGL or OpenGL ES context. 
        failed_glew_init = 0x0001000B,
    };

    struct Error {
    private:
        const char * what_;
        ErrorCode code_;

    public:
        Error() {
            code_ = static_cast<ErrorCode>(glfwGetError(&what_));
            if (code_ == ErrorCode::no_error)
                what_ = "";
        }

        Error(ErrorCode code, const char* what) {
            code_ = code;
            what_ = what;
        }

        Error(ErrorCode code) {
            code_ = code;
            what_ = "";
        }

        const auto& what() {
            return what_;
        }

        const auto& code() {
            return code_;
        }

        explicit operator bool() const
        {
            if (code_ == ErrorCode::no_error)
                return true;
            else
                return false;
        }
    };// class Error

    struct InitHint {
        int id;
        int value;
        enum class ID { // All default to true
            joystick_hat_buttons = GLFW_JOYSTICK_HAT_BUTTONS, //  specifies whether to also expose joystick hats as buttons, for compatibility with earlier versions of GLFW that did not have glfwGetJoystickHats. 
            cocoa_chdir_resources = GLFW_COCOA_CHDIR_RESOURCES, // MACOS, specifies whether to set the current directory to the application to the Contents/Resources subdirectory of the application's bundle, if present. 
            cocoa_menubar = GLFW_COCOA_MENUBAR // MACOS , specifies whether to create a basic menu bar, either from a nib or manually, when the first window is created, which is when AppKit is initialized.
        };
    };

    struct ContextHint {
        int id;
        int value;

        enum ID : int {
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

    static Error init(unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0) {
        // 1. Initialize GLFW library
        if (glfwInit()) {
            // Initialize GLEW
            // Create 'dummy' Window to provide an OpenGL context for GLEW
            // Assume future OpenGL contexts use the same GPU hardware during the lifetime of this program.
            GLFWwindow* temp_window;             ///glfwDefaultWindowHints();// Defaults to latest OpenGL Version Available. MAXIMUM 2.1 ??? WRONG!
            if (gl_vers_major != 0) { // If version was specified use that OpenGL instead. 
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_vers_major);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_vers_minor);
                if (gl_vers_major >= 3 && gl_vers_minor >= 2) { // Use core if specified Gl over 3.2
                    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
                }
            }
            else { // Default to 3.2 (Minimum for Core Profile)
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
            }

            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

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
            return Error(ErrorCode::no_error, "glfw and glew initialized succesfully!");
        } // end if (glfwInit())
        else {
            glfwTerminate();
            return Error();
        }
    } // end static Error init(unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0)

    static Error init(const std::vector<InitHint>& hints, unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0) {
        for (auto hint : hints) {
            glfwInitHint(hint.id, hint.value);
        }
        return init(gl_vers_major, gl_vers_minor);
    }

    static Error terminate(){
        glfwTerminate();
        return Error(ErrorCode::no_error, "");
    };

    class Monitor {
        GLFWmonitor* monitor_ptr_;
    public:

        Monitor(GLFWmonitor* glfwmonitor) {
            monitor_ptr_ = glfwmonitor;
        }
        gtl::vec2<int> getPhysicalSize(); // Physical size of monitor in milimeters (estimatted) no relation to current resolution.
        gtl::vec2<float> getMonitorContentScale();  // Ratio between the current DPI and the platform's default DPI.
                                                    // may depend on both the monitor resolution and pixel density and on user settings. 
        gtl::vec2<int> getVirtualPosition(); // position of the monitor on the virtual desktop, in screen coordinates
        gtl::vec2<gtl::vec2<int>> getWorkArea(); // area of a monitor not occupied by global task bars or menu bars, in screen coordinates
        std::string_view getStringName(); // The human-readable, UTF-8 encoded name of a monitor. Monitor names are not guaranteed to be unique.
        const GLFWvidmode& getCurrentVideoMode();
        std::vector<const GLFWvidmode&> getAvailVideoModes();
        void setGamma(float gamma);
        void setGammaRamp(const GLFWgammaramp& gamma_ramp);
        const GLFWgammaramp& getGammaRamp();


        void setMonitorSource(GLFWmonitor* monitor_ptr) {
            monitor_ptr_ = monitor_ptr;
        }

        GLFWmonitor* getGLFWMonitorPointer() const {
            return monitor_ptr_;
        }
    };

    class Viewport {
        static std::vector<Monitor>::iterator primary_monitor_;
        static std::vector<Monitor> monitors_;

        static void glfw_monitor_callback(GLFWmonitor* monitor, int event) {
            if (event == GLFW_CONNECTED)
            {
                // A monitor was connected, add it to vector if it does not already exist
                auto it = std::find_if(monitors_.begin(), monitors_.end(), [monitor](auto& a) {return a.getGLFWMonitorPointer() == monitor; });
                if (it == monitors_.end()) {
                    monitors_.push_back(monitor);
                }
                // Reset primary monitor
                auto p_monitor = glfwGetPrimaryMonitor();
                primary_monitor_ = std::find_if(monitors_.begin(), monitors_.end(), [p_monitor](auto& a) {return a.getGLFWMonitorPointer() == p_monitor; });
            }
            else if (event == GLFW_DISCONNECTED)
            {
                // A monitor was disconnected
                // Find the monitor index and remove it from monitor vector
                monitors_.erase(std::find_if(monitors_.begin(), monitors_.end(), [monitor](auto& a) {return a.getGLFWMonitorPointer() == monitor; }));
            }
        }

        Viewport() {
            int count;
            GLFWmonitor** temp_monitors_ptr = glfwGetMonitors(&count); // The primary monitor is always the first monitor in the returned array, 
            for (int i = 0; i < count; i++) { // but other monitors may be moved to a different index when a monitor is connected or disconnected.
                monitors_[i].setMonitorSource(temp_monitors_ptr[i]);
            }
            primary_monitor_ = monitors_.begin();
        }
    };

    class Subcontext {
        GLFWwindow* winptr_;
    public:
        //Creation/Destruction
        Subcontext() {};
        Error   init(const std::vector<ContextHint>& hints = std::vector<ContextHint>(), int width = 0, int height = 0
            , const char* title = "", Monitor* monitor = nullptr, Subcontext* shared_subcontext = nullptr);
        Error   terminate();
        void makeCurrent();
        GLFWwindow* getGLFWWinPtr();
    protected:
     //   GLFWwindow* getGLFWWinPtr();
        void    setUserPointer(void* pointer);
        void* getUserPointer();
    public:
        //Properties
        int     getHintVal(ContextHint::ID hint);
        void    setHintVal(ContextHint::ID hint, int val);
        void    defaultHints(void);
        //void 	glfwWindowHintString(int hint, const char* value);
        bool    isShouldClose();
        void 	setShouldClose(bool val);
        void    setTitle(const char* title);
        void 	setIcon(int count, const GLFWimage* images);
        gtl::vec2<int> 	getPosition();
        void 	setPosition(int xpos, int ypos);
        gtl::vec2<int> 	getSize();
        void 	setSize(int xpos, int ypos);
        void 	setSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight);
        void 	setAspectRatio(int numer, int denom);
        gtl::vec2<int> 	getFramebufferSize();
        gtl::vec2<gtl::vec2<int>> 	getFrameSize();
        gtl::vec2<float> 	getContentScale();
        float	getOpacity();
        void 	setOpacity(float opacity);
        void 	iconify();
        void 	restore();
        void 	maximize();
        void 	show();
        void 	hide();
        void 	focus();
        void 	requestAttention();
        GLFWmonitor* getMonitor();
        void 	setMonitor(GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
    };

    class Context {
        std::vector<Subcontext> subcontexts_;
    public:
        Error makeWindow(int width, int height, const char* name) {
            subcontexts_.push_back(Subcontext());
            subcontexts_.back().init(std::vector<ContextHint>(), width, height, name, nullptr, nullptr);
            return Error();
        }
    };


    //    std::pair<Error, std::vector<GLFWwindow*>::iterator> makeFullscreenWindow(int width, int height, const char* name, Monitor& monitor) {
    //        subcontexts_.push_back(glfwCreateWindow(width, height, name, monitor.getGLFWMonitorPointer(), NULL));
    //        return std::make_pair(Error(), subcontexts_.end() - 1);
    //    }

    //    //Windowed mode windows can be made full screen by setting a monitor with glfwSetWindowMonitor, 
    //    //and full screen ones can be made windowed by unsetting it with the same function.
    //    std::pair<Error, std::vector<GLFWwindow*>::iterator> setWindowFullscreen(std::vector<GLFWwindow*>::iterator it, int width, int height, int refreshrate, Monitor& monitor) {
    //        glfwSetWindowMonitor(*it, monitor.getGLFWMonitorPointer(), 0, 0, width, height, refreshrate);
    //    }

    //    std::pair<Error, std::vector<GLFWwindow*>::iterator> setWindowedFullscreen(std::vector<GLFWwindow*>::iterator it, int width, int height, int refreshrate, Monitor& monitor) {
    //        const auto& mode = monitor.getCurrentVideoMode();
    //        glfwWindowHint(GLFW_RED_BITS, mode.redBits);
    //        glfwWindowHint(GLFW_GREEN_BITS, mode.greenBits);
    //        glfwWindowHint(GLFW_BLUE_BITS, mode.blueBits);
    //        glfwWindowHint(GLFW_REFRESH_RATE, mode.refreshRate);
    //        glfwSetWindowMonitor(*it, monitor.getGLFWMonitorPointer(), 0, 0, mode.width, mode.height, mode.refreshRate);
    //    }
    //};


} // namespace gla