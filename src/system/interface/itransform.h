#pragma once

#include "api.h"
#include API_INTERFACE_IBASE


namespace api {
	class iTransform: public iBase{
		public:
			iTransform();
			virtual ~iTransform(){std::cout << "iTransform destructor" << std::endl;}
	};
}
