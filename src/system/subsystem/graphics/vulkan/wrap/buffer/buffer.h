#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>

namespace graphics {
namespace vulkan {

	class Buffer{
		public:
			Buffer();
			void init(std::shared_ptr<vk::Device> logicDevice);

		private:
			std::weak_ptr<vk::Device> pwLogicDevice;

			vk::BufferCreateInfo	info;
			vk::Buffer				buffer;
	};
} // namespace vulkan
} // namespace graphics



