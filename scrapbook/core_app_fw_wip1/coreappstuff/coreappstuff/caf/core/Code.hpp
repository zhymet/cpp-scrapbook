//
// Created by zbook15 on 9/23/2020.
//

#ifndef NTONESDK_CODE_HPP
#define NTONESDK_CODE_HPP
#include <string_view>
namespace caf {
    struct cafCode {
        enum class Error : int {
            NONE,
            FATAL,
            GLFW_INIT_FAILURE,
            GLEW_INIT_FAILURE,
            GLFW_NULL_WIN_PTR
        };
    private:
        std::string_view what_;
        Error code_;
    public:
        cafCode(Error err) {
            code_ = err;
        }

        cafCode(Error err, std::string_view what) {
            code_ = err;
            what_ = what;
        }

        const auto & what() {
            return what_.data();
        }

        const auto& code() {
            return code_;
        }

        explicit operator bool() const
        {
            if (code_ == Error::NONE)
                return true;
            else
                return false;
        }
    };
}
#endif //NTONESDK_CODE_HPP
