#include "glaMonitor.hpp"
namespace gla {
	// Physical size of monitor in milimeters (estimatted) no relation to current resolution.
	gtl::vec2<int> Monitor::getPhysicalSize() {
		gtl::vec2<int> size;
		glfwGetMonitorPhysicalSize(monitor_ptr_,&size.x,&size.y);
		return size;
	};
	// Ratio between the current DPI and the platform's default DPI.
	// may depend on both the monitor resolution and pixel density and on user settings. 
	gtl::vec2<float> Monitor::getMonitorContentScale() {
		gtl::vec2<float> scale;
		glfwGetMonitorContentScale(monitor_ptr_, &scale.x, &scale.y);
		return scale;
	};

	// position of the monitor on the virtual desktop, in screen coordinates
	gtl::vec2<int> Monitor::getVirtualPosition() {
		gtl::vec2<int> pos;
		glfwGetMonitorPos(monitor_ptr_, &pos.x, &pos.y);
		return pos;
	};

	// area of a monitor not occupied by global task bars or menu bars, in screen coordinates
	gtl::vec2<gtl::vec2<int>> Monitor::getWorkArea() {
		gtl::vec2<gtl::vec2<int>> area;
		glfwGetMonitorWorkarea(monitor_ptr_, &area.x.x, &area.x.y, &area.y.x, &area.y.x);
		return area;
	}; 

	// The human-readable, UTF-8 encoded name of a monitor. Monitor names are not guaranteed to be unique.
	std::string_view Monitor::getStringName() {
		return glfwGetMonitorName(monitor_ptr_);
	}; 

	const GLFWvidmode & Monitor::getCurrentVideoMode() {
		return *glfwGetVideoMode(monitor_ptr_);
	};

	std::vector<const GLFWvidmode &> Monitor::getAvailVideoModes() {
		std::vector<const GLFWvidmode &> ret;
		int count;
		const GLFWvidmode* modes = glfwGetVideoModes(monitor_ptr_, &count);
		for (size_t i = 0; i < count; i++)
		{
			ret.push_back(modes[i]);
		}
	};

	//  gamma 1.0, will produce the default (usually sRGB-like) behavior.
	void Monitor::setGamma(float gamma) {
		glfwSetGamma(monitor_ptr_, gamma);
	};

	void Monitor::setGammaRamp(const GLFWgammaramp & gamma_ramp) {
		glfwSetGammaRamp(monitor_ptr_, &gamma_ramp);
	};

	const GLFWgammaramp & Monitor::getGammaRamp() {
		return *glfwGetGammaRamp(monitor_ptr_);
	};


}