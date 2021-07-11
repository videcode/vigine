#pragma once

#include <vector>
#include <array>
#include <exception>
#include <iostream>


#include "api.h"
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IFIGURE

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

#include "device.h"

namespace graphics {
	namespace vulkan {
		class Instance{
			public:
				Instance();

				void init();
				bool init(X11::Window, X11::Display*);
				void add(api::iFigure*);
				void add(api::iCamera*);
				void prepare();
				void work();

			private:
				Device device;
		};
	}
}

