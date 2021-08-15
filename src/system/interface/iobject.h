#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IFIGURE


namespace api {
	class iObject: public iBase{
		public:
			iObject();
			virtual ~iObject(){std::cout << "iObject destructor" << std::endl;}

			virtual void						Figure(std::shared_ptr<iFigure> pFigure){this->pFigure_ = pFigure;}
			virtual std::shared_ptr<iFigure>	Figure(){return this->pFigure_;}

			virtual void		position(glm::vec3 position){this->position_ = position;}
			virtual glm::vec3	position(){return this->position_;}
		protected:
			std::shared_ptr<iFigure>	pFigure_{nullptr};
			glm::vec3					position_;
			glm::mat4					matrixRotation_;
			glm::mat4					matrixTransform_;
	};
}
