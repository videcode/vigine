#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_ISHADER
#include API_INTERFACE_IMESH

namespace api{

	class iFigure: public iBase{
		public:

			enum class  TYPE{
				VERTEX = 0,
				NORMAL,
				COLOR,
				VERTEX_INDEX
			};

			iFigure(){};
			virtual ~iFigure(){};

			virtual void		change()			= 0;
			virtual void		shader(iShader*)	= 0;
			virtual iShader*	shader()			= 0;

			virtual void		matrix(const glm::mat4&)	= 0;
			virtual glm::mat4	matrix()					= 0;
			virtual glm::mat4&	rmatrix()					= 0;

			// vertex, normal, color, vertexindex
			template<TYPE arr_t>
			size_t arrSize();

			template<TYPE arr_t>
			size_t arrSizeof();

			template<TYPE arr_t>
			auto* arrData();

		protected:
			std::shared_ptr<iMesh>		pMesh{nullptr};
			std::shared_ptr<iShader>	pShader{nullptr};
		private:
	};
}

