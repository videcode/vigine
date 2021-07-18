#include "swapchain.h"

using namespace graphics::vulkan;

Swapchain::Swapchain(){

}

void Swapchain::init(vk::Device& logicDevice, Surface& surface){
	// swapchain
	this->createInfo.sType	= vk::StructureType::eSwapchainCreateInfoKHR;
	this->createInfo.pNext	= nullptr;
	this->createInfo.flags	= {};
	this->createInfo.surface			= surface.get();
	this->createInfo.minImageCount		= surface.getMinImageCount();
	this->createInfo.imageFormat		= surface.getFormat().format;
	this->createInfo.imageColorSpace	= surface.getFormat().colorSpace;
	this->createInfo.imageExtent		= surface.getImageSize();
	this->createInfo.imageArrayLayers	= 1;
	this->createInfo.imageUsage			= surface.getImageUsage();
	this->createInfo.imageSharingMode	= vk::SharingMode::eExclusive;
	this->createInfo.queueFamilyIndexCount	= 0;
	this->createInfo.pQueueFamilyIndices	= nullptr;
	this->createInfo.preTransform		= surface.getTransform();
	this->createInfo.compositeAlpha		= vk::CompositeAlphaFlagBitsKHR::eOpaque;
	this->createInfo.presentMode		= surface.getPresentMode();
	this->createInfo.clipped			= VK_TRUE;
	this->createInfo.oldSwapchain		= nullptr;

	this->swapchain = logicDevice.createSwapchainKHR(this->createInfo);
	this->vImages	= logicDevice.getSwapchainImagesKHR(this->swapchain);
	this->imageIndex(logicDevice);
}

void Swapchain::imageIndex(vk::Device& logicDevice){

	uint32_t imageIndex = 0;
	vk::Result res = logicDevice.acquireNextImageKHR( this->swapchain, 2000000000, nullptr, nullptr, &imageIndex );

	if(res == vk::Result::eSuccess || res == vk::Result::eSuboptimalKHR)
		this->currentImageIndex = imageIndex;
	else
		std::runtime_error("ERROR: swapchain image index");
}









