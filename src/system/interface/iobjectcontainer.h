#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IOBJECT


namespace api {
	class iObjectContainer: public iBase{
		public:
			enum class  RELATION{
				child
			};

			iObjectContainer();
			virtual ~iObjectContainer(){std::cout << "iObjectContainer destructor" << std::endl;}

			virtual void relation(std::shared_ptr<iObject> pObjectTarget, std::shared_ptr<iObject> pObject, RELATION rel)	= 0;
	};
}
