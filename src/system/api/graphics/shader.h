#pragma once

#include "interface/graphics/ishader.h"
#include "subsystem/graphics/ishader.impl.h"

namespace api {
	using Shader = cShader_t<subsystem::graphics::Shader>;
}
