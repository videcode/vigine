#include "device.h"

using namespace graphics::vulkan;

Device::Device(){

}

void Device::init(vk::Instance& inst, Surface& surface){
	std::cout << "Device init" << std::endl;
	this->vDevice = inst.enumeratePhysicalDevices();

	if( this->vDevice.size() == 0 )
		throw std::runtime_error("ERROR: physical devices not isset (enumeratePhysicalDevices() return 0 count)");

	vk::PhysicalDevice& device	= this->vDevice[0];
	this->physicalDeviceFeature = device.getFeatures();

	this->indexFamilySupportSurfaceKHR(surface);
	this->createLogicDevice();

	this->createFamily();
}

void Device::createLogicDevice(){

	vk::PhysicalDevice& device = this->vDevice[0];

	vk::DeviceQueueCreateInfo         deviceQueueInfo;
	deviceQueueInfo.sType             = vk::StructureType::eDeviceQueueCreateInfo;
	deviceQueueInfo.pNext             = nullptr;
	deviceQueueInfo.flags             = {};
	deviceQueueInfo.queueFamilyIndex  = this->indexFamilySurfaceSupport;
	deviceQueueInfo.queueCount        = this->queuePriority.size();
	deviceQueueInfo.pQueuePriorities  = this->queuePriority.data();

	this->vQueueCreateInfo.push_back(deviceQueueInfo);

	std::vector<const char*> desiredExtensions = {
	    VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


	this->createInfo.sType                     = vk::StructureType::eDeviceCreateInfo;
	this->createInfo.pNext                     = nullptr;
	this->createInfo.flags                     = {};
	this->createInfo.queueCreateInfoCount      = this->vQueueCreateInfo.size();
	this->createInfo.pQueueCreateInfos         = this->vQueueCreateInfo.data();
	this->createInfo.enabledLayerCount         = 0;
	this->createInfo.ppEnabledLayerNames       = nullptr;
	this->createInfo.enabledExtensionCount     = desiredExtensions.size();
	this->createInfo.ppEnabledExtensionNames   = desiredExtensions.data();
	this->createInfo.pEnabledFeatures          = &this->physicalDeviceFeature;

	this->logicDevice = device.createDevice( this->createInfo, nullptr );
/*
	uint32_t queueIndex = 0;
	this->obj.queueGraphics = this->logicDevice.getQueue(this->indexFamilyGraphics, queueIndex);
*/
}

void Device::indexFamilySupportSurfaceKHR(Surface& surface){

	vk::PhysicalDevice& device = this->vDevice[0];

	std::vector<vk::QueueFamilyProperties> familyProperties = device.getQueueFamilyProperties();

	vk::Result	res;
	vk::Bool32	supported = VK_FALSE;

	for(uint32_t i = 0; i < familyProperties.size();i++ ){
		res = device.getSurfaceSupportKHR(i, surface.get(), &supported);
		if(res == vk::Result::eSuccess && supported == VK_TRUE){
			this->indexFamilySurfaceSupport = i;
			return;
		}
	}

	throw std::runtime_error("ERROR: physical devices not support surfaceKHR");
}

void Device::createFamily(){

}



