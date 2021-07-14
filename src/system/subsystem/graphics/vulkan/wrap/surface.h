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

			private:
				vk::SurfaceKHR surface;
		};
	}
}
