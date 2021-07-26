#include "pipelinegraphic.h"

using namespace graphics::vulkan;

PipelineGraphic::PipelineGraphic(){

}

void PipelineGraphic::init(std::shared_ptr<vk::Device> psLogicDevice){
	this->pwLogicDevice = psLogicDevice;

	this->createInfoInit();

	//psLogicDevice->createGraphicsPipeline(this->pipelineCahe, this->createInfo);

	this->renderpass.init();
}

void PipelineGraphic::createInfoInit(){
	this->createInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
	this->createInfo.pNext = nullptr;
	this->createInfo.flags = vk::PipelineCreateFlagBits::eDisableOptimization;
	this->createInfo.stageCount = 1;

	this->createInfoStageShader();
}

void PipelineGraphic::createInfoStageShader(){

}






