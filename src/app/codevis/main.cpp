#include <vector>
#include <type_traits>
#include <memory>

#define API_INTERFACE_ALL_IMPL_INCLUDE
#include "api.impl.h"
#include "glm/glm.hpp"
#include "x11/x11.h"

using namespace std;
using namespace graphics;
using namespace std::placeholders;
using namespace glm;



void onInit();
void onClose();
void onResize(int, int);
void onKeyPress(int);

void onMouseClickLeft(int, int);
void onMouseClickRight(int, int);
void onMouseClickWheel(int, int);
void onMouseWheelUp(int, int);
void onMouseWheelDown(int, int);


int main(){

	using IMPL_iWINDOW		= api::Impl<api::iWindow>;
	using IMPL_iRENDER		= api::Impl<api::iRender>;

	shared_ptr< api::iWindow >	piWindow = IMPL_iWINDOW::make();
	shared_ptr< api::iRender >	pRend	= IMPL_iRENDER::make();
	shared_ptr< api::iCamera >	pCamera	= api::Impl<api::iCamera>::make();

// custom figure
	/*
    Rate            rate;
    { // make rate shader
        std::string path = "/home/webliga/Documents/c/codeblocks/code/app/codevis/figure/rate/shader/";
		iShader* pShaderRate = api::impl<iShader>();
        pShaderRate->path<iShader::TYPE::VERTEX>(path+"rate.vert");
        pShaderRate->path<iShader::TYPE::FRAGMENT>(path+"rate.frag");

        rate.shader(pShaderRate);
    }
*/

// загрузка конфігурації
	pCamera->perspective(45.0f, (float)piWindow->width()/(float)piWindow->height(), 0.5f, 1000.0f);
	pCamera->lookAt(
	    vec3(0.0f, 0.0f, 2.0f),  // camera position
        vec3(0.0f, 0.0f, 0.0f),  // camera target
        vec3(0.0f, 1.0f, 0.0f)   // camera up
    );

// ініциалізація модулів
	pRend->camera(pCamera);
	piWindow->render(pRend);

// створення подій
	std::cout << "some ************8" << std::endl;
	using IMPL_iEVENT_INIT			= api::Impl<api::iEvent, api::iWindow::init_func_t>;
	using IMPL_iEVENT_CLOSE			= api::Impl<api::iEvent, api::iWindow::close_func_t>;
	using IMPL_iEVENT_RESIZE		= api::Impl<api::iEvent, api::iWindow::resize_func_t, int, int>;
	using IMPL_iEVENT_KEYPRESS		= api::Impl<api::iEvent, api::iWindow::keyPress_func_t, int>;
	using IMPL_iEVENT_MOUSE_CL		= api::Impl<api::iEvent, api::iWindow::mouseClickLeft_func_t, int, int>;
	using IMPL_iEVENT_MOUSE_CR		= api::Impl<api::iEvent, api::iWindow::mouseClickRight_func_t, int, int>;
	using IMPL_iEVENT_MOUSE_WUP		= api::Impl<api::iEvent, api::iWindow::mouseWheelUp_func_t, int, int>;
	using IMPL_iEVENT_MOUSE_WDOWN	= api::Impl<api::iEvent, api::iWindow::mouseWheelDown_func_t, int, int>;
	using IMPL_iEVENT_MOUSE_CW		= api::Impl<api::iEvent, api::iWindow::mouseClickWheel_func_t, int, int>;

	using shrdEvt = std::shared_ptr<api::iEvent>;

	shrdEvt	piEvtWindowInit				= IMPL_iEVENT_INIT::make();
	shrdEvt	piEvtWindowClose			= IMPL_iEVENT_CLOSE::make();
	shrdEvt	piEvtWindowResize			= IMPL_iEVENT_RESIZE::make();
	shrdEvt	piEvtKeypress				= IMPL_iEVENT_KEYPRESS::make();
	shrdEvt	piEvtMouseClickLeft			= IMPL_iEVENT_MOUSE_CL::make();
	shrdEvt	piEvtMouseClickRight		= IMPL_iEVENT_MOUSE_CR::make();
	shrdEvt	piEvtMouseWheelUp			= IMPL_iEVENT_MOUSE_WUP::make();
	shrdEvt	piEvtMouseWheelDown			= IMPL_iEVENT_MOUSE_WDOWN::make();
	shrdEvt	piEvtMouseClickWheel		= IMPL_iEVENT_MOUSE_CW::make();

	piEvtWindowInit->slot<api::iWindow::init_func_t>(onInit);
	piEvtWindowClose->slot<api::iWindow::close_func_t>(onClose);
	piEvtWindowResize->slot<api::iWindow::resize_func_t, int, int>(onResize);
	piEvtKeypress->slot<api::iWindow::keyPress_func_t, int>(onKeyPress);
	piEvtMouseClickLeft->slot<api::iWindow::mouseClickLeft_func_t, int, int>(onMouseClickLeft);
	piEvtMouseClickRight->slot<api::iWindow::mouseClickRight_func_t, int, int>(onMouseClickRight);
	piEvtMouseWheelUp->slot<api::iWindow::mouseWheelUp_func_t, int, int>(onMouseWheelUp);
	piEvtMouseWheelDown->slot<api::iWindow::mouseWheelDown_func_t, int, int>(onMouseWheelDown);
	piEvtMouseClickWheel->slot<api::iWindow::mouseClickWheel_func_t, int, int>(onMouseClickWheel);

	piWindow->event(piEvtWindowInit, api::WINDOW_EVENT::init);
	piWindow->event(piEvtWindowClose, api::WINDOW_EVENT::close);
	piWindow->event(piEvtWindowResize, api::WINDOW_EVENT::resize);
	piWindow->event(piEvtKeypress, api::WINDOW_EVENT::keyPress);
	piWindow->event(piEvtMouseClickLeft, api::WINDOW_EVENT::mouseClickLeft);
	piWindow->event(piEvtMouseClickRight, api::WINDOW_EVENT::mouseClickRight);
	piWindow->event(piEvtMouseWheelUp, api::WINDOW_EVENT::mouseWheelUp);
	piWindow->event(piEvtMouseWheelDown, api::WINDOW_EVENT::mouseWheelDown);
	piWindow->event(piEvtMouseClickWheel, api::WINDOW_EVENT::mouseClickWheel);

/*
    // register figure in render system
	//pRend->reg(&rate);
*/
	piWindow->init();
	piWindow->run();

	return 0;
}

void onInit(){
    std::cout << "linux::Window onInit()" << std::endl;
}

void onClose(){
    std::cout << "linux::Window onClose() need close all files and sockets" << std::endl;
}

void onResize(int w, int h){
	cout << "onResize: w = " << w << " h = " << h << endl;
}

void onKeyPress(int keyCode){
	cout << "onKeyPress: keyCode = " << keyCode << endl;
}

void onMouseClickLeft(int x, int y){
	cout << "onMouseClickLeft mouse click: x = " << x << " y = " << y << endl;
}

void onMouseClickRight(int x, int y){
    cout << "onMouseClickRight mouse click: x = " << x << " y = " << y << endl;
}

void onMouseClickWheel(int x, int y){
    cout << "onMouseClickWheel mouse click: x = " << x << " y = " << y << endl;
}

void onMouseWheelUp(int x, int y){
    cout << "onMouseWheelUp: x = " << x << " y = " << y << endl;
}

void onMouseWheelDown(int x, int y){
    cout << "onMouseWheelDown: x = " << x << " y = " << y << endl;
}

















