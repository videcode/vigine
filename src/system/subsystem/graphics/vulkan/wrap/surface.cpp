#include "surface.h"

using namespace graphics::vulkan;

Surface::Surface(){

}

void Surface::init(vk::Instance& inst){

	this->createInfo.sType		= vk::StructureType::eXlibSurfaceCreateInfoKHR;
	this->createInfo.pNext		= nullptr;
	this->createInfo.flags		= {};
	this->createInfo.dpy		= this->dpy;
	this->createInfo.window		= this->win;

	vk::Result res = inst.createXlibSurfaceKHR(&this->createInfo, nullptr, &this->surface);

	if(res == vk::Result::eSuccess){
		std::cout << "presentationSurface create" << std::endl;
	}else
		std::runtime_error("presentationSurface not create");

}

void Surface::xlibData(Window win, Display* dpy){
	this->win = win;
	this->dpy = dpy;
}

void Surface::presentModeKHR(vk::PresentModeKHR presentMode){
	this->presentMode = presentMode;
}








