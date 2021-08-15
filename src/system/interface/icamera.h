#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_ITRANSFORMATION

using namespace glm;

namespace api {
	class iCamera: public iBase{

		public:
			iCamera()	= default;
			~iCamera()	= default;

			virtual vec3  pos()				= 0;
			virtual vec3& rpos()			= 0;
			virtual void  pos(vec3)			= 0;

			virtual vec3  target()			= 0;
			virtual vec3& rtarget()			= 0;
			virtual void  target(vec3)		= 0;

			virtual vec3  up()				= 0;
			virtual vec3& rup()				= 0;
			virtual void  up(vec3)			= 0;

			virtual vec3  directMove()		= 0;
			virtual vec3& rdirectMove()		= 0;
			virtual void  directMove(vec3)	= 0;

			virtual mat4  view()			= 0;
			virtual mat4& rview()			= 0;
			virtual void  view(mat4)		= 0;

			virtual mat4  proj()			= 0;
			virtual mat4& rproj()			= 0;
			virtual void  proj(mat4)		= 0;

			virtual float  angle()			= 0;
			virtual float& rangle()			= 0;
			virtual void   angle(float)		= 0;

			virtual void perspective	(float fovy, float aspect, float near, float far)	= 0;
			virtual void lookAt			(vec3 posIn, vec3 targetIn, vec3 upIn)				= 0;
			virtual void lookAt			()													= 0;
			virtual void windowResize	(int width, int height)								= 0;
			virtual void keyPress		(int keyCode)										= 0;
			virtual std::shared_ptr<iTransformation>	transformation(){return this->pTransformation_;}
		protected:
			std::shared_ptr<iTransformation> pTransformation_{nullptr};
	};
}


















