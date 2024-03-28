#include "gla.hpp"
namespace gla {

	// Class: Subcontext
	// 
	// Construction & Destruction
	// Method: init
	Error	Subcontext::init(const std::vector<ContextHint>& hints, int width, int height
		, const char* title, Monitor* monitor, Subcontext* shared_subcontext) {
		glfwDefaultWindowHints();
		for (const auto& hint : hints) {
			glfwWindowHint(hint.id, hint.value);
		}

		GLFWwindow* glfw_shared_win_ptr = nullptr;
		GLFWmonitor* glfw_monitor_ptr = nullptr;
		if (shared_subcontext) {
			glfw_shared_win_ptr = shared_subcontext->getGLFWWinPtr();
		}
		if (monitor) {
			glfw_monitor_ptr = monitor->getGLFWMonitorPointer();
		}
		winptr_ = glfwCreateWindow(width, height, title, glfw_monitor_ptr, glfw_shared_win_ptr);
		return Error();
	}
	//Method:terminate
	Error	Subcontext::terminate() {
		glfwDestroyWindow(winptr_);
		return Error();
	}

	// Protected
	GLFWwindow* Subcontext::getGLFWWinPtr() {
		return winptr_;
	}
	void    Subcontext::setUserPointer(void* pointer) { glfwSetWindowUserPointer(winptr_, pointer); };
	void* Subcontext::getUserPointer() { return glfwGetWindowUserPointer(winptr_); };

	// Temp
	void Subcontext::makeCurrent() { glfwMakeContextCurrent(winptr_); }
	// Getters
	int		Subcontext::getHintVal(ContextHint::ID hint) { return glfwGetWindowAttrib(winptr_, hint); }
	bool	Subcontext::isShouldClose() { return glfwWindowShouldClose(winptr_); }
	gtl::vec2<int> 	Subcontext::getPosition() {
		gtl::vec2<int> pos;
		glfwGetWindowPos(winptr_, &pos.x, &pos.y);
		return pos;
	};
	gtl::vec2<int> 	Subcontext::getSize() {
		gtl::vec2<int> size;
		glfwGetWindowSize(winptr_, &size.x, &size.y);
		return size;
	};
	gtl::vec2<int> 	Subcontext::getFramebufferSize() {
		gtl::vec2<int> size;
		glfwGetFramebufferSize(winptr_, &size.x, &size.y);
		return size;
	}
	gtl::vec2<gtl::vec2<int>> 	Subcontext::getFrameSize() {
		gtl::vec2<gtl::vec2<int>> size; // int* left, int* top, int* right, int* bottom
		glfwGetWindowFrameSize(winptr_, &size.x.x, &size.x.y, &size.y.x, &size.y.y);
		return size;
	}
	gtl::vec2<float> 	Subcontext::getContentScale() {
		gtl::vec2<float> scale;
		glfwGetWindowContentScale(winptr_, &scale.x, &scale.y);
		return scale;
	}
	float	Subcontext::getOpacity() {
		return glfwGetWindowOpacity(winptr_);
	}
	GLFWmonitor* 	Subcontext::getMonitor() {
		return glfwGetWindowMonitor(winptr_);
	}

	// Setters
	void	Subcontext::setHintVal(ContextHint::ID hint, int val) { glfwSetWindowAttrib(winptr_, hint, val); }
	void	Subcontext::setShouldClose(bool val) { glfwSetWindowShouldClose(winptr_, val); }
	void	Subcontext::setTitle(const char* title) { glfwSetWindowTitle(winptr_, title); };
	void	Subcontext::setIcon(int count, const GLFWimage* images) {
		glfwSetWindowIcon(winptr_, count, images);
	}
	void 	Subcontext::setPosition(int xpos, int ypos) {
		return glfwSetWindowPos(winptr_, xpos, ypos);
	}
	void 	Subcontext::setSize(int x, int y) {
		return glfwSetWindowSize(winptr_, x, y);
	}
	void 	Subcontext::setSizeLimits(int minwidth, int minheight, int maxwidth, int maxheight) {
		glfwSetWindowSizeLimits(winptr_, minwidth, minheight, maxwidth, maxheight);
	}
	void 	Subcontext::setAspectRatio(int numer, int denom) {
		glfwSetWindowAspectRatio(winptr_, numer, denom);
	}
	void 	Subcontext::setOpacity(float opacity) {
		glfwSetWindowOpacity(winptr_, opacity);
	}
	void 	Subcontext::setMonitor(GLFWmonitor* monitor, int xpos, int ypos, int width, int height, int refreshRate) {

	};

	// Modifiers
	void	Subcontext::defaultHints(void) { glfwDefaultWindowHints(); }
	void 	Subcontext::iconify() {
		glfwIconifyWindow(winptr_);
	}
	void 	Subcontext::restore() {
		glfwRestoreWindow(winptr_);
	}
	void 	Subcontext::maximize() {
		glfwMaximizeWindow(winptr_);
	}
	void 	Subcontext::show() {
		glfwShowWindow(winptr_);
	}
	void 	Subcontext::hide() {
		glfwHideWindow(winptr_);
	}
	void 	Subcontext::focus() {
		glfwFocusWindow(winptr_);
	}
	void 	Subcontext::requestAttention() {
		glfwRequestWindowAttention(winptr_);
	}

}