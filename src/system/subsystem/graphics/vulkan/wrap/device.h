#pragma once

#include <vector>
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

#include <iostream>
#include "family.h"
#include "commandpool.h"

namespace graphics {
	namespace vulkan {
		class Device {
			public:
				Device();

				void init(vk::Instance&);
			private:
				vk::Device						logicDevice	{nullptr};

				std::vector< vk::PhysicalDevice >	vDevice;
				std::vector< Family >				vFamily;
				std::vector< CommandPool >			vCommandPool;

				bool createLogicDevice();
		};
	}
}

