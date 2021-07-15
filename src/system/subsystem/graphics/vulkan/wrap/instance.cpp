#include "instance.h"

using namespace graphics::vulkan;

Instance::Instance(){

}

void Instance::init(){
	std::cout << "Instance init" << std::endl;

	this->appInfo.sType                 = vk::StructureType::eApplicationInfo;
	this->appInfo.pNext                 = nullptr;
	this->appInfo.pApplicationName      = "deepCode";
	this->appInfo.applicationVersion    = VK_MAKE_API_VERSION(0, 1, 0, 0);
	this->appInfo.pEngineName           = "deepEngine";
	this->appInfo.engineVersion         = VK_MAKE_API_VERSION(0, 1, 0, 0);
	this->appInfo.apiVersion            = VK_MAKE_API_VERSION(0, 1, 0, 0);

	std::vector<const char*> layersNames = {
	    "VK_LAYER_KHRONOS_validation",
	};
	std::vector<const char*> desiredExtensions = {
	    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
	    "VK_KHR_display",
	    "VK_KHR_get_display_properties2",
	    "VK_KHR_get_surface_capabilities2",
	    "VK_KHR_surface",
	    "VK_KHR_surface_protected_capabilities",
	    "VK_KHR_xlib_surface",
	    "VK_EXT_acquire_xlib_display",
	    "VK_EXT_direct_mode_display",
	    "VK_EXT_display_surface_counter"
	};

	this->createInfo.sType                      = vk::StructureType::eInstanceCreateInfo;
	this->createInfo.pNext                      = nullptr;
	this->createInfo.flags                      = {};
	this->createInfo.pApplicationInfo           = &this->appInfo;
	this->createInfo.enabledLayerCount          = layersNames.size();
	this->createInfo.ppEnabledLayerNames        = layersNames.data();
	this->createInfo.enabledExtensionCount      = desiredExtensions.size();
	this->createInfo.ppEnabledExtensionNames    = desiredExtensions.data();

	this->inst = vk::createInstance( this->createInfo, nullptr );

	if( this->inst )
		this->debug();
	else
		throw std::runtime_error("ERROR: create vulkan instance");

	this->surface.initBeforeDeviceInit(this->inst);
	this->device.init(this->inst, this->surface);

	vk::PhysicalDevice& device = this->device.getPhysical();

	this->surface.initAfrerDeviceInit(device);
	this->swapchain.init(this->device.getLogical(), this->surface);
}

void Instance::xlibData(X11::Window win, X11::Display* dpy){
	this->surface.xlibData(win, dpy);
}

void Instance::debug(){
	PFN_vkCreateDebugReportCallbackEXT vk_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(this->inst, "vkCreateDebugReportCallbackEXT");

	// report callbacks
	VkDebugReportCallbackEXT vk_debugReportCallbackEXT;

	{
		VkDebugReportCallbackCreateInfoEXT vk_debugReportCallbackCreateInfoEXT;

		{
			vk_debugReportCallbackCreateInfoEXT.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			vk_debugReportCallbackCreateInfoEXT.pNext = nullptr;
			vk_debugReportCallbackCreateInfoEXT.flags =0/*
				VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
				VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT |
				VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
				VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
				VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT*/;
			vk_debugReportCallbackCreateInfoEXT.pfnCallback = [](
			    VkDebugReportFlagsEXT    flags,
			    VkDebugReportObjectTypeEXT    objectType,
			    uint64_t        object,
			    size_t          location,
			    int32_t         messageCode,
			    const char*     pLayerPrefix,
			    const char*     pMessage,
			    void*           pUserData) -> VkBool32{
				    std::cout << "(";
					if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0) std::cout << "INFO";
					if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0) std::cout << "WARNING";
					if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0) std::cout << "PERFORMANCE";
					if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0) std::cout << "DEBUG";
					if((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0) std::cout << "ERROR";
					std::cout << ")";
					std::cout << "{" << pLayerPrefix << "} " << pMessage << std::endl;
					return VK_FALSE;
			    };
			vk_debugReportCallbackCreateInfoEXT.pUserData = nullptr;
		}
		vk_vkCreateDebugReportCallbackEXT(this->inst, &vk_debugReportCallbackCreateInfoEXT, nullptr, &vk_debugReportCallbackEXT);
	}
}
