#pragma once
#include <concepts>


/*
#include API_INTERFACE_IWINDOW_IMPL
#include API_INTERFACE_IEVENT_IMPL
#include API_INTERFACE_ICAMERA_IMPL
#include API_INTERFACE_IFIGURE_IMPL
#include API_INTERFACE_IRENDER_IMPL

namespace api {
	template<typename TClass>
	concept cFigure = std::is_class_v<TClass>;


	template<
			typename TClass,
			typename TFigure = render::Figure
	>
	concept cRender = requires{
		requires cFigure<TFigure>;
		requires requires (TClass obj, std::shared_ptr<TFigure> fig){
			obj.init();
			obj.reg(fig);
			{obj.shI() }-> std::same_as<std::shared_ptr<api::iCamera>>;
		};
	};


}

template<api::cRender TClass>
using cRender_t = TClass;

template<cFigure TClass>
using cFigure_t = TClass;

namespace api{
	using Render = cRender_t<graphics::vulkan::Render>;
	using Figure = cFigure_t<render::Figure>;
}


api::Render rend;
std::shared_ptr<api::Figure> fig;
void f(){
	::rend.reg(fig);
}

*/


