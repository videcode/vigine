#pragma once

#include "queue.h"
#include <vector>

namespace graphics {
namespace vulkan {
class Family {
public:
  Family();

private:
  unsigned int index{0};
  std::vector<Queue *> queueArr;
};
} // namespace vulkan
} // namespace graphics
