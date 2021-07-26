#include "pipelinegraphic.h"

using namespace graphics::vulkan;

PipelineGraphic::PipelineGraphic(){

}

void PipelineGraphic::init(std::shared_ptr<vk::Device> psLogicDevice){
	this->pwLogicDevice = psLogicDevice;
	this->renderpass.init();
}
