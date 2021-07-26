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
