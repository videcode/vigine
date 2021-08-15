#pragma once

#include "api.h"
#include API_INTERFACE_IBASE


namespace api {
	class iMesh: public iBase{
		public:
			iMesh();
			virtual ~iMesh(){std::cout << "iRender destructor" << std::endl;}
	};
}
