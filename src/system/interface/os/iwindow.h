#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IEVENT
#include API_INTERFACE_IRENDER

#include <concepts>
#include <type_traits>
#include <memory>

#include "api/core/event.h"

namespace api{

	enum class WINDOW_DISPLAY_SYSTEM{
		none = 0,
		x11,
		xcb,
		wayland,
		other
	};

	enum class WINDOW_EVENT{
		init = 0,
		close,
		resize,

		mouseClickLeft,
		mouseClickRight,
		mouseClickWheel,
		mouseWheelUp,
		mouseWheelDown,

		keyPress
	};

	struct WindowEventType{
		using init		= void();
		using close		= void();
		using resize	= void(int, int);

		struct Mouse{
			struct Button{
				struct Left{
					using click	= void(int, int);
				};
				struct Right{
					using click	= void(int, int);
				};
				struct Wheel{
					using up	= void(int, int);
					using down	= void(int, int);
					using click = void(int, int);
				};
			};
		};
		struct Keyboard{
			struct Key{
				using press		= void (int);
				using release	= void (int);
			};
		};

		template<WINDOW_EVENT wevt>
		struct Get;

		template<>
		struct Get<WINDOW_EVENT::init>{
			using type = WindowEventType::init;
		};
		template<>
		struct Get<WINDOW_EVENT::close>{
			using type = WindowEventType::close;
		};
		template<>
		struct Get<WINDOW_EVENT::resize>{
			using type = WindowEventType::resize;
		};


		template<>
		struct Get<WINDOW_EVENT::mouseClickLeft>{
			using type = WindowEventType::Mouse::Button::Left::click;
		};
		template<>
		struct Get<WINDOW_EVENT::mouseClickRight>{
			using type = WindowEventType::Mouse::Button::Right::click;
		};
		template<>
		struct Get<WINDOW_EVENT::mouseClickWheel>{
			using type = WindowEventType::Mouse::Button::Wheel::click;
		};
		template<>
		struct Get<WINDOW_EVENT::mouseWheelUp>{
			using type = WindowEventType::Mouse::Button::Wheel::up;
		};
		template<>
		struct Get<WINDOW_EVENT::mouseWheelDown>{
			using type = WindowEventType::Mouse::Button::Wheel::down;
		};


		template<>
		struct Get<WINDOW_EVENT::keyPress>{
			using type = WindowEventType::Keyboard::Key::press;
		};

	};

	template<WINDOW_EVENT evnt>
	using winevnt_t = typename WindowEventType::Get<evnt>::type;

	template<typename TWindow>
	concept cWindow = requires(
	                      TWindow obj,
	                      std::shared_ptr<api::Event<winevnt_t<WINDOW_EVENT::init>>> spEvent,
	                      std::shared_ptr<api::Event<winevnt_t<WINDOW_EVENT::keyPress>>> spEvent2,
	                      std::shared_ptr<api::Event<winevnt_t<WINDOW_EVENT::mouseClickLeft>>> spEvent3,
	                      int width
	) {
	    requires cBase<TWindow>;

	    { obj.init()		}			-> std::same_as<void>;
	    { obj.width(width)  }			-> std::same_as<void>;
	    { obj.height(width) }			-> std::same_as<void>;
	    { obj.width()	}				-> std::same_as<int>;
	    { obj.height()  }				-> std::same_as<int>;
	    { obj.run()	    }				-> std::same_as<void>;
	    { obj.template event<WINDOW_EVENT::init>(spEvent)				}	-> std::same_as<void>;
	    { obj.template event<WINDOW_EVENT::keyPress>(spEvent2)			}	-> std::same_as<void>;
	    { obj.template event<WINDOW_EVENT::mouseClickLeft>(spEvent3)	}	-> std::same_as<void>;

    };

	template<typename TWindow> requires cWindow<TWindow>
	using window_t = TWindow;



/*
	template<api::WINDOW_EVENT eventType, typename TSlot, typename... Args>
	class iWindowHelper;



	class iWindow: public iBase{
		public:

			using init_func_t    = void ();
			using close_func_t   = void ();
			using resize_func_t  = void (int, int);

			using mouseClickLeft_func_t  = void (int, int);
			using mouseClickRight_func_t = void (int, int);
			using mouseClickWheel_func_t = void (int, int);
			using mouseWheelUp_func_t    = void (int, int);
			using mouseWheelDown_func_t  = void (int, int);

			using keyPress_func_t  = void (int);

			// event helper
			using iEVENT_HELPER_INIT		= api::iEventHelper<api::iWindow::init_func_t>;
			using iEVENT_HELPER_CLOSE		= api::iEventHelper<api::iWindow::close_func_t>;
			using iEVENT_HELPER_RESIZE		= api::iEventHelper<api::iWindow::resize_func_t, int, int>;
			using iEVENT_HELPER_MOUSE_CL	= api::iEventHelper<api::iWindow::mouseClickLeft_func_t, int, int>;
			using iEVENT_HELPER_MOUSE_CR	= api::iEventHelper<api::iWindow::mouseClickRight_func_t, int, int>;
			using iEVENT_HELPER_MOUSE_CW	= api::iEventHelper<api::iWindow::mouseClickWheel_func_t, int, int>;
			using iEVENT_HELPER_MOUSE_WUP	= api::iEventHelper<api::iWindow::mouseWheelUp_func_t, int, int>;
			using iEVENT_HELPER_MOUSE_WDOWN = api::iEventHelper<api::iWindow::mouseWheelDown_func_t, int, int>;
			using iEVENT_HELPER_KEYPRESS	= api::iEventHelper<api::iWindow::keyPress_func_t, int>;




			virtual void 	init()					= 0;
			virtual void 	width(int)				= 0;
			virtual void 	height(int)				= 0;
			virtual int   	width()					= 0;
			virtual int   	height()				= 0;
			virtual void	run()					= 0;
			virtual void 	render(std::shared_ptr<iRender>)  = 0;
			virtual void	event(std::shared_ptr< iEvent >, api::WINDOW_EVENT) = 0;
	};


	template<api::WINDOW_EVENT eventType, typename TSlot, typename... Args>
	class iWindowHelper{
		public:
			virtual void event(TSlot*)		= 0;

		protected:
			virtual void window(iWindow*)	= 0;

		friend iWindow;
	};
*/

}
