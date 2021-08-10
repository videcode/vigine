#pragma once

#include "../ishader.h"

namespace render {
namespace Vulkan {
class Shader : public iShader {
public:
  Shader();
  virtual ~Shader();

  void compile() override;
  void use() override;

protected:
private:
};
} // namespace Vulkan
} // namespace render
