#include "surface.h"

using namespace graphics::vulkan;

Surface::Surface(){

}

void Surface::init(vk::Instance& inst){

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

void Surface::xlibData(Window win, Display* dpy){
	this->win = win;
	this->dpy = dpy;
}

void Surface::presentModeKHR(vk::PresentModeKHR presentMode){
	this->presentMode = presentMode;
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








