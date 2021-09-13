#pragma once

#include "api/core/event.h"
#include "interface/os/iwindow.h"
#include "subsystem/os/iwindow.impl.h"


namespace api{

	using Window = window_t<subsystem::os::Window>;

}
