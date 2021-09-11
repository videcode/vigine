#pragma once

#include "api.h"
#include API_INTERFACE_IBASE
#include API_INTERFACE_ISHADER
#include API_INTERFACE_IMESH
#include API_INTERFACE_IMATERIAL
#include API_INTERFACE_IVERTEX

#include <vector>

namespace api{
	template<typename TClass, typename TShader >
	concept cFigure = requires (TClass obj, TShader* pShader){
	    requires cBase<TClass>;
	    requires cShader<TShader>;

	    {obj.shader(pShader)	}->std::same_as<void>;
	    {obj.shader()			}->std::same_as<TShader*>;
    };

	template<typename TClass, typename TShader> requires cFigure<TClass, TShader>
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

