#include "ifigure.impl.h"

render::Figure::Figure() { this->matrix_ = glm::mat4(1.0f); }

render::Figure::~Figure() {
  // dtor
}
