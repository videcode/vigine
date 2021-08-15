#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IFIGURE


namespace api {
	class iObject: public iBase{
		public:
			iObject();
			virtual ~iObject(){std::cout << "iObject destructor" << std::endl;}

			virtual void						Figure(std::shared_ptr<iFigure> pFigureIn){this->pFigure = pFigureIn;}
			virtual std::shared_ptr<iFigure>	Figure(){return this->pFigure;}
		protected:
			std::shared_ptr<iFigure>	pFigure{nullptr};
			glm::vec3					position;
			glm::mat4					matrix;
	};
}
