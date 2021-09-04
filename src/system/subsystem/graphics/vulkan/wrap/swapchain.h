#pragma once

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "surface.h"
#include <memory>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace graphics {
namespace vulkan {
class Swapchain {
public:
  Swapchain();
  ~Swapchain() {}
  void destroy(std::shared_ptr<vk::Device> logicDevice) {
    for (vk::ImageView &item : this->vImageViews)
      logicDevice->destroyImageView(item);
  }
  void init(std::shared_ptr<vk::Device> logicDevice, Surface &);
  void imageIndex(std::shared_ptr<vk::Device>);
  vk::SwapchainKHR &get() { return this->swapchain; }
  vk::SwapchainCreateInfoKHR& getInfo(){return this->createInfo;}

private:
  vk::SwapchainKHR swapchain;
  vk::SwapchainCreateInfoKHR createInfo;
  std::vector<vk::Image> vImages;
  std::vector<vk::ImageView> vImageViews;

  uint32_t currentImageIndex{0};

  void createImages(std::shared_ptr<vk::Device>, Surface &);
};
} // namespace vulkan
} // namespace graphics
