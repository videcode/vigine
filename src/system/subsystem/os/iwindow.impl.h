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

#include "x11/x11.h"

#include "api/core/base.h"
#include "interface/os/iwindow.h"
#include "api/core/event.h"
#include "api/core/universaldata.h"


namespace subsystem{
	namespace os {
		class Window{
				template<typename T>
				using sp = std::shared_ptr<T>;

				struct ScreenSize{
					int width{600};
					int height{500};
				};

				X11::Display *dpy;             //
				X11::Window root;              //
				X11::XVisualInfo *vi;          //
				X11::Colormap cmap;            //
				X11::XSetWindowAttributes swa; //
				X11::Window win;               //
				X11::XWindowAttributes gwa;
				X11::XEvent xev;

			public:

				void init();
				void width(int w){this->size.width = w;}
				void height(int h){this->size.height = h;}
				int  width(){return this->size.width;}
				int  height(){this->size.height;}
				void run();

				template<api::WINDOW_EVENT evnt, typename TFuncSignature>
				void event(sp<api::Event<TFuncSignature>> evt){

					if constexpr (evnt == api::WINDOW_EVENT::mouseClickLeft){
						this->spMouseLeftClick = evt;
						api::print("add mouse click event");
					}
					if constexpr (evnt == api::WINDOW_EVENT::displaySystem){
						this->spDisplaySystem = evt;
						api::print("add display system event");
					}
					if constexpr (evnt == api::WINDOW_EVENT::init){
						this->spWindowInit = evt;
						api::print("add window init event");
					}
				}

				void destroy();
			private:
				ScreenSize size{};

				sp<api::WindowEventMouseLeftClick> spMouseLeftClick;
				sp<api::WindowEventDisplaySystem> spDisplaySystem;
				sp<api::WindowEventInit> spWindowInit;
		};

		//api::window_t<Window, api::Event<void()> > test;
	}
}

/*
namespace subsystem {
namespace os {
class Window : public api::iWindow {

private:
  X11::Display *dpy;             //
  X11::Window root;              //
  X11::XVisualInfo *vi;          //
  X11::Colormap cmap;            //
  X11::XSetWindowAttributes swa; //
  X11::Window win;               //
  X11::XWindowAttributes gwa;
  X11::XEvent xev;

public:
  using shrdEvt = std::shared_ptr<api::iEvent>;

  Window();
  virtual ~Window();

  // interface methods
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

      this->pEventInit = pEventIn;
    } else if (evtype == api::WINDOW_EVENT::close) {

      this->pEventClose = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickLeft) {

      this->pEventMouseClickLeft = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickRight) {

      this->pEventMouseClickRight = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseClickWheel) {

      this->pEventMouseClickWheel = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseWheelUp) {

      this->pEventMouseWheelUp = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::mouseWheelDown) {

      this->pEventMouseWheelDown = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::keyPress) {

      this->pEventKeyPress = pEventIn;

    } else if (evtype == api::WINDOW_EVENT::resize) {

      this->pEventResize = pEventIn;

    } else
      std::runtime_error("api::WINDOW_EVENT are not recognized in func void "
                         "Window::event(api::iEvent* pEventIn, "
                         "api::WINDOW_EVENT evtype)");
  }

  // self methods
  template <typename T> T xlib() {
    if constexpr (std::is_same_v<T, X11::Display *>)
      return this->dpy;
    else if constexpr (std::is_same_v<T, X11::Window>)
      return this->root;
    else
      std::runtime_error("ERROR: Window xlib() type T not good");
  }

protected:
  int width_ = 1000;
  int height_ = 600;

  shrdEvt pEventInit;
  shrdEvt pEventClose;
  shrdEvt pEventResize;

  shrdEvt pEventMouseClickLeft;
  shrdEvt pEventMouseClickRight;
  shrdEvt pEventMouseClickWheel;
  shrdEvt pEventMouseWheelUp;
  shrdEvt pEventMouseWheelDown;

  shrdEvt pEventKeyPress;

  std::shared_ptr<api::iRender> pRend;
};
} // namespace os
} // namespace subsystem

namespace api {
template <> class Impl<iWindow> {
public:
  static std::unique_ptr<iWindow> make() {
    return std::unique_ptr<iWindow>(
        static_cast<iWindow *>(new subsystem::os::Window()));
  }

private:
  Impl<iWindow>() = delete;
  ~Impl<iWindow>() = delete;
};
} // namespace api
*/
