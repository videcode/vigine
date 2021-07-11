#pragma once

#include <vector>
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

#include "family.h"
#include "commandpool.h"

namespace graphics {
	namespace vulkan {
		class Device{
			public:
				using shrdPhysicalDevice	= std::shared_ptr<vk::PhysicalDevice>;
				using shrdFamily			= std::shared_ptr<Family>;
				using shrdCommandPool		= std::shared_ptr<CommandPool>;


				Device();

				void init();
			private:
				vk::UniqueDevice				logicDevice	{nullptr};

				std::vector< shrdPhysicalDevice >	vDevice;
				std::vector< shrdFamily >			vFamily;
				std::vector< shrdCommandPool >		vCommandPool;
		};
	}
}

