#include "iwindow.impl.h"

using namespace subsystem::os::glfw;

Window::shrdEvt Window::pEventInit;
Window::shrdEvt Window::pEventClose;
Window::shrdEvt Window::pEventResize;
Window::shrdEvt Window::pEventMouseClickLeft;
Window::shrdEvt Window::pEventMouseClickRight;
Window::shrdEvt Window::pEventMouseClickWheel;
Window::shrdEvt Window::pEventMouseWheelUp;
Window::shrdEvt Window::pEventMouseWheelDown;
Window::shrdEvt Window::pEventKeyPress;

void error_callback(int error, const char* description){
	std::string errmess = description;
	std::cout << "ERROR: glfw error ( code " << error << " ) " << errmess << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	std::cout << "key: " << scancode << std::endl;
}

void key_char_callback(GLFWwindow* window, unsigned int codepoint){

	char32_t ch = codepoint;
	const wchar_t wideChar = codepoint;

	std::wcout << "key_char: " << wideChar << "(" << codepoint <<")" << std::endl;
}

void mouse_callback(GLFWwindow* window, int button, int action, int mods){

	if(action == GLFW_PRESS){
		if(button == 0 ){
			auto pEventHelperClickLeft	= Window::event<api::WINDOW_EVENT::mouseClickLeft>()->helper<api::iWindow::mouseClickLeft_func_t, int, int>();
			pEventHelperClickLeft->on(111,111);
		}else if(button == 1){
			auto pEventHelperClickRight	= Window::event<api::WINDOW_EVENT::mouseClickRight>()->helper<api::iWindow::mouseClickRight_func_t, int, int>();
			pEventHelperClickRight->on(222,222);
		}else if(button == 2){
			auto pEventHelperClickWheel	= Window::event<api::WINDOW_EVENT::mouseClickWheel>()->helper<api::iWindow::mouseClickWheel_func_t, int, int>();
			pEventHelperClickWheel->on(333,333);
		}

		std::cout << "mouse GLFW_PRESS: " << button << std::endl;
	}
}

Window::Window(){

}

void Window::init(){
	if (!glfwInit())
		std::runtime_error("window glfw failed");

	glfwSetErrorCallback(error_callback);

	this->pWindowGLFW = glfwCreateWindow(this->width_, this->height_, "My Title", NULL, NULL);

	if (!this->pWindowGLFW)
		std::runtime_error("window glfw opengl context failed");

	glfwMakeContextCurrent(this->pWindowGLFW);

	std::function<void(GLFWwindow* window, int button, int action, int mods)> fn = [](GLFWwindow* window, int button, int action, int mods){
		std::cout << "mouse lamda: " << button << std::endl;
	};

	glfwSetKeyCallback(this->pWindowGLFW, key_callback);
	glfwSetCharCallback(this->pWindowGLFW, key_char_callback);
	glfwSetMouseButtonCallback( this->pWindowGLFW, mouse_callback );
}

void Window::run(){

	while (!glfwWindowShouldClose(this->pWindowGLFW)){

		//std::cout << "Keep running" << std::endl;

		//glfwPollEvents();
		glfwWaitEventsTimeout(0.9);
	}
	std::cout << "not run()" << std::endl;

	glfwDestroyWindow(this->pWindowGLFW);
	glfwTerminate();
}

