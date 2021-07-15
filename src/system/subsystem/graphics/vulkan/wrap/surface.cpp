#include "surface.h"

using namespace graphics::vulkan;

Surface::Surface(){

}

void Surface::initBeforeDevice(vk::Instance& inst){

	this->createInfo.sType		= vk::StructureType::eXlibSurfaceCreateInfoKHR;
	this->createInfo.pNext		= nullptr;
	this->createInfo.flags		= {};
	this->createInfo.dpy		= this->dpy;
	this->createInfo.window		= this->win;

	vk::Result res = inst.createXlibSurfaceKHR(&this->createInfo, nullptr, &this->surface);

	if(res == vk::Result::eSuccess){
		std::cout << "presentationSurface create" << std::endl;
	}else
		std::runtime_error("presentationSurface not create");

}

void Surface::initAfrerDevice(vk::PhysicalDevice& device){
	this->presentModeKHR(device);
	this->capabilitiesKHR(device);
	this->setFormat(device);
	this->imageUsagesFlags();
	this->supportedTransforms();
}

void Surface::xlibData(Window win, Display* dpy){
	this->win = win;
	this->dpy = dpy;
}

void Surface::presentModeKHR(vk::PhysicalDevice& device){
	std::vector<vk::PresentModeKHR> presentModes = device.getSurfacePresentModesKHR(this->surface);
	if(presentModes.size() > 0)
		this->presentMode = vk::PresentModeKHR::eFifo;
	else
		std::runtime_error("ERROR: physical device does not suppot any present mode");
}

void Surface::capabilitiesKHR(vk::PhysicalDevice& device){

	vk::Result res = device.getSurfaceCapabilitiesKHR(this->surface, &this->surfaceCapabilities);
	if(res == vk::Result::eSuccess){

		this->minImageCount = this->surfaceCapabilities.minImageCount + 1;
		if(this->surfaceCapabilities.maxImageCount > 0 && this->minImageCount > this->surfaceCapabilities.maxImageCount)
			this->minImageCount = this->surfaceCapabilities.maxImageCount;

		if( 0xFFFFFFFF == this->surfaceCapabilities.currentExtent.width ) {

			if( this->imageSize.width < this->surfaceCapabilities.minImageExtent.width )
				this->imageSize.width = this->surfaceCapabilities.minImageExtent.width;
			else if( this->imageSize.width > this->surfaceCapabilities.maxImageExtent.width )
				this->imageSize.width = this->surfaceCapabilities.maxImageExtent.width;

			if( this->imageSize.height < this->surfaceCapabilities.minImageExtent.height )
				this->imageSize.height = this->surfaceCapabilities.minImageExtent.height;
			else if( this->imageSize.height > this->surfaceCapabilities.maxImageExtent.height )
				this->imageSize.height = this->surfaceCapabilities.maxImageExtent.height;
		}else
			this->imageSize = this->surfaceCapabilities.currentExtent;
	}else
		std::runtime_error("ERROR: device.getSurfaceCapabilitiesKHR return bad result");
}

void Surface::imageUsagesFlags(){
	vk::ImageUsageFlags supportedImageUsages = this->imageUsage & this->surfaceCapabilities.supportedUsageFlags;
	if (supportedImageUsages != this->imageUsage)
		std::runtime_error("ERROR: imageUsagesFlags not all support");
}

void Surface::supportedTransforms(){
	if(!(this->surfaceCapabilities.supportedTransforms & this->surfaceTransform))
		this->surfaceTransform = this->surfaceCapabilities.currentTransform;
}

void Surface::setFormat(vk::PhysicalDevice& device){
	vk::SurfaceFormatKHR desiredFormat;
	desiredFormat.format		= {};
	desiredFormat.colorSpace	= {};

	std::vector<vk::SurfaceFormatKHR> surfaceFormatArr = device.getSurfaceFormatsKHR(this->surface);
	if(surfaceFormatArr.size() > 0){
		if( (1 == surfaceFormatArr.size()) && (vk::Format::eUndefined == surfaceFormatArr[0].format) ) {
			this->surfaceFormat.format = desiredFormat.format;
			this->surfaceFormat.colorSpace = desiredFormat.colorSpace;

		}else{
			bool find = false;
			for( vk::SurfaceFormatKHR& item: surfaceFormatArr){
				if(item.format == desiredFormat.format && item.colorSpace == desiredFormat.colorSpace){
					this->surfaceFormat.format		= item.format;
					this->surfaceFormat.colorSpace	= item.colorSpace;
					find = true;
					break;
				}
			}
			if(!find){
				for(const vk::SurfaceFormatKHR& item: surfaceFormatArr){
					if(item.format == desiredFormat.format ){
						this->surfaceFormat.format		= item.format;
						this->surfaceFormat.colorSpace	= item.colorSpace;
						find = true;
						break;
					}
				}
				if(!find){
					this->surfaceFormat.format		= surfaceFormatArr[0].format;
					this->surfaceFormat.colorSpace	= surfaceFormatArr[0].colorSpace;
				}
			}
		}
	}else
		std::runtime_error("ERROR: surface format not support");
}









