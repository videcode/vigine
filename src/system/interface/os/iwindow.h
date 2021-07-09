#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IEVENT
#include API_INTERFACE_IRENDER

#include <concepts>
#include <type_traits>

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
			virtual void 	render(iRender*)		= 0;
			virtual void	event(iEvent*, api::WINDOW_EVENT) = 0;
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






/*


	template<cWindow T>
	class iWindow: public iBase {
		public:





		protected:
			iWindow<T>()	= default;
			~iWindow<T>()	= default;


			api::iEvent<mouseClickLeft_func_t, int, int>*	pEventInit;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>*	pEventClose;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>*	pEventResize;

			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>*	pEventMouseClickLeft;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>* pEventMouseClickRight;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>* pEventMouseClickWheel;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>*	pEventMouseWheelUp;
			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>*	pEventMouseWheelDown;

			api::iEvent<api::iWindow::mouseClickLeft_func_t, int, int>* pEventKeyPress;

			api::iRender*	pRend{nullptr};

	};
}





    class iWindow{
        public:
            using init_t    = void ();
            using close_t   = void ();
            using resize_t  = void (int, int);

            using mouseClickLeft_t  = void (int, int);
            using mouseClickRight_t = void (int, int);
            using mouseClickWheel_t = void (int, int);
            using mouseWheelUp_t    = void (int, int);
            using mouseWheelDown_t  = void (int, int);

            using keyPress_t  = void (int);

            enum class EVENT_TYPE{
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

            iWindow();
            virtual ~iWindow();

			virtual void init()         { this->evInit.on();};
            virtual void width(int)     = 0;
            virtual void height(int)    = 0;
            virtual int  width()        = 0;
            virtual int  height()       = 0;
            virtual void run()          = 0;
            virtual void irender(render::iRender* pRend){
                std::cout << "irender(render::iRender* pRend)" << std::endl;
                this->pRend = pRend;
            }

            virtual render::iRender* irender(){
                return this->pRend;
            }

            template<EVENT_TYPE evtype, typename T>
            auto& event(T evt){

                if constexpr(evtype == EVENT_TYPE::init){

                    static_assert(!std::is_same_v<T, init_t>);

                    this->evInit.handler(evt);
                    return this->evInit;

                }else if constexpr(evtype == EVENT_TYPE::close){

                    static_assert(!std::is_same_v<T, close_t>);

                    this->evClose.handler(evt);
                    return this->evClose;

                }else if constexpr(evtype == EVENT_TYPE::mouseClickLeft){

                    static_assert(!std::is_same_v<T, mouseClickLeft_t>);

                    this->evMouseClickLeft.handler(evt);
                    return this->evMouseClickLeft;

                }else if constexpr(evtype == EVENT_TYPE::mouseClickRight){

                    static_assert(!std::is_same_v<T, mouseClickRight_t>);

                    this->evMouseClickRight.handler(evt);
                    return this->evMouseClickRight;

                }else if constexpr(evtype == EVENT_TYPE::mouseClickWheel){

                    static_assert(!std::is_same_v<T, mouseClickWheel_t>);

                    this->evMouseClickWheel.handler(evt);
                    return this->evMouseClickWheel;

                }else if constexpr(evtype == EVENT_TYPE::mouseWheelUp){

                    static_assert(!std::is_same_v<T, mouseWheelUp_t>);

                    this->evMouseWheelUp.handler(evt);
                    return this->evMouseWheelUp;

                }else if constexpr(evtype == EVENT_TYPE::mouseWheelDown){

                    static_assert(!std::is_same_v<T, mouseWheelDown_t>);

                    this->evMouseWheelDown.handler(evt);
                    return this->evMouseWheelDown;

                }else if constexpr(evtype == EVENT_TYPE::keyPress){

                    static_assert(!std::is_same_v<T, keyPress_t>);

                    this->evKeyPress.handler(evt);
                    return this->evKeyPress;

                }else if constexpr(evtype == EVENT_TYPE::resize){

                    static_assert(!std::is_same_v<T, resize_t>);

                    this->evResize.handler(evt);
                    return this->evResize;

                } else
                    return nullptr;
            };


        protected:
			int width_      = 1000;
			int height_     = 600;

            Event<init_t>   evInit;
            Event<close_t>  evClose;
            Event<resize_t> evResize;

            Event<mouseClickLeft_t>     evMouseClickLeft;
            Event<mouseClickRight_t>    evMouseClickRight;
            Event<mouseClickWheel_t>    evMouseClickWheel;
            Event<mouseWheelUp_t>       evMouseWheelUp;
            Event<mouseWheelDown_t>     evMouseWheelDown;

            Event<keyPress_t>     evKeyPress;

            render::iRender* pRend{nullptr};

        private:
    };
}

*/
