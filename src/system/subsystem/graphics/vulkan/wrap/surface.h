#pragma once

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

namespace graphics {
namespace vulkan {
class Surface {
public:
  Surface();
  void destroy(vk::Instance &inst) { inst.destroySurfaceKHR(this->surface); }

  void initBeforeDeviceInit(vk::Instance &);
  void initAfrerDeviceInit(vk::PhysicalDevice &);
  void xlibData(Window, Display *);
  void presentModeKHR(vk::PhysicalDevice &);
  void capabilitiesKHR(vk::PhysicalDevice &);
  void imageUsagesFlags();
  void supportedTransforms();
  void setFormat(vk::PhysicalDevice &);

  vk::SurfaceKHR &get() { return this->surface; }
  vk::XlibSurfaceCreateInfoKHR& getInfo() {this->createInfo;}
  vk::SurfaceFormatKHR &getFormat() { return this->surfaceFormat; }
  uint32_t getMinImageCount() { return this->minImageCount; }
  vk::Extent2D getImageSize() { return this->imageSize; }
  vk::ImageUsageFlags getImageUsage() { return this->imageUsage; }
  vk::PresentModeKHR getPresentMode() { return this->presentMode; }
  vk::SurfaceTransformFlagBitsKHR getTransform() {
    return this->surfaceTransform;
  }

private:
  vk::SurfaceKHR surface;
  vk::XlibSurfaceCreateInfoKHR createInfo;
  vk::PresentModeKHR presentMode{};
  vk::SurfaceCapabilitiesKHR surfaceCapabilities{};
  vk::SurfaceFormatKHR surfaceFormat{};

  Window win{0};
  Display *dpy{nullptr};

  uint32_t minImageCount{0};
  vk::Extent2D imageSize{640, 480};
  vk::ImageUsageFlags imageUsage{vk::ImageUsageFlagBits::eColorAttachment};
  vk::SurfaceTransformFlagBitsKHR surfaceTransform{
      vk::SurfaceTransformFlagBitsKHR::eIdentity};
};
} // namespace vulkan
} // namespace graphics
