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

	this->createInfoStageShader();
	this->createInfoStateVertexInput();
	this->createInfoStateInputAssembly();
	this->createInfoStateTessellation();
	this->createInfoStateViewport();
	this->createInfoStateRasterization();
	this->createInfoStateMultisample();
	this->createInfoStateDepthStencil();
	this->createInfoStateColorBlend();
	this->createInfoStateDynamic();
/*
	this->createInfo.layout = ;
	this->createInfo.renderPass = ;
	this->createInfo.subpass = ;
	this->createInfo.basePipelineHandle = ;
	this->createInfo.basePipelineIndex = ;
*/
}

void PipelineGraphic::createInfoStageShader(){
	this->createInfo.stageCount = 1;

}

void PipelineGraphic::createInfoStateVertexInput(){

}

void PipelineGraphic::createInfoStateInputAssembly(){

}

void PipelineGraphic::createInfoStateTessellation(){

}

void PipelineGraphic::createInfoStateViewport(){

}

void PipelineGraphic::createInfoStateRasterization(){

}

void PipelineGraphic::createInfoStateMultisample(){

}

void PipelineGraphic::createInfoStateDepthStencil(){

}

void PipelineGraphic::createInfoStateColorBlend(){

}

void PipelineGraphic::createInfoStateDynamic(){

}






