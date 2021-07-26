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
#include "pipeline/pipelinegraphic.h"
#include "pipeline/renderpass.h"

namespace graphics {
	namespace vulkan {
		class Device {
			public:
				Device();
				~Device(){
				}
				void destroy(){
					std::cout << "~Device(){}" << std::endl;
					this->swapchain.destroy(this->psLogicDevice);
					this->psLogicDevice->destroySwapchainKHR(this->swapchain.get());
					this->psLogicDevice->destroy();
				}

				void init(vk::Instance&, Surface&);
				void createSwapchain(Surface&);
				void createPipelineGraphic();
				vk::PhysicalDevice&			getPhysical()	{return this->vDevice[0];}
				std::shared_ptr<vk::Device>	getLogical()	{return this->psLogicDevice;}


			private:
				// info
				vk::DeviceCreateInfo					createInfo;
				std::vector<vk::DeviceQueueCreateInfo>	vQueueCreateInfo;

				vk::PhysicalDeviceFeatures			physicalDeviceFeature;

				// objects
				std::shared_ptr<vk::Device>			psLogicDevice;
				std::vector< vk::PhysicalDevice >	vDevice;
				vk::Queue							queueGraphics;
				//std::vector< Family >				vFamily;
				//std::vector< CommandPool >		vCommandPool;
				Swapchain							swapchain;
				PipelineGraphic						pipelineGraphic;

				// settings
				int										indexFamilySurfaceSupport	{-1};
				std::vector<float>						queuePriority				{1.0f};

				void createLogicDevice();
				void indexFamilySupportSurfaceKHR(Surface&);
				void createQueue();
		};
	}
}

