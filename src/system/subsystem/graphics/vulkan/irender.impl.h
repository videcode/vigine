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

#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <memory>

#include "system/subsystem/core/base.h"
#include "wrap/instance.h"

namespace graphics{
	namespace vulkan{


		void print_prop(vk::PhysicalDevice&, std::string str="");
		void print_prop(vk::PhysicalDeviceMemoryProperties&);
		void print_prop(vk::PhysicalDeviceFeatures&, std::string str="");
		void print_prop(vk::LayerProperties&);
		void print_prop(vk::ExtensionProperties&);
		void print_prop(vk::QueueFamilyProperties&, std::string str="");
		void print_prop(std::vector<vk::PresentModeKHR>&, std::string str="");
		void print_prop(vk::SurfaceCapabilitiesKHR&, std::string str="");
		void print_prop(vk::SurfaceFormatKHR&, std::string str="");

		template<typename T, typename T2>
		void print_bit(T var, T2 var2, std::string, bool print_if_eual = false);
		template<typename T, typename T2>
		void print_equal(T var, T2 var2, std::string);
		template<int n, typename T>
		void print_extent(T var, std::string);

		class VulkanStructInfo{
			public:
				vk::InstanceCreateInfo			instCreate;
				vk::ApplicationInfo				app;
				vk::DeviceCreateInfo			logicDevice;
				vk::XlibSurfaceCreateInfoKHR	surfaceCreate;
				vk::SwapchainCreateInfoKHR		swapchainCreate;
				vk::PresentInfoKHR				present;
				vk::CommandPoolCreateInfo		commandPool;
				vk::CommandBufferAllocateInfo	commandBufferAllocate;
				vk::CommandBufferBeginInfo		commandBufferBegin;

				std::vector<vk::DeviceQueueCreateInfo> deviceQueueArr;
		};

		class VulkanStructObject{
			public:
				vk::UniqueInstance		inst				{nullptr};
				vk::SurfaceKHR			presentationSurface	{nullptr};
				vk::UniqueDevice		logicDevice			{nullptr};
				vk::UniqueSwapchainKHR	swapchain			{nullptr};

				vk::Semaphore			semaphore			{nullptr};
				vk::Fence				fence				{nullptr};

				vk::Queue				queueGraphics		{nullptr};
				vk::UniqueCommandPool	commandPool			{nullptr};

				std::vector<vk::PhysicalDevice>			deviceArr;
				//  need change image layout VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				std::vector<vk::Image>					swapchainImageArr;
				std::vector<vk::UniqueCommandBuffer>	commandBufferArrUniq;

				uint32_t				swapchainImageIndex{0};

				~VulkanStructObject(){

				}
		};

		class VulkanStructSettings{
			public:
				vk::SurfaceCapabilitiesKHR	surfaceCapabilities {};
				vk::SurfaceFormatKHR		surfaceFormat{};
				vk::PresentModeKHR			presentationMode	{};

				std::array<float, 1>		queuePriority {1.0f};
				vk::Extent2D				imageSize { 640, 480 };
				uint32_t					minImageCount{0};

				vk::PhysicalDeviceFeatures	physicalDeviceFeature;

				vk::ImageUsageFlags				imageUsage {vk::ImageUsageFlagBits::eColorAttachment};
				vk::SurfaceTransformFlagBitsKHR surfaceTransform {vk::SurfaceTransformFlagBitsKHR::eIdentity};
		};


		class Render: public api::iRender{
            public:
                Render();
				~Render();

				void    init()	override;
				void    reg(std::shared_ptr<api::iFigure>)  override;
                void    draw()  override;
				void    upd()	override;

				// self functions presenting
				void wh(int w, int h) override{
					this->settings.imageSize.width	= w;
					this->settings.imageSize.height	= h;
				}
				void camera(std::shared_ptr<api::iCamera> pCamIn) override {this->pCam_ = pCamIn;}
				void Delete() override{};

				template<api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
				void windowDisplaySystemData(Args... argv){
					if (wds == api::WINDOW_DISPLAY_SYSTEM::x11)
					    this->xlibInit(argv...);
					else
					    std::runtime_error("ERROR: in Render windowDisplaySystemData(Args... argv) 'WINDOW_DISPLAY_SYSTEM is not x11' ");


				}

            protected:

			private:
				Instance				inst;


				VulkanStructInfo		info;
				VulkanStructObject		obj;
				VulkanStructSettings	settings;

				std::shared_ptr<api::iCamera> pCam_;

				// other

				int width	{0};
				int heidht	{0};

				bool xlibInit(X11::Window, X11::Display*);

				bool step_presentationMode();
				bool step_capabilitiesPresentationSurface();
				bool step_imageUseges();
				bool step_createLogicDevice();
				bool step_createSwapchain();
				bool step_surfaceFormat();
				bool step_swapchainImages();
				bool step_swapchainCurrentImageIndex();
				bool step_present();

				bool step_commandPool();
				void step_commandPoolReset();
				bool step_commandBuffer();
				bool step_commandBufferBegin();
				void step_commandBufferEnd();
        };
// https://gamedev.ru/code/articles/VulkanTriangle
		template<api::WINDOW_DISPLAY_SYSTEM wds, typename... Args>
		class RenderHelper: public api::iRenderHelper<wds, Args...>{
			public:
				        RenderHelper<wds, Args...>(){};
				virtual ~RenderHelper<wds, Args...>(){std::cout << "RenderHelper destructor" << std::endl;};

				void windowDisplaySystemData(Args... argv) override{
					this->pRend->template windowDisplaySystemData<wds>(argv...);
				}

				void Delete() override{}

			protected:
				virtual void render(api::iRender* pRendIn) override{
					this->pRend = static_cast<Render*> (pRendIn);
				}

				Render* pRend{nullptr};
		};
    }
}


namespace api{

	template<>
	class Impl< api::iRender >{
		public:
			static std::unique_ptr<api::iRender> make(){
				namespace	ns		= graphics::vulkan;
				using		iHelper		= iRenderHelper<WINDOW_DISPLAY_SYSTEM::x11, X11::Window, X11::Display*>;
				using		HelperImpl	= ns::RenderHelper<WINDOW_DISPLAY_SYSTEM::x11, X11::Window, X11::Display*>;

				std::unique_ptr<api::iRender>	piRend( static_cast<api::iRender*>(new ns::Render()) );
				std::shared_ptr< iHelper >		piRendHelper( static_cast<iHelper*>(new HelperImpl()) );
				piRend->helper(piRendHelper);

				return piRend;
			}

		private:
			Impl< api::iRender >();
			~Impl< api::iRender >();
	};
}

