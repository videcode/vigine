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

	this->createInfo.layout = VK_NULL_HANDLE;
	//this->createInfo.renderPass = ;
	this->createInfo.subpass = 0;
	this->createInfo.basePipelineHandle = VK_NULL_HANDLE;
	this->createInfo.basePipelineIndex = 0;
}

void PipelineGraphic::createInfoStageShader(){
	this->createInfo.stageCount = 1;
	this->stageShaderInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
	this->stageShaderInfo.pNext = nullptr;
	this->stageShaderInfo.flags = {};
	this->stageShaderInfo.stage = vk::ShaderStageFlagBits::eVertex;
	//this->stageShaderInfo.module = ;
	this->stageShaderInfo.pName = "main";
	this->stageShaderInfo.pSpecializationInfo = nullptr;

	this->createInfo.pStages = &this->stageShaderInfo;
}

void PipelineGraphic::createInfoStateVertexInput(){
	/*
	Буфер повинен бути створенний з бітом VK_BUFFER_USAGE_VERTEX_BUFFER_BIT
	*/
	this->stateVertexInput.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
	this->stateVertexInput.pNext = nullptr;
	this->stateVertexInput.flags = {};
	this->stateVertexInput.vertexBindingDescriptionCount	= 0;
	this->stateVertexInput.pVertexBindingDescriptions		= nullptr;
	this->stateVertexInput.vertexAttributeDescriptionCount	= 0;
	this->stateVertexInput.pVertexAttributeDescriptions		= nullptr;

	this->createInfo.pVertexInputState = &this->stateVertexInput;
}

void PipelineGraphic::createInfoStateInputAssembly(){
	this->stateInputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
	this->stateInputAssembly.pNext = nullptr;
	this->stateInputAssembly.flags = {};
	this->stateInputAssembly.topology				= vk::PrimitiveTopology::ePointList;
	this->stateInputAssembly.primitiveRestartEnable	= VK_FALSE;

	this->createInfo.pInputAssemblyState = &this->stateInputAssembly;
}

void PipelineGraphic::createInfoStateTessellation(){
	this->createInfo.pTessellationState = nullptr;
}

void PipelineGraphic::createInfoStateViewport(){
	this->dummyViewport.x		= 0.0f;
	this->dummyViewport.y		= 0.0f;
	this->dummyViewport.width		= 1.0f;
	this->dummyViewport.height	= 1.0f;
	this->dummyViewport.minDepth	= 0.1f;
	this->dummyViewport.maxDepth	= 1000.0f;

	this->dummyScissor.offset.x	= 0;
	this->dummyScissor.offset.y	= 0;
	this->dummyScissor.extent.width	= 1;
	this->dummyScissor.extent.height	= 1;

	this->stateViewport.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
	this->stateViewport.pNext = nullptr;
	this->stateViewport.flags = {};
	this->stateViewport.viewportCount	= 1;
	this->stateViewport.pViewports		= &this->dummyViewport;
	this->stateViewport.scissorCount	= 1;
	this->stateViewport.pScissors		= &this->dummyScissor;

	this->createInfo.pViewportState = &this->stateViewport;
}

void PipelineGraphic::createInfoStateRasterization(){
	this->stateRasterization.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
	this->stateRasterization.pNext = nullptr;
	this->stateRasterization.flags = {};
	this->stateRasterization.depthClampEnable			= VK_FALSE;
	this->stateRasterization.rasterizerDiscardEnable	= VK_TRUE;
	this->stateRasterization.polygonMode	= vk::PolygonMode::eFill;
	this->stateRasterization.cullMode		= vk::CullModeFlagBits::eNone;
	this->stateRasterization.frontFace		= vk::FrontFace::eCounterClockwise;
	this->stateRasterization.depthBiasEnable			= VK_FALSE;
	this->stateRasterization.depthBiasConstantFactor	= 0.0f;
	this->stateRasterization.depthBiasClamp				= 0.0f;
	this->stateRasterization.depthBiasSlopeFactor		= 0.0f;
	this->stateRasterization.lineWidth					= 0.0f;

	this->createInfo.pRasterizationState = &this->stateRasterization;
}

void PipelineGraphic::createInfoStateMultisample(){
	this->createInfo.pMultisampleState = nullptr;
}

void PipelineGraphic::createInfoStateDepthStencil(){
	this->createInfo.pDepthStencilState = nullptr;
}

void PipelineGraphic::createInfoStateColorBlend(){
	this->createInfo.pColorBlendState = nullptr;
}

void PipelineGraphic::createInfoStateDynamic(){
	this->createInfo.pDynamicState = nullptr;
}






