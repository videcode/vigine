#pragma once

#include "interface/ibase.h"
#include "subsystem/core/base.h"
#include <memory>

namespace api{
	template<typename T>
	using sp = std::shared_ptr<T>;
}
