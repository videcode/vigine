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
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

#include "device.h"
#include "surface.h"

namespace graphics {
namespace vulkan {
class Instance {
public:
  Instance();
  ~Instance() { std::cout << "~Instance(){}" << std::endl; }
  void destroy() {
    this->device.destroy();
    this->surface.destroy(this->inst);
    this->inst.destroy();
    std::cout << "Instance::destroy(){}" << std::endl;
  }

  void init();
  void xlibData(X11::Window, X11::Display *);
  void add(api::iFigure *);
  void add(api::iCamera *);
  void prepare();
  void work();

private:
  vk::ApplicationInfo appInfo;
  vk::InstanceCreateInfo createInfo;
  vk::Instance inst{nullptr};

  Device device;
  Surface surface;

  void debug();
};
} // namespace vulkan
} // namespace graphics
