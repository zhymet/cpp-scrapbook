#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <string_view>
#include <unordered_map>

namespace gla {
    // GLFW Error Handling
    // The last error code for the calling thread can be queried at any time with glfwGetError.
    // If no error has occurred since the last call, GLFW_NO_ERROR (zero) is returned. The error is cleared before the function returns.
    // GLFW often has more information about an error than its general category. You can retrieve a UTF-8 encoded human-readable description along with the error code.
    // If no error has occurred since the last call, the description is set to NULL.
    /*
    Reported errors are never fatal.
    As long as GLFW was successfully initialized, it will remain initialized and in a safe state until terminated regardless of how many errors occur.
    If an error occurs during initialization that causes glfwInit to fail, any part of the library that was initialized will be safely terminated.
    */

    enum class ErrorCode : int {
        no_error = GLFW_NO_ERROR, //No error has occurred
        not_initialized = GLFW_NOT_INITIALIZED, //GLFW has not been initialized.
        no_current_context = GLFW_NO_CURRENT_CONTEXT, //No context is current for this thread
        invalid_enum = GLFW_INVALID_ENUM, //One of the arguments to the function was an invalid enum value.More...
        invalid_value = GLFW_INVALID_VALUE,// One of the arguments to the function was an invalid value. 
        out_of_memory = GLFW_OUT_OF_MEMORY, // 	A memory allocation failed
        api_unavailable = GLFW_API_UNAVAILABLE, // GLFW could not find support for the requested API on the system. 
        version_unavailable = GLFW_VERSION_UNAVAILABLE,// 	The requested OpenGL or OpenGL ES version is not available.
        platform_error = GLFW_PLATFORM_ERROR,// 	A platform-specific error occurred that does not match any of the more specific categories.
        format_unavailable = GLFW_FORMAT_UNAVAILABLE, // The requested format is not supported or available
        no_window_context = GLFW_NO_WINDOW_CONTEXT, // The specified window does not have an OpenGL or OpenGL ES context. 
        failed_glew_init = 100000,
    };

    struct Error {
    private:
        const char* what_;
        ErrorCode code_;

    public:
        Error() {
            code_ = static_cast<ErrorCode>(glfwGetError(&what_));
        }

        Error(ErrorCode code, const char * what) {
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
    };
}