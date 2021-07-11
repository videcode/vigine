#pragma once

#include <vector>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

namespace graphics {
	namespace vulkan {
		class Device{
			public:
				Device();

				void init();
			private:
				vk::UniqueDevice				logicDevice	{nullptr};
				std::vector<vk::PhysicalDevice>	deviceArr;
		};
	}
}

