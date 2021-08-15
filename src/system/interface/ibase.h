#pragma once


#define	GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
//#define GLM_EXTERNAL_TEMPLATE
    #include "glm/glm.hpp"
    #include "glm/ext.hpp"
//#undef GLM_EXTERNAL_TEMPLATE

#include <any>
#include <memory>
#include <iostream>

namespace api {

	class iBase{
		protected:
			virtual ~iBase() = default;


		public:
			virtual void	Delete()				= 0;
			        iBase&	operator=(const iBase&)	= delete;
	};

	class iImplementation{
		public:
			virtual void make() = 0;
	};


	template<typename T, typename... tArgs>
	class Impl{
		public:
			static T* make();

		//private:
			Impl();
			~Impl();
	};


}


