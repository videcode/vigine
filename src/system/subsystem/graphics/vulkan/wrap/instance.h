#pragma once

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "api.h"
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IFIGURE

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR

#include <vulkan/vulkan.hpp>

namespace graphics {
namespace vulkan {
class Instance {
public:
  Instance();
  ~Instance() { std::cout << "~Instance(){}" << std::endl; }
  void destroy() {
    this->inst.destroy();
    std::cout << "Instance::destroy(){}" << std::endl;
  }

  void init();

  vk::Instance& get(){return this->inst;}

private:
  vk::ApplicationInfo appInfo;
  vk::InstanceCreateInfo createInfo;
  vk::Instance inst{nullptr};

};
} // namespace vulkan
} // namespace graphics
