#pragma once

#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

namespace graphics {
	namespace vulkan {
		class Surface{
			public:
				Surface();
				void init(vk::Instance&);
				void xlibData(Window, Display*);
				vk::SurfaceKHR& get(){return this->surface;}
				void presentModeKHR(vk::PresentModeKHR);
				void capabilitiesKHR(vk::PhysicalDevice&);
				void imageUsagesFlags();

				uint32_t		getMinImageCount()	{return this->minImageCount;}
				vk::Extent2D	getImageSize()		{return this->imageSize;}

			private:
				vk::SurfaceKHR					surface;
				vk::XlibSurfaceCreateInfoKHR	createInfo;
				vk::PresentModeKHR				presentMode	{};
				vk::SurfaceCapabilitiesKHR		surfaceCapabilities {};

				Window		win	{0};
				Display*	dpy	{nullptr};

				uint32_t			minImageCount	{0};
				vk::Extent2D		imageSize		{ 640, 480 };
				vk::ImageUsageFlags	imageUsage		{vk::ImageUsageFlagBits::eColorAttachment};
		};
	}
}
