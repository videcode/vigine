#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IOBJECT
#include API_INTERFACE_IRENDER


namespace api {
	class iWorld: public iBase{
		public:
			iWorld();
			virtual ~iWorld(){std::cout << "iWorld destructor" << std::endl;}

			virtual void						camera(std::shared_ptr<iCamera> pCameraIn){this->pCamera = pCameraIn;}
			virtual std::shared_ptr<iCamera>	camera(){return this->pCamera;}
			virtual void						render(std::shared_ptr<iRender> pRenderIn){this->pRender = pRenderIn;}
			virtual std::shared_ptr<iRender>	render(){return this->pRender;}
			virtual void						object(std::shared_ptr<iObject> pObjectIn)	= 0;
			virtual std::shared_ptr<iObject>	object(uint id)								= 0;
		protected:
			std::shared_ptr<iCamera> pCamera{nullptr};
			std::shared_ptr<iRender> pRender{nullptr};
	};
}
