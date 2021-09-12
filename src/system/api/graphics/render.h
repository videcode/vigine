#pragma once

#include "interface/graphics/irender.h"
#include "subsystem/graphics/vulkan/irender.impl.h"

namespace api{
	using Render = cRender_t<subsystem::graphics::vulkan::Render>;
}
