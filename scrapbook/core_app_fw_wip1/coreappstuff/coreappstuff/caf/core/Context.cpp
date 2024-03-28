#include "Context.hpp"

/*
Returns true if the window is currently focused.
By default, newly created windows are given input focus.
You can change this behavior by setting the FOCUSED window hint before creating the window.
*/
bool isFocused() {
    return glfwGetWindowAttrib(window_.get(), GLFW_FOCUSED);
}

/*
//Indicates whether the specified window is iconified.
//*/
//bool isIconified() {
//    return glfwGetWindowAttrib(window_.get(), GLFW_FOCUSED);
//}
//
///*
//Indicates whether the specified window is iconified.
//*/
//bool isVisible() {
//    return glfwGetWindowAttrib(window_.get(), GLFW_VISIBLE);
//}