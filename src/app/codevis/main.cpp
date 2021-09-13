#include <memory>
#include <type_traits>
#include <vector>

#define API_INTERFACE_ALL_IMPL_INCLUDE
#include "api.concept.h"
#include "glm/glm.hpp"
#include "x11/x11.h"

#include "subsystem/ogre3d/ogre3dapp.h"

#include "api/core/event.h"
#include "api/core/universaldata.h"
#include "api/graphics/render.h"
#include "api/os/window.h"

using namespace std;
// using namespace graphics;
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

int main() {

  std::shared_ptr<api::WindowEventMouseLeftClick> spMouseLeftClick(
      new api::WindowEventMouseLeftClick());
  std::shared_ptr<api::WindowEventDisplaySystem> spDisplaySystem(
      new api::WindowEventDisplaySystem());
  std::shared_ptr<api::WindowEventInit> spWindowInit(
      new api::WindowEventInit());


  api::Window window;
  api::Render render;

  spMouseLeftClick->callback(onMouseClickLeft);
  spDisplaySystem->callback(
      [&render](std::shared_ptr<api::UniversalData> spUData) {
        render.displaySystem(spUData);
      });
  spWindowInit->callback([&render]() { render.init(); });

  window.event<api::WINDOW_EVENT::mouseClickLeft>(spMouseLeftClick);
  window.event<api::WINDOW_EVENT::displaySystem>(spDisplaySystem);
  window.event<api::WINDOW_EVENT::init>(spWindowInit);

  window.init();
  window.run();

  return 0;
}

/*
int main_old() {

  // custom figure
  /*
Rate            rate;
{ // make rate shader
  std::string path =
"/home/webliga/Documents/c/codeblocks/code/app/codevis/figure/rate/shader/";
                                                                  iShader*
pShaderRate = api::impl<iShader>();
  pShaderRate->path<iShader::TYPE::VERTEX>(path+"rate.vert");
  pShaderRate->path<iShader::TYPE::FRAGMENT>(path+"rate.frag");

  rate.shader(pShaderRate);
}


  // загрузка конфігурації
  pCamera->perspective(45.0f,
                                                                                   (float)piWindow->width() /
(float)piWindow->height(), 0.5f, 1000.0f); pCamera->lookAt(vec3(0.0f,
0.0f, 2.0f), // camera position vec3(0.0f, 0.0f, 0.0f), // camera target
                                                                  vec3(0.0f, 1.0f,
0.0f)  // camera up
  );

  // ініциалізація модулів
  pRend->camera(pCamera);
  piWindow->render(pRend);


                                                                  // register
figure in render syste
                                                                  //pRend->reg(&rate);

piWindow->init();
  piWindow->run();

  return 0;
}

*/
void onInit() { std::cout << "linux::Window onInit()" << std::endl; }

void onClose() {
  std::cout << "linux::Window onClose() need close all files and sockets"
            << std::endl;
}

void onResize(int w, int h) {
  cout << "onResize: w = " << w << " h = " << h << endl;
}

void onKeyPress(int keyCode) {
  cout << "onKeyPress: keyCode = " << keyCode << endl;
}

void onMouseClickLeft(int x, int y) {
  cout << "function onMouseClickLeft mouse click: x = " << x << " y = " << y
       << endl;
}

void onMouseClickRight(int x, int y) {
  cout << "onMouseClickRight mouse click: x = " << x << " y = " << y << endl;
}

void onMouseClickWheel(int x, int y) {
  cout << "onMouseClickWheel mouse click: x = " << x << " y = " << y << endl;
}

void onMouseWheelUp(int x, int y) {
  cout << "onMouseWheelUp: x = " << x << " y = " << y << endl;
}

void onMouseWheelDown(int x, int y) {
  cout << "onMouseWheelDown: x = " << x << " y = " << y << endl;
}
