
#include "Engine.hpp"

namespace caf {
    // Method: init
    // Purpose: Initialize all library dependencies. (GLFW, GLEW )
    cafCode Engine::init(unsigned gl_vers_major /*= 0*/,unsigned gl_vers_minor/* = 0*/) {
        // 1. Initialize GLFW and GLEW library
        gla::init();

        return cafCode(cafCode::Error::NONE); // Init Successful
    }

    void Engine::terminate() {
        gla::terminate();
    }

    bool Engine::is_init() {
        return gla::isGLFWInit() && gla::isGLEWInit();
    }

    //cafCode::Error cafEngine::run() {
    //    is_running_ = true;
    //    while (current_loop_->start())
    //        current_loop_->finish();
    //    is_running_ = false;
    //    return cafCode::Error::NONE;
    //}

}
