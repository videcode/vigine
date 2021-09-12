#pragma once
#include <concepts>
#include <api/core/base.h>

namespace api {

	template<typename TUniversalData>
	concept cUniversalData = requires (TUniversalData obj, int data){
	    requires cBase<TUniversalData>;
	    {obj.set(data)	}->std::same_as<void>;
	    {obj.del(1)		}->std::same_as<void>;
	    {obj.size()		}->std::same_as<size_t>;
	    {obj.template get<int>(0)			}->std::same_as<int>;
	    {obj.template get<std::string>(0)	}->std::same_as<std::string>;
	    {obj.template insert<int>(data, 0)	}->std::same_as<void>;
    };

	template<typename TUniversalData> requires cUniversalData<TUniversalData>
	using cUniversalData_t = TUniversalData;
}

