#pragma once

#include <vector>
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

#include <iostream>
#include "family.h"
#include "commandpool.h"
#include "surface.h"
#include "swapchain.h"

namespace graphics {
	namespace vulkan {
		class Device {
			public:
				Device();
				~Device(){
				}
				void destroy(){
					std::cout << "~Device(){}" << std::endl;
					this->swapchain.destroy(this->logicDevice);
					this->logicDevice.destroySwapchainKHR(this->swapchain.get());
					this->logicDevice.destroy();
				}

				void init(vk::Instance&, Surface&);
				void createSwapchain(Surface&);
				vk::PhysicalDevice& getPhysical()	{return this->vDevice[0];}
				vk::Device&			getLogical()	{return this->logicDevice;}


			private:
				// info
				vk::DeviceCreateInfo					createInfo;
				std::vector<vk::DeviceQueueCreateInfo>	vQueueCreateInfo;

				vk::PhysicalDeviceFeatures			physicalDeviceFeature;
				// objects
				vk::Device							logicDevice;
				std::vector< vk::PhysicalDevice >	vDevice;
				vk::Queue							queueGraphics;
				//std::vector< Family >				vFamily;
				//std::vector< CommandPool >		vCommandPool;
				Swapchain							swapchain;

				// settings
				int										indexFamilySurfaceSupport	{-1};
				std::vector<float>						queuePriority				{1.0f};

				void createLogicDevice();
				void indexFamilySupportSurfaceKHR(Surface&);
				void createQueue();
		};
	}
}

