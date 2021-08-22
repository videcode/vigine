#include "instance.h"

using namespace graphics::vulkan;

Instance::Instance() {}

void Instance::init() {
  std::cout << "Instance init" << std::endl;

  this->appInfo.sType = vk::StructureType::eApplicationInfo;
  this->appInfo.pNext = nullptr;
  this->appInfo.pApplicationName = "visual deep code";
  this->appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  this->appInfo.pEngineName = "vigine";
  this->appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);
  this->appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);

  std::vector<const char *> layersNames = {
      "VK_LAYER_KHRONOS_validation",
  };
  std::vector<const char *> desiredExtensions = {
      VK_EXT_DEBUG_REPORT_EXTENSION_NAME, "VK_KHR_display",
      "VK_KHR_get_display_properties2", "VK_KHR_get_surface_capabilities2",
      "VK_KHR_surface",
      //"VK_KHR_surface_protected_capabilities",
      "VK_KHR_xlib_surface", "VK_EXT_acquire_xlib_display",
      "VK_EXT_direct_mode_display", "VK_EXT_display_surface_counter"};

  this->createInfo.sType = vk::StructureType::eInstanceCreateInfo;
  this->createInfo.pNext = nullptr;
  this->createInfo.flags = {};
  this->createInfo.pApplicationInfo = &this->appInfo;
  this->createInfo.enabledLayerCount = layersNames.size();
  this->createInfo.ppEnabledLayerNames = layersNames.data();
  this->createInfo.enabledExtensionCount = desiredExtensions.size();
  this->createInfo.ppEnabledExtensionNames = desiredExtensions.data();

  this->inst = vk::createInstance(this->createInfo, nullptr);

  //

  //

  // this->surface.initAfrerDeviceInit(device);
  // this->device.createSwapchain(this->surface);
  // this->device.createPipelineGraphic();
}
