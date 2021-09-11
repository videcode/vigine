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
#include <concepts>
#include <tuple>

namespace api {

	// cBase
	template<typename TClass>
	concept cBase = requires (TClass obj){
	    obj.destroy();
    };

	template<typename TClass> requires cBase<TClass>
	using cBase_t = TClass;

	// Signature
	template<typename TFunc>
	struct FunctionSignature;

	template<typename TReturn, typename... TArgs>
	struct FunctionSignature<TReturn(TArgs...)>{
		using return_t                      = TReturn;
		using params_t                      = std::tuple<TArgs...>;
		static const size_t params_count    = sizeof... (TArgs);
	};

	// tuple compare
	template<typename TTuple, typename TTuple2, size_t i = 0>
	 constexpr bool tuple_compare(){
		 if constexpr(std::tuple_size<TTuple>::value != std::tuple_size<TTuple2>::value)
		    return false;

		static_assert(i < std::tuple_size<TTuple>::value, "i >= std::tuple_size<TTuple>::value");

		//std::cout << "i: " << i << std::endl;
		if constexpr (!std::is_same_v< std::tuple_element_t<i, TTuple>, std::tuple_element_t<i, TTuple2> >)
		    return false;
		else if constexpr ((i+1) == std::tuple_size<TTuple>::value){
			return true;
		}else{
			//std::cout << "recursion " << std::endl;
			return tuple_compare<TTuple, TTuple2, i+1>();
		}
	}




/*

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

*/
}


