#pragma once

#include "api/core/base.h"

#include "interface/ievent.h"
#include "subsystem/core/ievent.impl.h"

namespace api{
	template<typename TCallback>
	using Event = cEvent_t<subsystem::core::Event, TCallback>;
}
