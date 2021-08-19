#pragma once

#include "api.h"
#include API_INTERFACE_IBASE


namespace api {
	class iVertex: public iBase{
		public:
			iVertex();
			virtual ~iVertex(){}

			glm::vec3 position;
			glm::vec3 normal;
			glm::vec3 color;
			glm::vec3 texCoord;
	};
}
