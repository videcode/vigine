#pragma once

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>
#include "surface.h"
#include <vector>

namespace graphics {
	namespace vulkan {
		class Swapchain{
			public:
				Swapchain();
				void init(vk::Device& logicDevice, Surface&);
				void imageIndex(vk::Device&);
			private:
				vk::SwapchainKHR			swapchain;
				vk::SwapchainCreateInfoKHR	createInfo;
				std::vector<vk::Image>		vImages;

				uint32_t					currentImageIndex{0};
		};
	}
}
