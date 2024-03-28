#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <exception>
#include <charconv>
#include <array>
#include <sstream>

namespace gla {
	/* Typedefs */
	using Window = GLFWwindow;
	using Monitor = GLFWmonitor;

	/* Exceptions */
	struct GLFWInitFailureEXC : public std::exception {
		const char* what() {
			return "gla failed to initialize GLFW.";
		}
	};

	struct WindowNoGLFWInitFailureEXC : public std::exception {
		const char* what() {
			return "Attempting to create GLFWWindow before GLFW is initialized. "
				"Make sure to call gla::glfw::init().";
		}
	};

	struct WindowNullWindowPtrEXC : public std::exception {
		const char* what() {
			return "Attempting to make a null window the current context.";
		}
	};

	struct GlewInitEXC : public std::exception {
		const char* exc_str_;
		std::string str_;
		explicit GlewInitEXC(GLenum glew_error, Window* window)
			: std::exception() {
			std::stringstream temp_sstr;
			str_ = "Failed to init GLEW for the current window's OpenGl context. cafWindow: " + std::to_string((unsigned long long)(void*)(window))
				+ "GLEW Error Number:" + std::to_string(glew_error);
			str_ = temp_sstr.str();
			exc_str_ = str_.c_str(); // C26815
		}

		const char* what() {
			return exc_str_;
		}
	};

	/* Methods: Library Initialization/Termination and check. */
	namespace detail {
		static bool* GLFW_INIT = nullptr;
		static bool* GLEW_INIT = nullptr;
	}

	static inline bool initGLFW() {
		if (!glfwInit()) {
			detail::GLFW_INIT = new bool(false);
			throw GLFWInitFailureEXC(); // Attempted to initalize but failed.
		}
		detail::GLFW_INIT = new bool(true);
		return true; // Successful initalization.
	}

	static inline bool initGlew(Window* current_context) {
		glewExperimental = true; // Needed in core profile
		GLenum err = glewInit();
		if (err != GL_NONE) {
			detail::GLFW_INIT = new bool(false);
			throw GlewInitEXC(err, current_context);
		}
		detail::GLFW_INIT = new bool(true);
		return true;
	}

	static inline bool terminate() {
		if (detail::GLFW_INIT != nullptr) { // GLFW been initialized(or attempted to) ? Terminate it.
			glfwTerminate();
			detail::GLFW_INIT = nullptr;
			return true;
		}
		else
			return false; // Cannot terminate , glfw never initialized.
	}

	static inline bool isGLEWInit() {
		return detail::GLEW_INIT != nullptr // Initialization attempt occured
			&& *detail::GLEW_INIT; // Initialization was successful.
	}

	static inline bool isGLFWInit() {
		return detail::GLFW_INIT != nullptr // Initialization attempt occured
			&& *detail::GLFW_INIT; // Initialization was successful.
	}


	static inline Window* createWindow(int width, int height, const char* title, Monitor* monitor, Window* share) {
		if (!isGLFWInit()) 
			throw WindowNoGLFWInitFailureEXC();
		else
			return glfwCreateWindow(width, height, title, monitor, share);
	}

	static inline Monitor* getPrimaryMonitor() {
		glfwGetPrimaryMonitor();
	};

	static inline void destroyWindow(Window* window) {
		glfwDestroyWindow(window);
	};

	static inline void makeContextCurrent(Window* window) {
		if (!window)
			throw WindowNullWindowPtrEXC();
		else
			glfwMakeContextCurrent(window);
	}

	static inline void setDefaultWindowHints() {
		glfwDefaultWindowHints();
	}
}
