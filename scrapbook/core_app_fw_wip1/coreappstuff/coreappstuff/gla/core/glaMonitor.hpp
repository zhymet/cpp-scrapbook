#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "glfwError.hpp"

#include <vector>
#include "../../gtl/gfx/vec2.hpp"
// Monitor objects cannot be created or destroyed by the application and retain their addresses until the monitors they represent are 
// disconnected or until the library is terminated.
namespace gla {

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
		const GLFWvidmode & getCurrentVideoMode();
		std::vector<const GLFWvidmode &> getAvailVideoModes();
		void setGamma(float gamma);
		void setGammaRamp(const GLFWgammaramp & gamma_ramp);
		const GLFWgammaramp & getGammaRamp();


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
				auto it = std::find_if(monitors_.begin(), monitors_.end(), [monitor](auto& a) {a.getGLFWMonitorPointer() == monitor; });
				if (it == monitors_.end()) {
					monitors_.push_back(monitor);
				}
				// Reset primary monitor
				auto p_monitor = glfwGetPrimaryMonitor();
				primary_monitor_ = std::find_if(monitors_.begin(), monitors_.end(), [p_monitor](auto& a) {a.getGLFWMonitorPointer() == p_monitor; });
			}
			else if (event == GLFW_DISCONNECTED)
			{
				// A monitor was disconnected
				// Find the monitor index and remove it from monitor vector
				monitors_.erase(std::find_if(monitors_.begin(), monitors_.end(), [monitor](auto& a) {a.getGLFWMonitorPointer() == monitor; }));
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
}