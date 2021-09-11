#pragma once
#include <concepts>
#include <api/core/base.h>

namespace api {

	template<typename TUniversalData>
	concept cUniversalData = requires (TUniversalData obj, int data){
	    requires cBase<TUniversalData>;
	    {obj.set(0, data)	}->std::same_as<void>;
	    {obj.template get<int>(0)	}->std::same_as<int>;
	    {obj.template get<std::string>(0)	}->std::same_as<std::string>;
    };

	template<typename TUniversalData> requires cUniversalData<TUniversalData>
	using cUniversalData_t = TUniversalData;
}

