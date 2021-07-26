#pragma once
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

#include "renderpass.h"

namespace graphics{
	namespace vulkan{
		class PipelineGraphic{
			public:
				PipelineGraphic();

				void init();

			private:
				Renderpass renderpass;

				std::weak_ptr<vk::Device> pwDevice;
		};
	}
}
