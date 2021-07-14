#include "device.h"

using namespace graphics::vulkan;

Device::Device(){

}

void Device::init(vk::Instance& inst){
	std::cout << "Device init" << std::endl;
	this->vDevice = inst.enumeratePhysicalDevices();

	if( this->vDevice.size() == 0 )
		throw std::runtime_error("ERROR: physical devices not isset (enumeratePhysicalDevices() return 0 count)");
}

bool Device::createLogicDevice(){
	vk::PhysicalDevice& device = this->vDevice[0];

	auto indexFamilySupportSurfaceKHR = [&device](uint32_t& queueFamilyIndex, vk::SurfaceKHR& presentationSurface)->bool{

		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();
		uint32_t	index = 0;
		vk::Bool32	presentation_supported = VK_FALSE;
		vk::Result	res;

		// get index of family that support surfaceKHR
		for(auto qfItem: queueFamilies){
			res = device.getSurfaceSupportKHR(index, presentationSurface, &presentation_supported);
			if(res == vk::Result::eSuccess && presentation_supported == VK_TRUE){
				queueFamilyIndex = index;
				return true;
			}
			index++;
		}
		return false;
	};

	uint32_t queueFamilyIndex = 0;
	if(!indexFamilySupportSurfaceKHR(queueFamilyIndex, this->obj.presentationSurface))
		return false;


	vk::DeviceQueueCreateInfo         deviceQueueInfo;
	deviceQueueInfo.sType             = vk::StructureType::eDeviceQueueCreateInfo;
	deviceQueueInfo.pNext             = nullptr;
	deviceQueueInfo.flags             = {};
	deviceQueueInfo.queueFamilyIndex  = queueFamilyIndex;
	deviceQueueInfo.queueCount        = this->settings.queuePriority.size();
	deviceQueueInfo.pQueuePriorities  = this->settings.queuePriority.data();

	this->info.deviceQueueArr.push_back(deviceQueueInfo);


	std::vector<const char*> desiredExtensions = {
	    VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};


	this->info.logicDevice.sType                     = vk::StructureType::eDeviceCreateInfo;
	this->info.logicDevice.pNext                     = nullptr;
	this->info.logicDevice.flags                     = {};
	this->info.logicDevice.queueCreateInfoCount      = this->info.deviceQueueArr.size();
	this->info.logicDevice.pQueueCreateInfos         = this->info.deviceQueueArr.data();
	this->info.logicDevice.enabledLayerCount         = 0;
	this->info.logicDevice.ppEnabledLayerNames       = nullptr;
	this->info.logicDevice.enabledExtensionCount     = desiredExtensions.size();
	this->info.logicDevice.ppEnabledExtensionNames   = desiredExtensions.data();
	this->info.logicDevice.pEnabledFeatures          = &this->settings.physicalDeviceFeature;

	this->obj.logicDevice = device.createDeviceUnique(
	                                this->info.logicDevice,
	                                nullptr
	                                );

	if(this->obj.logicDevice){
		uint32_t queueIndex = 0;
		this->obj.queueGraphics = this->obj.logicDevice->getQueue(queueFamilyIndex, queueIndex);
		return true;
	}

	return false;
}
