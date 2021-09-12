#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_ISHADER
#include API_INTERFACE_IMESH
#include API_INTERFACE_IMATERIAL
#include API_INTERFACE_IVERTEX

#include <vector>
#include "api/graphics/shader.h"

namespace api{
	template<typename TClass>
	concept cFigure = requires (
	  TClass obj,
	  std::shared_ptr<api::Shader> spShader
	){
	    requires cBase<TClass>;

	    {obj.shader(spShader)	}->std::same_as<void>;
	    {obj.shader()			}->std::same_as<std::shared_ptr<api::Shader>>;
    };

	template<typename TClass> requires cFigure<TClass>
	using  cFigure_t = TClass;

	/*

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

			// vertex, normal, color, vertexindex
			template<TYPE arr_t>
			size_t arrSize();

			template<TYPE arr_t>
			size_t arrSizeof();

			template<TYPE arr_t>
			auto* arrData();

		protected:
			std::vector<std::shared_ptr<iVertex>>	pVertex_{nullptr};
			std::shared_ptr<iMesh>		pMesh_{nullptr};
			std::shared_ptr<iMaterial>	pMaterial_{nullptr};
			std::shared_ptr<iShader>	pShader_{nullptr};
		private:
	};

	*/
}

