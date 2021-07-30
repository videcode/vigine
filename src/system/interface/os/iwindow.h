#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IEVENT
#include API_INTERFACE_IRENDER

#include <concepts>
#include <type_traits>
#include <memory>

namespace api{

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


	template<typename tWindow>
	concept cWindow = requires(tWindow obj, int i, iRender* y, iEvent* pEventIn, WINDOW_EVENT evtype) {
	    requires std::is_base_of_v<iWindow, tWindow>;
	    obj.init();
	    { obj.width(i)  } -> std::same_as<void>;
	    { obj.height(i) } -> std::same_as<void>;
	    { obj.width()	} -> std::same_as<int>;
	    { obj.height()  } -> std::same_as<int>;
	    { obj.run()	    } -> std::same_as<void>;
	    { obj.Delete()  } -> std::same_as<void>;
	    { obj.render(y) } -> std::same_as<void>;
	    { obj.event(pEventIn, evtype) } -> std::same_as<void>;

    };
}
