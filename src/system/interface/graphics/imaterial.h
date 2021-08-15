#pragma once

#include "api.h"
#include API_INTERFACE_IBASE


namespace api {
	class iMaterial: public iBase{
		public:
			iMaterial();
			virtual ~iMaterial(){std::cout << "iMaterial destructor" << std::endl;}
	};
}
