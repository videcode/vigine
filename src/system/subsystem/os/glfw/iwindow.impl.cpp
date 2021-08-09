#include "iwindow.impl.h"

using namespace subsystem::os::glfw;

void error_callback(int error, const char *description) {
  std::string errmess = description;
  std::cout << "ERROR: glfw error ( code " << error << " ) " << errmess
            << std::endl;
}

Window::Window() {}

void Window::init() {
  if (!glfwInit())
    std::runtime_error("window glfw failed");

  glfwSetErrorCallback(error_callback);
  this->pWindowGLFW =
      glfwCreateWindow(this->width_, this->height_, "My Title", NULL, NULL);

  if (!this->pWindowGLFW)
    std::runtime_error("window glfw opengl context failed");

  glfwMakeContextCurrent(this->pWindowGLFW);
}

void Window::run() {

  while (!glfwWindowShouldClose(this->pWindowGLFW)) {

    // std::cout << "Keep running" << std::endl;

    glfwPollEvents();
  }
  std::cout << "not run()" << std::endl;
  glfwDestroyWindow(this->pWindowGLFW);
  glfwTerminate();
}
