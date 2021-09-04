#pragma once

#include "api.h"
#include API_INTERFACE_IRENDER
#include API_INTERFACE_IEVENT
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IFIGURE

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;

#include <array>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

#include "system/subsystem/core/base.h"

#include "vulkanapi.h"

namespace graphics {
namespace vulkan {

void print_prop(vk::PhysicalDevice &, std::string str = "");
void print_prop(vk::PhysicalDeviceMemoryProperties &);
void print_prop(vk::PhysicalDeviceFeatures &, std::string str = "");
void print_prop(vk::LayerProperties &);
void print_prop(vk::ExtensionProperties &);
void print_prop(vk::QueueFamilyProperties &, std::string str = "");
void print_prop(std::vector<vk::PresentModeKHR> &, std::string str = "");
void print_prop(vk::SurfaceCapabilitiesKHR &, std::string str = "");
void print_prop(vk::SurfaceFormatKHR &, std::string str = "");

template <typename T, typename T2>
void print_bit(T var, T2 var2, std::string, bool print_if_eual = false);
template <typename T, typename T2>
void print_equal(T var, T2 var2, std::string);
template <int n, typename T> void print_extent(T var, std::string);

class Render : public api::iRender {
public:
  Render();
  ~Render();

  void init() override;
  void reg(std::shared_ptr<api::iFigure>) override;
  void draw() override;
  void upd() override;

  // self functions presenting
  void wh(int w, int h) override {
    this->width = w;
    this->height = h;
  }
  void camera(std::shared_ptr<api::iCamera> pCamIn) override {
    this->pCam_ = pCamIn;
  }
  void Delete() override { this->vk.destroy(); };

  template <api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
  void windowDisplaySystemData(Args... argv) {
    if (wds == api::WINDOW_DISPLAY_SYSTEM::x11)
      this->xlibInit(argv...);
    else
      std::runtime_error("ERROR: in Render windowDisplaySystemData(Args... "
                         "argv) 'WINDOW_DISPLAY_SYSTEM is not x11' ");
  }

protected:
private:
  Vulkan	vk;
  std::shared_ptr<api::iCamera> pCam_;
  // other
  int width{0};
  int height{0};

  void xlibInit(X11::Window, X11::Display *);
};

// https://gamedev.ru/code/articles/VulkanTriangle
template <api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
class RenderHelper : public api::iRenderHelper<wds, Args...> {
public:
  RenderHelper<wds, Args...>(){};
  virtual ~RenderHelper<wds, Args...>() {
    std::cout << "RenderHelper destructor" << std::endl;
  };

  void windowDisplaySystemData(Args... argv) override {
    this->pRend->template windowDisplaySystemData<wds>(argv...);
  }

  void Delete() override {}

protected:
  virtual void render(api::iRender *pRendIn) override {
    this->pRend = static_cast<Render *>(pRendIn);
  }

  Render *pRend{nullptr};
};
} // namespace vulkan
} // namespace graphics

namespace api {

template <> class Impl<api::iRender> {
public:
  static std::unique_ptr<api::iRender> make() {
    namespace ns = graphics::vulkan;
    using iHelper =
        iRenderHelper<WINDOW_DISPLAY_SYSTEM::x11, X11::Window, X11::Display *>;
    using HelperImpl = ns::RenderHelper<WINDOW_DISPLAY_SYSTEM::x11, X11::Window,
                                        X11::Display *>;

    std::unique_ptr<api::iRender> piRend(
        static_cast<api::iRender *>(new ns::Render()));
    std::shared_ptr<iHelper> piRendHelper(
        static_cast<iHelper *>(new HelperImpl()));
    piRend->helper(piRendHelper);

    return piRend;
  }

private:
  Impl<api::iRender>();
  ~Impl<api::iRender>();
};
} // namespace api
