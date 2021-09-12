#pragma once

#include "interface/icamera.h"
#include "subsystem/camera/icamera.impl.h"

namespace api{
	using Camera = cCamera_t<subsystem::camera::Camera>;
}
