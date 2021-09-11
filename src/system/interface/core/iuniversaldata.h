#pragma once
#include <concepts>
#include <api/core/base.h>

namespace api {

	template<typename TUniversalData>
	concept cUniversalData = requires (TUniversalData obj, int data){
	    requires cBase<TUniversalData>;
	    {obj.set(0, data)	}->std::same_as<void>;
	    {obj.get(0)			}->std::same_as<void*>;
	    {obj.allocate(10)	}->std::same_as<bool>;
	    {obj.free()			}->std::same_as<void>;
    };

	template<typename TUniversalData> requires cUniversalData<TUniversalData>
	using cUniversalData_t = TUniversalData;
}

