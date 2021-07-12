#include "icamera.impl.h"

subsystem::Camera::Camera(){
    this->view_ = glm::mat4(1.0f);
    this->proj_ = glm::mat4(1.0f);
    this->directMove_ = glm::vec3(0.0f, 0.0f, 0.1f);
}

subsystem::Camera::~Camera()
{
	std::cout << "Camera destructor" << std::endl;
}


