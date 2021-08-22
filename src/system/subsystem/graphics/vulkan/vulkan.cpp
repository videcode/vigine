#include "vulkan.h"

graphics::vulkan::Vulkan::Vulkan() {}

void graphics::vulkan::Vulkan::init() {
  // 01. create vulkan instance
  this->createInstance();
  // 02. setup debug callbacks
  this->setupDebugCallbacks();
  // 03. create surface
  this->createSurface();
  // 04. list physical devices
  // 05. pick right physical device
  this->selectPhysicalDevice();
  // 06. create logical device
  this->createLogicalDevice();
  // 07. create uniform variable buffers
  this->createUniformVariableBuffers();
  // 08. create vertex data buffers
  // 09. create texture sampler
  // 10. create texture images
  // 11. create swap chain
  // 12. create depth and stencil images
  // 13. create renderpass
  // 14. create framebuffer(s)
  // 15. create descriptor set pool
  // 16. create command buffer pool
  // 17. create command buffer(s)
  // 18. read shaders
  // 19. create descriptor set layouts
  // 20. create and populate descriptor sets
  // 21. create graphics pipeline(s)
  // 22. update-render-update-render
}

void graphics::vulkan::Vulkan::xlibData(X11::Window win, X11::Display *dpy) {
  this->surface.xlibData(win, dpy);
}

void graphics::vulkan::Vulkan::createInstance() { this->instance.init(); }

void graphics::vulkan::Vulkan::createSurface() {

  this->surface.initBeforeDeviceInit(this->instance.get());
}

void graphics::vulkan::Vulkan::createLogicalDevice() {
  this->device.createLogicalDevice();
}

void graphics::vulkan::Vulkan::createUniformVariableBuffers() {

  this->buffer.init(this->device.getLogical());
}

void graphics::vulkan::Vulkan::setupDebugCallbacks() {

  PFN_vkCreateDebugReportCallbackEXT vk_vkCreateDebugReportCallbackEXT =
      (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(
          this->instance.get(), "vkCreateDebugReportCallbackEXT");

  // report callbacks
  VkDebugReportCallbackEXT vk_debugReportCallbackEXT;

  {
    VkDebugReportCallbackCreateInfoEXT vk_debugReportCallbackCreateInfoEXT;

    {
      vk_debugReportCallbackCreateInfoEXT.sType = VkStructureType::
          VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
      vk_debugReportCallbackCreateInfoEXT.pNext = nullptr;
      vk_debugReportCallbackCreateInfoEXT.flags =
          0 /*
VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT |
VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT*/
          ;
      vk_debugReportCallbackCreateInfoEXT.pfnCallback =
          [](VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType,
             uint64_t object, size_t location, int32_t messageCode,
             const char *pLayerPrefix, const char *pMessage,
             void *pUserData) -> VkBool32 {
        std::cout << "(";
        if ((flags &
             VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT) !=
            0)
          std::cout << "INFO";
        if ((flags &
             VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
          std::cout << "WARNING";
        if ((flags & VkDebugReportFlagBitsEXT::
                         VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
          std::cout << "PERFORMANCE";
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT) !=
            0)
          std::cout << "DEBUG";
        if ((flags & VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT) !=
            0)
          std::cout << "ERROR";
        std::cout << ")";
        std::cout << "{" << pLayerPrefix << "} " << pMessage << std::endl;
        return VK_FALSE;
      };
      vk_debugReportCallbackCreateInfoEXT.pUserData = nullptr;
    }
    vk_vkCreateDebugReportCallbackEXT(this->instance.get(),
                                      &vk_debugReportCallbackCreateInfoEXT,
                                      nullptr, &vk_debugReportCallbackEXT);
  }
}

void graphics::vulkan::Vulkan::selectPhysicalDevice() {
  this->device.init(this->instance, this->surface);
}
