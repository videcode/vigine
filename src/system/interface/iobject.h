#pragma once

#include "api.h"
#include API_INTERFACE_IBASE


namespace api {
	class iObject: public iBase{
		public:
			iObject();
			virtual ~iObject(){std::cout << "iObject destructor" << std::endl;}

		protected:

	};
}
