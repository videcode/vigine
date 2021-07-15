#include "irender.impl.h"
using namespace std;

graphics::vulkan::Render::Render(){
    using namespace std;

/*
	this->info.app.sType                 = vk::StructureType::eApplicationInfo;
	this->info.app.pNext                 = nullptr;
	this->info.app.pApplicationName      = "deepCode";
	this->info.app.applicationVersion    = VK_MAKE_API_VERSION(0, 1, 0, 0);
	this->info.app.pEngineName           = "deepEngine";
	this->info.app.engineVersion         = VK_MAKE_API_VERSION(0, 1, 0, 0);
	this->info.app.apiVersion            = VK_MAKE_API_VERSION(0, 1, 0, 0);
*/
// https://github.com/KhronosGroup/Vulkan-Hpp
// https://github.com/g-truc/gli
/*
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

	// list
	{
		// list of layers
		std::vector<vk::LayerProperties> lPropArr = vk::enumerateInstanceLayerProperties();
		//cout << "lPropArr.size(): " << lPropArr.size() << endl;
		if(lPropArr.size() > 0){
			for(auto lProp: lPropArr){
				//print_prop(lProp);
			}
		}

		// list of extensions
		std::vector<vk::ExtensionProperties> extPropArr = vk::enumerateInstanceExtensionProperties();
		//cout << "extPropArr.size(): " << extPropArr.size() << endl;
		if(extPropArr.size() > 0){
			for(auto extProp: extPropArr){
				//print_prop(extProp);
			}
		}
	}


	this->info.instCreate.sType                      = vk::StructureType::eInstanceCreateInfo;
	this->info.instCreate.pNext                      = nullptr;
	this->info.instCreate.flags                      = {};
	this->info.instCreate.pApplicationInfo           = &this->info.app;
	this->info.instCreate.enabledLayerCount          = layersNames.size();
	this->info.instCreate.ppEnabledLayerNames        = layersNames.data();
	this->info.instCreate.enabledExtensionCount      = desiredExtensions.size();
	this->info.instCreate.ppEnabledExtensionNames    = desiredExtensions.data();




    // instance
	this->obj.inst = vk::createInstanceUnique( this->info.instCreate, nullptr );
	if( this->obj.inst ){
		PFN_vkCreateDebugReportCallbackEXT vk_vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(this->obj.inst.get(), "vkCreateDebugReportCallbackEXT");

		// report callbacks
		VkDebugReportCallbackEXT vk_debugReportCallbackEXT;
		{
			VkDebugReportCallbackCreateInfoEXT vk_debugReportCallbackCreateInfoEXT;
			{
				vk_debugReportCallbackCreateInfoEXT.sType = VkStructureType::VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
				vk_debugReportCallbackCreateInfoEXT.pNext = nullptr;
				vk_debugReportCallbackCreateInfoEXT.flags =0
				    VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
				    VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT |
				    VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
					VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT;
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
			vk_vkCreateDebugReportCallbackEXT(this->obj.inst.get(), &vk_debugReportCallbackCreateInfoEXT, nullptr, &vk_debugReportCallbackEXT);

        }


        // physical devices
		this->obj.deviceArr = this->obj.inst->enumeratePhysicalDevices();
		if( this->obj.deviceArr.size() == 0 )
			throw std::runtime_error("ERROR: physical devices not isset (enumeratePhysicalDevices() return 0 count)");

    }else{
        throw std::runtime_error("error create vulkan instance");
    }
	*/
}

graphics::vulkan::Render::~Render()
{
	std::cout << "Render destructor" << std::endl;
}


void graphics::vulkan::Render::init(){
	this->inst.init();



/*
	print("in func graphics::Vulkan::Render::init()");

	vk::PhysicalDevice& device = this->obj.deviceArr[0];

	// physical device features
	this->settings.physicalDeviceFeature = device.getFeatures();

	//print_prop(this->settings.physicalDeviceFeature, "vkGetPhysicalDeviceFeatures");

	// create logical device
	if(!this->step_createLogicDevice())
		std::runtime_error("ERROR: not create logic device");

	// present modes
	if(!this->step_presentationMode())
		std::runtime_error("ERROR: not make presentation mode");

	// capabilities presentation surface
	if(!this->step_capabilitiesPresentationSurface())
		std::runtime_error("ERROR: not make capabilities presentation surface");
*/
	// image useges
	if(!this->step_imageUseges())
		std::runtime_error("ERROR: not all image usages supports");

	// transform
	if(!(this->settings.surfaceCapabilities.supportedTransforms & this->settings.surfaceTransform))
		this->settings.surfaceTransform = this->settings.surfaceCapabilities.currentTransform;

	// format swapchain images
	if(!this->step_surfaceFormat())
		std::runtime_error("ERROR: not supports surfaceFormatKHR");

	print_prop(this->settings.surfaceFormat, "SurfaceFormatKHR");

	// create swapchain
	if(!this->step_createSwapchain())
		std::runtime_error("ERROR: swapchain is not created");

	print("swapchain is created");

	// swapchain images
	if(!this->step_swapchainImages())
		std::runtime_error("ERROR: swapchain images is not acquired");

	// swapchain image index
	if(!this->step_swapchainCurrentImageIndex())
		std::runtime_error("ERROR: swapchain image index");

	// presentin an image
	if(!this->step_present())
		std::runtime_error("ERROR: presentin an image");

	// command pool
	if(!this->step_commandPool())
		std::runtime_error("ERROR: step_commandPool()");

	// command buffer
	if(!this->step_commandBuffer())
		std::runtime_error("ERROR: step_commandBuffer()");

}

void graphics::vulkan::Render::reg(std::shared_ptr<api::iFigure> fig){

}

void graphics::vulkan::Render::draw(){

}

void graphics::vulkan::Render::upd(){

}

void graphics::vulkan::Render::xlibInit(X11::Window win, X11::Display* dpy){
	this->inst.xlibData(win, dpy);
}

bool graphics::vulkan::Render::step_presentationMode(){

	vk::PhysicalDevice& device = this->obj.deviceArr[0];
	std::vector<vk::PresentModeKHR> presentModes = device.getSurfacePresentModesKHR(this->obj.presentationSurface);

	if(presentModes.size() > 0){
		print_prop(presentModes, "PresentModeKHR (" + std::to_string(presentModes.size()) + ")");
		this->settings.presentationMode = vk::PresentModeKHR::eFifo;
		return true;
	}

	return false;
}

bool graphics::vulkan::Render::step_capabilitiesPresentationSurface(){

	vk::PhysicalDevice& device = this->obj.deviceArr[0];

	vk::Result res = device.getSurfaceCapabilitiesKHR(this->obj.presentationSurface, &this->settings.surfaceCapabilities);
	if(res == vk::Result::eSuccess){
		print_prop(this->settings.surfaceCapabilities, "SurfaceCapabilitiesKHR");

		this->settings.minImageCount = this->settings.surfaceCapabilities.minImageCount + 1;
		if(this->settings.surfaceCapabilities.maxImageCount > 0 && this->settings.minImageCount > this->settings.surfaceCapabilities.maxImageCount)
			this->settings.minImageCount = this->settings.surfaceCapabilities.maxImageCount;

		if( 0xFFFFFFFF == this->settings.surfaceCapabilities.currentExtent.width ) {

			if( this->settings.imageSize.width < this->settings.surfaceCapabilities.minImageExtent.width )
				this->settings.imageSize.width = this->settings.surfaceCapabilities.minImageExtent.width;
			else if( this->settings.imageSize.width > this->settings.surfaceCapabilities.maxImageExtent.width )
				this->settings.imageSize.width = this->settings.surfaceCapabilities.maxImageExtent.width;

			if( this->settings.imageSize.height < this->settings.surfaceCapabilities.minImageExtent.height )
				this->settings.imageSize.height = this->settings.surfaceCapabilities.minImageExtent.height;
			else if( this->settings.imageSize.height > this->settings.surfaceCapabilities.maxImageExtent.height )
				this->settings.imageSize.height = this->settings.surfaceCapabilities.maxImageExtent.height;
		}else
			this->settings.imageSize = this->settings.surfaceCapabilities.currentExtent;
	}

	return false;
}

bool graphics::vulkan::Render::step_imageUseges(){
	vk::ImageUsageFlags supportedImageUsages = this->settings.imageUsage & this->settings.surfaceCapabilities.supportedUsageFlags;
	return (supportedImageUsages == this->settings.imageUsage);
}

bool graphics::vulkan::Render::step_createLogicDevice(){
	vk::PhysicalDevice& device = this->obj.deviceArr[0];

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

bool graphics::vulkan::Render::step_createSwapchain(){
	// swapchain
	this->info.swapchainCreate.sType	= vk::StructureType::eSwapchainCreateInfoKHR;
	this->info.swapchainCreate.pNext	= nullptr;
	this->info.swapchainCreate.flags	= {};
	this->info.swapchainCreate.surface			= this->obj.presentationSurface;
	this->info.swapchainCreate.minImageCount	= this->settings.minImageCount;
	this->info.swapchainCreate.imageFormat		= this->settings.surfaceFormat.format;
	this->info.swapchainCreate.imageColorSpace	= this->settings.surfaceFormat.colorSpace;
	this->info.swapchainCreate.imageExtent		= this->settings.imageSize;
	this->info.swapchainCreate.imageArrayLayers	= 1;
	this->info.swapchainCreate.imageUsage		= this->settings.imageUsage;
	this->info.swapchainCreate.imageSharingMode	= vk::SharingMode::eExclusive;
	this->info.swapchainCreate.queueFamilyIndexCount	= 0;
	this->info.swapchainCreate.pQueueFamilyIndices		= nullptr;
	this->info.swapchainCreate.preTransform		= this->settings.surfaceTransform;
	this->info.swapchainCreate.compositeAlpha	= vk::CompositeAlphaFlagBitsKHR::eOpaque;
	this->info.swapchainCreate.presentMode		= this->settings.presentationMode;
	this->info.swapchainCreate.clipped			= VK_TRUE;
	this->info.swapchainCreate.oldSwapchain		= nullptr;

	this->obj.swapchain = this->obj.logicDevice->createSwapchainKHRUnique(this->info.swapchainCreate);

	return (this->obj.swapchain)?true:false;
}

bool graphics::vulkan::Render::step_surfaceFormat(){
	vk::SurfaceFormatKHR desiredFormat;
	desiredFormat.format		= {};
	desiredFormat.colorSpace	= {};

	vk::PhysicalDevice& device = this->obj.deviceArr[0];

	std::vector<vk::SurfaceFormatKHR> surfaceFormatArr = device.getSurfaceFormatsKHR(this->obj.presentationSurface);
	if(surfaceFormatArr.size() > 0){
		print("surfaceFormatArr.size(): " + std::to_string(surfaceFormatArr.size()));
		if( (1 == surfaceFormatArr.size()) && (vk::Format::eUndefined == surfaceFormatArr[0].format) ) {
			this->settings.surfaceFormat.format = desiredFormat.format;
			this->settings.surfaceFormat.colorSpace = desiredFormat.colorSpace;

		}else{
			bool find = false;
			for( vk::SurfaceFormatKHR& item: surfaceFormatArr){
				if(item.format == desiredFormat.format && item.colorSpace == desiredFormat.colorSpace){
					this->settings.surfaceFormat.format		= item.format;
					this->settings.surfaceFormat.colorSpace	= item.colorSpace;
					find = true;
					break;
				}
			}
			if(!find){
				for(const vk::SurfaceFormatKHR& item: surfaceFormatArr){
					if(item.format == desiredFormat.format ){
						this->settings.surfaceFormat.format		= item.format;
						this->settings.surfaceFormat.colorSpace	= item.colorSpace;
						find = true;
						break;
					}
				}
				if(!find){
					this->settings.surfaceFormat.format		= surfaceFormatArr[0].format;
					this->settings.surfaceFormat.colorSpace	= surfaceFormatArr[0].colorSpace;
				}
			}
		}

		return true;
	}

	return false;
}

bool graphics::vulkan::Render::step_swapchainImages(){

	this->obj.swapchainImageArr = this->obj.logicDevice->getSwapchainImagesKHR(this->obj.swapchain.get());
	return (this->obj.swapchainImageArr.size() > 0)?true:false;
}

bool graphics::vulkan::Render::step_swapchainCurrentImageIndex(){

	uint32_t imageIndex = 0;
	vk::Result res = this->obj.logicDevice->acquireNextImageKHR( this->obj.swapchain.get(), 2000000000, this->obj.semaphore, this->obj.fence, &imageIndex );

	if(res == vk::Result::eSuccess || res == vk::Result::eSuboptimalKHR){
		print("imageIndex: "+std::to_string(imageIndex));
		this->obj.swapchainImageIndex = imageIndex;

		return true;
	}

	return false;
}

bool graphics::vulkan::Render::step_present(){
	this->info.present.sType = vk::StructureType::ePresentInfoKHR;
	this->info.present.pNext = nullptr;
	this->info.present.waitSemaphoreCount	= 0;
	this->info.present.pWaitSemaphores		= nullptr;
	this->info.present.swapchainCount		= 1;
	this->info.present.pSwapchains			= &this->obj.swapchain.get();
	this->info.present.pImageIndices		= &this->obj.swapchainImageIndex;
	this->info.present.pResults				= nullptr;

	vk::Result res = this->obj.queueGraphics.presentKHR(this->info.present);
	if(res == vk::Result::eSuccess)
		return true;
	//  need change image layout VK_IMAGE_LAYOUT_PRESENT_SRC_KHR

	return false;
}

bool graphics::vulkan::Render::step_commandPool(){
	this->info.commandPool.sType			= vk::StructureType::eCommandPoolCreateInfo;
	this->info.commandPool.pNext			= nullptr;
	this->info.commandPool.flags			= vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
	this->info.commandPool.queueFamilyIndex	= this->info.deviceQueueArr[0].queueFamilyIndex;

	this->obj.commandPool = this->obj.logicDevice->createCommandPoolUnique(this->info.commandPool);
	if(this->obj.commandPool)
		return true;
	return false;
}

void graphics::vulkan::Render::step_commandPoolReset(){
	this->obj.logicDevice->resetCommandPool(this->obj.commandPool.get(), vk::CommandPoolResetFlagBits::eReleaseResources);
}

bool graphics::vulkan::Render::step_commandBuffer(){

	this->info.commandBufferAllocate.sType			= vk::StructureType::eCommandBufferAllocateInfo;
	this->info.commandBufferAllocate.pNext			= nullptr;
	this->info.commandBufferAllocate.commandPool	= this->obj.commandPool.get();
	this->info.commandBufferAllocate.level			= vk::CommandBufferLevel::ePrimary;
	this->info.commandBufferAllocate.commandBufferCount	= 1;

	this->obj.commandBufferArrUniq = this->obj.logicDevice->allocateCommandBuffersUnique(this->info.commandBufferAllocate);

	if(this->obj.commandBufferArrUniq.size() > 0)
		return true;
	return false;
}

bool graphics::vulkan::Render::step_commandBufferBegin(){

	this->info.commandBufferBegin.sType = vk::StructureType::eCommandBufferBeginInfo;
	this->info.commandBufferBegin.pNext = nullptr;
	this->info.commandBufferBegin.flags = vk::CommandBufferUsageFlagBits::eSimultaneousUse;
	this->info.commandBufferBegin.pInheritanceInfo = nullptr;

	vk::Result res = this->obj.commandBufferArrUniq[0]->begin(&this->info.commandBufferBegin);

	if(res == vk::Result::eSuccess)
		return true;
	return false;
}

void graphics::vulkan::Render::step_commandBufferEnd(){
	this->obj.commandBufferArrUniq[0]->end();
}



void graphics::vulkan::print_prop(vk::PhysicalDevice& device, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    VkPhysicalDeviceProperties prop;
    vkGetPhysicalDeviceProperties(device, &prop);

    cout << "apiVersion: " << prop.apiVersion << endl;
    cout << "driverVersion: " << prop.driverVersion << endl;
    cout << "vendorID: " << prop.vendorID << endl;
    cout << "deviceID: " << prop.deviceID << endl;
    cout << "deviceName: " << prop.deviceName << endl;


/*
    // Provided by VK_VERSION_1_0
    typedef struct VkPhysicalDeviceProperties {
        uint32_t                            apiVersion;
        uint32_t                            driverVersion;
        uint32_t                            vendorID;
        uint32_t                            deviceID;
        VkPhysicalDeviceType                deviceType;
        char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
        uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
        VkPhysicalDeviceLimits              limits;
        VkPhysicalDeviceSparseProperties    sparseProperties;
    } VkPhysicalDeviceProperties;
*/

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::PhysicalDeviceMemoryProperties& memProp){
    using namespace std;

    cout << "memoryTypeCount: " << memProp.memoryTypeCount << endl;
    cout << "memoryHeapCount: " << memProp.memoryHeapCount << endl;

    for(int i = 0;i < memProp.memoryTypeCount;i++){
		vk::MemoryType memType = memProp.memoryTypes[i];
        cout << "memoryType: [" << i << "]: " << endl;
        cout << "   heapIndex: " << memType.heapIndex << endl;

		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal){
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostVisible){
            cout << "   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostCoherent){
            cout << "   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostCached){
            cout << "   VK_MEMORY_PROPERTY_HOST_CACHED_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_CACHED_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eLazilyAllocated){
            cout << "   VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT is 0" << endl;
        }

        print("   ---");
    }

    for(int i = 0;i < memProp.memoryHeapCount;i++){
        VkMemoryHeap memHeap = memProp.memoryHeaps[i];
        cout << "memoryHeap [" << i << "]: " << endl;
        cout << "   size: " << memHeap.size << endl;

        // Provided by VK_VERSION_1_0
        if(memHeap.flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT){
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 0" << endl;
        }

        // Provided by VK_VERSION_1_1
        if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT){
            cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 0" << endl;
        }

        // Provided by VK_KHR_device_group_creation
        // VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT
        #ifdef VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR
            if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR){
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR is 1" << endl;
            }else {
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR is 0" << endl;
            }
            #else
            if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT){
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 1" << endl;
            }else {
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 0" << endl;
            }
        #endif // VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR


        print("   ---");
    }


}

void graphics::vulkan::print_prop(vk::LayerProperties& prop){
    using namespace std;

    cout << "layerName: " << prop.layerName << endl;
}

void graphics::vulkan::print_prop(vk::ExtensionProperties& extProp){
    using namespace std;

    cout << "extName: " << extProp.extensionName << endl;
}

void graphics::vulkan::print_prop(vk::QueueFamilyProperties& prop, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    cout << "VkQueueFamilyProperties.queueCount: " << prop.queueCount << endl;
    cout << "VkQueueFamilyProperties.timestampValidBits: " << prop.timestampValidBits << endl;

	if(prop.queueFlags & vk::QueueFlagBits::eGraphics){
        cout << "   VK_QUEUE_GRAPHICS_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_GRAPHICS_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eCompute){
        cout << "   VK_QUEUE_COMPUTE_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_COMPUTE_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eTransfer){
        cout << "   VK_QUEUE_TRANSFER_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_TRANSFER_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eSparseBinding){
        cout << "   VK_QUEUE_SPARSE_BINDING_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_SPARSE_BINDING_BIT is 0" << endl;
    }

    cout << "VkQueueFamilyProperties.minImageTransferGranularity: " << endl;
    cout << "   width: " << prop.minImageTransferGranularity.width << endl;
    cout << "   height: " << prop.minImageTransferGranularity.height << endl;
    cout << "   depth: " << prop.minImageTransferGranularity.depth << endl;

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::PhysicalDeviceFeatures& prop, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    if(prop.robustBufferAccess == VK_TRUE){
        cout << "   robustBufferAccess: true" << endl;
    }else{
        cout << "   robustBufferAccess: false" << endl;
    }

    if(prop.fullDrawIndexUint32 == VK_TRUE){
        cout << "   fullDrawIndexUint32: true" << endl;
    }else{
        cout << "   fullDrawIndexUint32: false" << endl;
    }

    if(prop.imageCubeArray == VK_TRUE){
        cout << "   imageCubeArray: true" << endl;
    }else{
        cout << "   imageCubeArray: false" << endl;
    }

    if(prop.independentBlend == VK_TRUE){
        cout << "   independentBlend: true" << endl;
    }else{
        cout << "   independentBlend: false" << endl;
    }

    if(prop.geometryShader == VK_TRUE){
        cout << "   geometryShader: true" << endl;
    }else{
        cout << "   geometryShader: false" << endl;
    }

    if(prop.tessellationShader == VK_TRUE){
        cout << "   tessellationShader: true" << endl;
    }else{
        cout << "   tessellationShader: false" << endl;
    }

    if(prop.sampleRateShading == VK_TRUE){
        cout << "   sampleRateShading: true" << endl;
    }else{
        cout << "   sampleRateShading: false" << endl;
    }

    if(prop.dualSrcBlend == VK_TRUE){
        cout << "   dualSrcBlend: true" << endl;
    }else{
        cout << "   dualSrcBlend: false" << endl;
    }

    if(prop.logicOp == VK_TRUE){
        cout << "   logicOp: true" << endl;
    }else{
        cout << "   logicOp: false" << endl;
    }

    if(prop.multiDrawIndirect == VK_TRUE){
        cout << "   multiDrawIndirect: true" << endl;
    }else{
        cout << "   multiDrawIndirect: false" << endl;
    }

    if(prop.drawIndirectFirstInstance == VK_TRUE){
        cout << "   drawIndirectFirstInstance: true" << endl;
    }else{
        cout << "   drawIndirectFirstInstance: false" << endl;
    }

    if(prop.depthClamp == VK_TRUE){
        cout << "   depthClamp: true" << endl;
    }else{
        cout << "   depthClamp: false" << endl;
    }

    if(prop.depthBiasClamp == VK_TRUE){
        cout << "   depthBiasClamp: true" << endl;
    }else{
        cout << "   depthBiasClamp: false" << endl;
    }

    if(prop.fillModeNonSolid == VK_TRUE){
        cout << "   fillModeNonSolid: true" << endl;
    }else{
        cout << "   fillModeNonSolid: false" << endl;
    }

    if(prop.depthBounds == VK_TRUE){
        cout << "   depthBounds: true" << endl;
    }else{
        cout << "   depthBounds: false" << endl;
    }

    if(prop.wideLines == VK_TRUE){
        cout << "   wideLines: true" << endl;
    }else{
        cout << "   wideLines: false" << endl;
    }

    if(prop.largePoints == VK_TRUE){
        cout << "   largePoints: true" << endl;
    }else{
        cout << "   largePoints: false" << endl;
    }

    if(prop.alphaToOne == VK_TRUE){
        cout << "   alphaToOne: true" << endl;
    }else{
        cout << "   alphaToOne: false" << endl;
    }

    if(prop.multiViewport == VK_TRUE){
        cout << "   multiViewport: true" << endl;
    }else{
        cout << "   multiViewport: false" << endl;
    }

    if(prop.samplerAnisotropy == VK_TRUE){
        cout << "   samplerAnisotropy: true" << endl;
    }else{
        cout << "   samplerAnisotropy: false" << endl;
    }

    if(prop.textureCompressionETC2 == VK_TRUE){
        cout << "   textureCompressionETC2: true" << endl;
    }else{
        cout << "   textureCompressionETC2: false" << endl;
    }

    if(prop.textureCompressionASTC_LDR == VK_TRUE){
        cout << "   textureCompressionASTC_LDR: true" << endl;
    }else{
        cout << "   textureCompressionASTC_LDR: false" << endl;
    }

    if(prop.textureCompressionBC == VK_TRUE){
        cout << "   textureCompressionBC: true" << endl;
    }else{
        cout << "   textureCompressionBC: false" << endl;
    }

    if(prop.occlusionQueryPrecise == VK_TRUE){
        cout << "   occlusionQueryPrecise: true" << endl;
    }else{
        cout << "   occlusionQueryPrecise: false" << endl;
    }

    if(prop.pipelineStatisticsQuery == VK_TRUE){
        cout << "   pipelineStatisticsQuery: true" << endl;
    }else{
        cout << "   pipelineStatisticsQuery: false" << endl;
    }

    if(prop.vertexPipelineStoresAndAtomics == VK_TRUE){
        cout << "   vertexPipelineStoresAndAtomics: true" << endl;
    }else{
        cout << "   vertexPipelineStoresAndAtomics: false" << endl;
    }

    if(prop.fragmentStoresAndAtomics == VK_TRUE){
        cout << "   fragmentStoresAndAtomics: true" << endl;
    }else{
        cout << "   fragmentStoresAndAtomics: false" << endl;
    }

    if(prop.shaderTessellationAndGeometryPointSize == VK_TRUE){
        cout << "   shaderTessellationAndGeometryPointSize: true" << endl;
    }else{
        cout << "   shaderTessellationAndGeometryPointSize: false" << endl;
    }

    if(prop.shaderImageGatherExtended == VK_TRUE){
        cout << "   shaderImageGatherExtended: true" << endl;
    }else{
        cout << "   shaderImageGatherExtended: false" << endl;
    }

    if(prop.shaderStorageImageExtendedFormats == VK_TRUE){
        cout << "   shaderStorageImageExtendedFormats: true" << endl;
    }else{
        cout << "   shaderStorageImageExtendedFormats: false" << endl;
    }

    if(prop.shaderStorageImageMultisample == VK_TRUE){
        cout << "   shaderStorageImageMultisample: true" << endl;
    }else{
        cout << "   shaderStorageImageMultisample: false" << endl;
    }

    if(prop.shaderStorageImageReadWithoutFormat == VK_TRUE){
        cout << "   shaderStorageImageReadWithoutFormat: true" << endl;
    }else{
        cout << "   shaderStorageImageReadWithoutFormat: false" << endl;
    }

    if(prop.shaderStorageImageWriteWithoutFormat == VK_TRUE){
        cout << "   shaderStorageImageWriteWithoutFormat: true" << endl;
    }else{
        cout << "   shaderStorageImageWriteWithoutFormat: false" << endl;
    }

    if(prop.shaderUniformBufferArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderUniformBufferArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderUniformBufferArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderSampledImageArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderSampledImageArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderSampledImageArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderStorageBufferArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderStorageBufferArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderStorageBufferArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderStorageImageArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderStorageImageArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderStorageImageArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderClipDistance == VK_TRUE){
        cout << "   shaderClipDistance: true" << endl;
    }else{
        cout << "   shaderClipDistance: false" << endl;
    }

    if(prop.shaderCullDistance == VK_TRUE){
        cout << "   shaderCullDistance: true" << endl;
    }else{
        cout << "   shaderCullDistance: false" << endl;
    }

    if(prop.shaderFloat64 == VK_TRUE){
        cout << "   shaderFloat64: true" << endl;
    }else{
        cout << "   shaderFloat64: false" << endl;
    }

    if(prop.shaderInt64 == VK_TRUE){
        cout << "   shaderInt64: true" << endl;
    }else{
        cout << "   shaderInt64: false" << endl;
    }

    if(prop.shaderInt16 == VK_TRUE){
        cout << "   shaderInt16: true" << endl;
    }else{
        cout << "   shaderInt16: false" << endl;
    }

    if(prop.shaderResourceResidency == VK_TRUE){
        cout << "   shaderResourceResidency: true" << endl;
    }else{
        cout << "   shaderResourceResidency: false" << endl;
    }

    if(prop.shaderResourceMinLod == VK_TRUE){
        cout << "   shaderResourceMinLod: true" << endl;
    }else{
        cout << "   shaderResourceMinLod: false" << endl;
    }

    if(prop.sparseBinding == VK_TRUE){
        cout << "   sparseBinding: true" << endl;
    }else{
        cout << "   sparseBinding: false" << endl;
    }

    if(prop.sparseResidencyBuffer == VK_TRUE){
        cout << "   sparseResidencyBuffer: true" << endl;
    }else{
        cout << "   sparseResidencyBuffer: false" << endl;
    }

    if(prop.sparseResidencyImage2D == VK_TRUE){
        cout << "   sparseResidencyImage2D: true" << endl;
    }else{
        cout << "   sparseResidencyImage2D: false" << endl;
    }

    if(prop.sparseResidencyImage3D == VK_TRUE){
        cout << "   sparseResidencyImage3D: true" << endl;
    }else{
        cout << "   sparseResidencyImage3D: false" << endl;
    }

    if(prop.sparseResidency2Samples == VK_TRUE){
        cout << "   sparseResidency2Samples: true" << endl;
    }else{
        cout << "   sparseResidency2Samples: false" << endl;
    }

    if(prop.sparseResidency4Samples == VK_TRUE){
        cout << "   sparseResidency4Samples: true" << endl;
    }else{
        cout << "   sparseResidency4Samples: false" << endl;
    }

    if(prop.sparseResidency8Samples == VK_TRUE){
        cout << "   sparseResidency8Samples: true" << endl;
    }else{
        cout << "   sparseResidency8Samples: false" << endl;
    }

    if(prop.sparseResidency16Samples == VK_TRUE){
        cout << "   sparseResidency16Samples: true" << endl;
    }else{
        cout << "   sparseResidency16Samples: false" << endl;
    }

    if(prop.sparseResidencyAliased == VK_TRUE){
        cout << "   sparseResidencyAliased: true" << endl;
    }else{
        cout << "   sparseResidencyAliased: false" << endl;
    }

    if(prop.variableMultisampleRate == VK_TRUE){
        cout << "   variableMultisampleRate: true" << endl;
    }else{
        cout << "   variableMultisampleRate: false" << endl;
    }

    if(prop.inheritedQueries == VK_TRUE){
        cout << "   inheritedQueries: true" << endl;
    }else{
        cout << "   inheritedQueries: false" << endl;
    }

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(std::vector<vk::PresentModeKHR>& arr, string str){
}

void graphics::vulkan::print_prop(vk::SurfaceCapabilitiesKHR& var, string str){

	using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

	/*
// Provided by VK_KHR_surface
typedef struct VkSurfaceCapabilitiesKHR {
	uint32_t                         minImageCount;
	uint32_t                         maxImageCount;
	VkExtent2D                       currentExtent;
	VkExtent2D                       minImageExtent;
	VkExtent2D                       maxImageExtent;
	uint32_t                         maxImageArrayLayers;
	VkSurfaceTransformFlagsKHR       supportedTransforms;
	VkSurfaceTransformFlagBitsKHR    currentTransform;
	VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
	VkImageUsageFlags                supportedUsageFlags;
} VkSurfaceCapabilitiesKHR;
	*/
	print(".minImageCount: " + std::to_string(var.minImageCount));
	print(".maxImageCount: " + std::to_string(var.maxImageCount));
	print(".maxImageArrayLayers: " + std::to_string(var.maxImageArrayLayers));
	print_extent<2>(var.currentExtent, ".currentExtent");
	print_extent<2>(var.currentExtent, ".minImageExtent");
	print_extent<2>(var.currentExtent, ".maxImageExtent");

	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eIdentity, ".supportedTransforms.eIdentity");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate90, ".supportedTransforms.eRotate90");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate180, ".supportedTransforms.eRotate180");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate270, ".supportedTransforms.eRotate270");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror, ".supportedTransforms.eHorizontalMirror");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90, ".supportedTransforms.eHorizontalMirrorRotate90");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180, ".supportedTransforms.eHorizontalMirrorRotate180");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270, ".supportedTransforms.eHorizontalMirrorRotate270");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eInherit, ".supportedTransforms.eInherit");
	print(" ");

	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eIdentity, ".currentTransform.eIdentity");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate90, ".currentTransform.eRotate90");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate180, ".currentTransform.eRotate180");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate270, ".currentTransform.eRotate270");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror, ".currentTransform.eHorizontalMirror");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90, ".currentTransform.eHorizontalMirrorRotate90");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180, ".currentTransform.eHorizontalMirrorRotate180");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270, ".currentTransform.eHorizontalMirrorRotate270");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eInherit, ".currentTransform.eInherit");
	print(" ");

	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::eOpaque, ".supportedCompositeAlpha.eOpaque");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::ePreMultiplied, ".supportedCompositeAlpha.ePreMultiplied");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::ePostMultiplied, ".supportedCompositeAlpha.ePostMultiplied");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::eInherit, ".supportedCompositeAlpha.eInherit");
	print(" ");

	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eSampled, ".supportedUsageFlags.eSampled");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eStorage, ".supportedUsageFlags.eStorage");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eColorAttachment, ".supportedUsageFlags.eColorAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eDepthStencilAttachment, ".supportedUsageFlags.eDepthStencilAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eInputAttachment, ".supportedUsageFlags.eInputAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eTransientAttachment, ".supportedUsageFlags.eTransientAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eFragmentShadingRateAttachmentKHR, ".supportedUsageFlags.eFragmentShadingRateAttachmentKHR");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eFragmentDensityMapEXT, ".supportedUsageFlags.eFragmentDensityMapEXT");


	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::SurfaceFormatKHR& var, string str){

	using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

	print(".format."+vk::to_string(var.format));
	print(".colorSpace."+vk::to_string(var.colorSpace));

	if(!str.empty())
		print("--- end "+str+" ---");
}

template<typename T, typename T2>
void graphics::vulkan::print_bit(T var, T2 var2, string str, bool print_if_eual){
	if(var & var2)
		print(str+": 1");
	else
		if(!print_if_eual)
			print(str+": 0");

}

template<typename T, typename T2>
void graphics::vulkan::print_equal(T var, T2 var2, string str ){
	if(var == var2)
		print(str);
}

template<int n, typename T>
void graphics::vulkan::print_extent(T var, std::string str){

	if constexpr (n == 2){
		print(str+".width: "+std::to_string(var.width));
		print(str+".height: "+std::to_string(var.height));
	}
	if constexpr (n == 3){
		print(str+".width: "+std::to_string(var.width));
		print(str+".height: "+std::to_string(var.height));
		print(str+".depth: "+std::to_string(var.depth));
	}
}


