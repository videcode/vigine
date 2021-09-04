#include "buffer.h"

using namespace graphics::vulkan;

Buffer::Buffer() {
  this->info.sType = vk::StructureType::eBufferCreateInfo;
  this->info.pNext = nullptr;
  this->info.flags = {}; //
  this->info.size = 0;
  this->info.usage = vk::BufferUsageFlagBits::eVertexBuffer;
  this->info.sharingMode = vk::SharingMode::eExclusive;
  this->info.queueFamilyIndexCount = 0;
  this->info.pQueueFamilyIndices = nullptr;
}

void Buffer::init(std::shared_ptr<vk::Device> logicDevice) {
  this->pwLogicDevice = logicDevice;

  if (this->pwLogicDevice.expired()) {
    auto psLogicDevice = this->pwLogicDevice.lock();
    this->buffer = psLogicDevice->createBuffer(this->info);
  }
}
