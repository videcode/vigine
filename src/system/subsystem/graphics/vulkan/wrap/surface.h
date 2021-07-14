#pragma once

#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

namespace graphics {
	namespace vulkan {
		class Surface{
			public:
				Surface();
				void init(vk::Instance&);
				void xlibData(Window, Display*);
				vk::SurfaceKHR& get(){return this->surface;}
				void presentModeKHR(vk::PresentModeKHR);
			private:
				vk::SurfaceKHR					surface;
				vk::XlibSurfaceCreateInfoKHR	createInfo;

				Window		win	{0};
				Display*	dpy	{nullptr};

				vk::PresentModeKHR				presentMode	{};
		};
	}
}
