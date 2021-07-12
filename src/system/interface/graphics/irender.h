#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IFIGURE
#include API_INTERFACE_ICAMERA

#include <any>
#include <memory>
#include <iostream>

namespace api{
	enum class WINDOW_DISPLAY_SYSTEM{
		none = 0,
		x11,
		xcb,
		wayland,
		other
	};

	template<typename tRender, typename tFigure, typename tCamera, typename tShader>
	concept cRender = requires(tRender obj, tFigure* obj2, tCamera* obj3, int x){
	    { obj.init()		}-> std::same_as<void>;
	    { obj.reg(obj2)		}-> std::same_as<void>;
	    { obj.draw()		}-> std::same_as<void>;
	    { obj.upd()			}-> std::same_as<void>;
	    { obj.wh(x, x)		}-> std::same_as<void>;
	    { obj.camera(obj3)	}-> std::same_as<void>;
    };

	template<api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
	class iRenderHelper;

	class iRender: public iBase{
		public:
			                iRender(){}
			virtual         ~iRender(){std::cout << "iRender destructor" << std::endl;}

			virtual void    init()				= 0;
			virtual void    reg(std::shared_ptr<iFigure>)		= 0;
			virtual void    draw()				= 0;
			virtual void    upd()				= 0;
			virtual void	wh(int, int)		= 0;

			virtual void    camera(std::shared_ptr<iCamera>)	= 0;

			template<api::WINDOW_DISPLAY_SYSTEM wds, typename... tArgs>
			void helper(std::shared_ptr< iRenderHelper<wds, tArgs...> > pHelperIn){
				pHelperIn->render(this);
				this->helper_ = pHelperIn;
			}

			template<api::WINDOW_DISPLAY_SYSTEM wds, typename... tArgs>
			void windowDisplaySystemData(tArgs... argv){
				std::any_cast< std::shared_ptr< iRenderHelper< wds, tArgs...> > >(this->helper_)->windowDisplaySystemData(argv...);
			}

		protected:
			std::any helper_;
	};

	// purpose is transfer display system data to iRender implementation
	template<api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
	class iRenderHelper: public iBase{
		public:
			                iRenderHelper(){};
			virtual         ~iRenderHelper(){std::cout << "iRenderHelper destructor" << std::endl;};

			virtual void windowDisplaySystemData(Args... argv) = 0;

		protected:
			virtual void render(iRender*) = 0;

		friend class iRender;
	};
}

