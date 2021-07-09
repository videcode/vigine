#pragma once

#include "api.h"
#include API_INTERFACE_IWINDOW
#include API_INTERFACE_IRENDER
#include API_INTERFACE_IEVENT

#include <stdio.h>
#include <iostream>
#include <string>
#include <type_traits>

#include "x11.h"

namespace subsystem{
	namespace os {
		class Window: public api::iWindow{

			private:
				X11::Display*				 dpy; //
				X11::Window                  root; //
				X11::XVisualInfo*			 vi;  //
				X11::Colormap                cmap; //
				X11::XSetWindowAttributes    swa;  //
				X11::Window                  win;  //
				X11::XWindowAttributes       gwa;
				X11::XEvent                  xev;


			public:


				Window();
				virtual ~Window();


				// interface methods
				void init()			override;

				void width(int w)	override {this->width_ = w;}
				void height(int h)	override {this->height_ = h;}
				int  width()		override {return this->width_;}
				int  height()		override {return this->height_;}
				void run()			override;
				void render(api::iRender* pRendIn)	override{this->pRend = pRendIn;}
				void Delete()		override {};
				void event(api::iEvent* pEventIn, api::WINDOW_EVENT evtype) override{

					if (evtype == api::WINDOW_EVENT::init){

						this->pEventInit = pEventIn;
					}else if (evtype == api::WINDOW_EVENT::close){

						this->pEventClose = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::mouseClickLeft){

						this->pEventMouseClickLeft = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::mouseClickRight){

						this->pEventMouseClickRight = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::mouseClickWheel){

						this->pEventMouseClickWheel = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::mouseWheelUp){

						this->pEventMouseWheelUp = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::mouseWheelDown){

						this->pEventMouseWheelDown = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::keyPress){

						this->pEventKeyPress = pEventIn;

					}else if (evtype == api::WINDOW_EVENT::resize){

						this->pEventResize = pEventIn;

					} else
						std::runtime_error("api::WINDOW_EVENT are not recognized in func void Window::event(api::iEvent* pEventIn, api::WINDOW_EVENT evtype)");
				}

				// self methods
				template<typename T>
				T xlib(){
					if constexpr (std::is_same_v<T, X11::Display*>)
					        return this->dpy;
					else if constexpr (std::is_same_v<T, X11::Window>)
					        return this->root;
					else
					    std::runtime_error("ERROR: Window xlib() type T not good");
				}

			protected:
				int width_      = 1000;
				int height_     = 600;

				api::iEvent*	pEventInit;
				api::iEvent*	pEventClose;
				api::iEvent*	pEventResize;

				api::iEvent*	pEventMouseClickLeft;
				api::iEvent*	pEventMouseClickRight;
				api::iEvent*	pEventMouseClickWheel;
				api::iEvent*	pEventMouseWheelUp;
				api::iEvent*	pEventMouseWheelDown;

				api::iEvent*	pEventKeyPress;

				api::iRender*	pRend{nullptr};
		};
	}
}


namespace api{
	template<>
	class Impl< iWindow >{
		public:
			static iWindow*  make(){
				return new subsystem::os::Window();
			}

		private:
			Impl< iWindow >()=delete;
			~Impl< iWindow >()=delete;
	};
}
