#pragma once

#include "api.h"
#include API_INTERFACE_IWINDOW
#include API_INTERFACE_IRENDER
#include API_INTERFACE_IEVENT

#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <type_traits>

#include <GLFW/glfw3.h>

namespace subsystem {
namespace os {
namespace glfw {

class Window : public api::iWindow {
public:
  using shrdEvt = std::shared_ptr<api::iEvent>;

  Window();
  void init() override;

  void width(int w) override { this->width_ = w; }
  void height(int h) override { this->height_ = h; }
  int width() override { return this->width_; }
  int height() override { return this->height_; }
  void run() override;
  void render(std::shared_ptr<api::iRender> pRendIn) override {
    this->pRend = pRendIn;
  }
  void Delete() override{};
  void event(shrdEvt pEventIn, api::WINDOW_EVENT evtype) override {
	  if (evtype == api::WINDOW_EVENT::init) {
							Window::pEventInit = pEventIn;
						}else if (evtype == api::WINDOW_EVENT::close){

							Window::pEventClose = pEventIn;
    } else if (evtype == api::WINDOW_EVENT::close) {
							Window::pEventMouseClickLeft = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickLeft) {
							Window::pEventMouseClickRight = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickRight) {
							Window::pEventMouseClickWheel = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickWheel) {
							Window::pEventMouseWheelUp = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseWheelUp) {
							Window::pEventMouseWheelDown = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseWheelDown) {
							Window::pEventKeyPress = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::keyPress) {
							Window::pEventResize = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::resize) {

      this->pEventResize = pEventIn;

    } else
      std::runtime_error("api::WINDOW_EVENT are not recognized in func void "
                         "Window::event(api::iEvent* pEventIn, "
                         "api::WINDOW_EVENT evtype)");
  }


					// non interface functions
					template<api::WINDOW_EVENT evt>
					static shrdEvt event(){

						if constexpr (evt == api::WINDOW_EVENT::init){
							return Window::pEventInit;
						}

						if constexpr (evt == api::WINDOW_EVENT::close){
							return Window::pEventClose;
						}

						if constexpr (evt == api::WINDOW_EVENT::resize){
							return Window::pEventResize;
						}


						if constexpr (evt == api::WINDOW_EVENT::mouseClickLeft){
							return Window::pEventMouseClickLeft;
						}

						if constexpr (evt == api::WINDOW_EVENT::mouseClickRight){
							return Window::pEventMouseClickRight;
						}

						if constexpr (evt == api::WINDOW_EVENT::mouseClickWheel){
							return Window::pEventMouseClickWheel;
						}

						if constexpr (evt == api::WINDOW_EVENT::mouseWheelUp){
							return Window::pEventMouseWheelUp;
						}

						if constexpr (evt == api::WINDOW_EVENT::mouseWheelDown){
							return Window::pEventMouseWheelDown;
						}

						if constexpr (evt == api::WINDOW_EVENT::keyPress){
							return Window::pEventKeyPress;
						}
					}

				protected:
					int width_      = 1000;
					int height_     = 600;

					static Window::shrdEvt	pEventInit;
					static Window::shrdEvt	pEventClose;
					static Window::shrdEvt	pEventResize;

					static Window::shrdEvt	pEventMouseClickLeft;
					static Window::shrdEvt	pEventMouseClickRight;
					static Window::shrdEvt	pEventMouseClickWheel;
					static Window::shrdEvt	pEventMouseWheelUp;
					static Window::shrdEvt	pEventMouseWheelDown;

					static Window::shrdEvt	pEventKeyPress;


  std::shared_ptr<api::iRender> pRend;

private:
  GLFWwindow *pWindowGLFW{nullptr};
};
} // namespace glfw
} // namespace os
} // namespace subsystem

namespace api {
template <> class Impl<iWindow> {
public:
  static std::unique_ptr<iWindow> make() {
    return std::unique_ptr<iWindow>(
        static_cast<iWindow *>(new subsystem::os::glfw::Window()));
  }

private:
  Impl<iWindow>() = delete;
  ~Impl<iWindow>() = delete;
};
} // namespace api
