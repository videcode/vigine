#pragma once

#include "api.h"
#include API_INTERFACE_IRENDER
#include API_INTERFACE_IEVENT
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IFIGURE

#define VULKAN_HPP_NO_NODISCARD_WARNINGS
#define VK_USE_PLATFORM_XLIB_KHR
#include "x11/x11.h"
using namespace X11;
#include <vulkan/vulkan.hpp>

#include "system/subsystem/core/base.h"
#include "wrap/instance.h"
#include "wrap/surface.h"
#include "wrap/device.h"
#include "wrap/buffer/buffer.h"
#include "wrap/concepts.h"

namespace gv = graphics::vulkan;

namespace graphics {
	namespace vulkan {
		class Vulkan{
			public:
				template<cInfo T>
				using cInfo_t = T;

				Vulkan();
				void init();
				void destroy(){this->instance.destroy();}
				void xlibData(X11::Window, X11::Display *);

				void createInstance();
				void createSurface();
				void createLogicalDevice();
				void createUniformVariableBuffers();
				void createVertexDataBuffers();
				void createTextureSampler();
				void createTextureImages();
				void createSwapchain();
				void createDepthAndStencilImages();
				void createRenderpass();
				void createFrameBuffers();
				void createDescriptorSetPool();
				void createCommandBufferPool();
				void createCommandBuffers();
				void createDescriptorSetLayouts();
				void createDescriptorSets();
				void createGraphicsPipelines();

				void setupDebugCallbacks();
				void selectPhysicalDevice();
				void readShaders();

				void update();
				void render();

			private:

				cInst_t<gv::Instance>	instance{};
				cDevice_t<gv::Device>	device{};
				cSurf_t<gv::Surface>	surface{};
				cBuff_t<gv::Buffer>		bufferUniform{};
		};
	}
}
