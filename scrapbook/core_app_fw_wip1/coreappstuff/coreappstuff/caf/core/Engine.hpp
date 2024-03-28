#pragma once

#include "../external.hpp" // glfw
#include "Code.hpp" // cafCode
#include "memory" // unique_ptr

namespace caf {

    struct Engine {
        static cafCode init(unsigned gl_vers_major = 0, unsigned gl_vers_minor = 0);
        static void terminate();
        static bool is_init();
    //    //cafCode::Error run();
    //private:
    //    //bool is_running_;
    //    //std::unique_ptr<EngineLoop> current_loop_;
    };
}
