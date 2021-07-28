#pragma once
#include <memory>

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.hpp>

#include "renderpass.h"

namespace graphics{
	namespace vulkan{
		class PipelineGraphic{
			public:
				PipelineGraphic();

				void init(std::shared_ptr<vk::Device>);

			private:
				Renderpass			renderpass{};
				vk::PipelineCache	pipelineCahe{};
				vk::GraphicsPipelineCreateInfo createInfo{};

				std::weak_ptr<vk::Device> pwLogicDevice;

				vk::PipelineShaderStageCreateInfo			stageShaderInfo{};
				vk::PipelineVertexInputStateCreateInfo		stateVertexInput{};
				vk::PipelineInputAssemblyStateCreateInfo	stateInputAssembly{};
				vk::PipelineTessellationStateCreateInfo		stateTessellation{};
				vk::PipelineViewportStateCreateInfo			stateViewport{};
				vk::PipelineRasterizationStateCreateInfo	stateRasterization{};
				vk::PipelineMultisampleStateCreateInfo		stateMultisample{};
				vk::PipelineDepthStencilStateCreateInfo		stateDepthStencil{};
				vk::PipelineColorBlendStateCreateInfo		stateColorBlend{};
				vk::PipelineDynamicStateCreateInfo			stateDynamic{};

				vk::Viewport	dummyViewport;
				vk::Rect2D		dummyScissor;

				void createInfoInit();
				void createInfoStageShader();
				void createInfoStateVertexInput();
				void createInfoStateInputAssembly();
				void createInfoStateTessellation();
				void createInfoStateViewport();
				void createInfoStateRasterization();
				void createInfoStateMultisample();
				void createInfoStateDepthStencil();
				void createInfoStateColorBlend();
				void createInfoStateDynamic();
		};
	}
}
