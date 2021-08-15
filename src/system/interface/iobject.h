#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_IFIGURE
#include API_INTERFACE_ITRANSFORMATION


namespace api {
	class iObject: public iBase{
		public:
			iObject();
			virtual ~iObject(){std::cout << "iObject destructor" << std::endl;}

			virtual uint								id(){return this->id_;}
			virtual void								Figure(std::shared_ptr<iFigure> pFigure){this->pFigure_ = pFigure;}
			virtual std::shared_ptr<iFigure>			Figure(){return this->pFigure_;}
			virtual std::shared_ptr<iTransformation>	transformation(){return this->pTransformation_;}

			virtual void		child(std::shared_ptr<iObject> child)	= 0;
		protected:
			uint								id_{0};
			std::shared_ptr<iFigure>			pFigure_{nullptr};
			std::shared_ptr<iTransformation>	pTransformation_{nullptr};
	};
}
