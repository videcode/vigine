#pragma once

#include "api.h"
#include API_INTERFACE_IBASE

#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>
#include <any>
#include <memory>

namespace api{
	// TSlot	- function type
	// Args		- TSlot arguments, need to virtual on(Args... argv) function

	template<typename  TCallback>
	concept cCallback = requires{
	    requires std::is_function_v<TCallback>;
    };

	template<typename TClass, typename... TArgs>
	concept cCallTuple = requires (TClass obj, TArgs... argv){
	    { obj.template call<TArgs...>(argv...)		} -> std::same_as<void>;
    };


	template<typename TClass, typename... TArgs> requires cCallTuple<TClass, TArgs...>
	struct Call{};

	template<typename TClass, typename TReturn, typename... TArgs> requires cCallTuple<TClass, TArgs...>
	struct Call<TClass, TReturn(TArgs...)>{};

	template<template<typename> class TClass, typename TCallback>
	concept cEvent = requires (
	                     TClass<TCallback> obj,
	                     TCallback callback,
	                     Call<TClass<TCallback>, TCallback> call
	){
	    requires cBase< TClass<TCallback> >;
	    requires cCallback<TCallback>;

	    { obj.callback(callback)		}-> std::same_as<void>;
	    { obj.callbackRemove(callback)	}-> std::same_as<void>;
    };

	template<
	        template<typename > class TClass,
	        typename TCallback
	> requires cEvent< TClass, TCallback>
	using cEvent_t = TClass<TCallback>;




/*
	template<template<typename> typename TClass, typename TCallback, typename... TArgs> requires cEvent<TClass, TCallback, TArgs...>
	class iEventHelper;

	class iEvent: public iBase{
		public:
			virtual ~iEvent()	= default;

			template<typename TSlot, typename... TArgs> requires cCallback<TSlot, TArgs...>
			using shrdEvHelp = std::shared_ptr< iEventHelper<TSlot, TArgs...> >;

			//append slot to array
			template<typename tSlot, typename... tArgs>
			void helper( shrdEvHelp<tSlot, tArgs...> pHelperIn){
				pHelperIn->event(this);
				this->helper_ = pHelperIn;
			}

			template<typename tSlot, typename... tArgs>
			 shrdEvHelp<tSlot, tArgs...> helper(){
				return std::any_cast<  shrdEvHelp<tSlot, tArgs...>  >(this->helper_);
			}



			//append slot to array
			template<typename tSlot, typename... tArgs>
			void slot(tSlot* slotIn){
				std::any_cast< shrdEvHelp<tSlot, tArgs...> >(this->helper_)->slot(slotIn);
			}

			//remove slot from array
			template<typename tSlot, typename... tArgs>
			void slotRemove	(tSlot* slotIn){
				std::any_cast< shrdEvHelp<tSlot, tArgs...> >(this->helper_)->slotRemove(slotIn);
			}

			// call all slots
			template<typename tSlot, typename... tArgs>
			void on(tArgs... argv){
				std::any_cast< shrdEvHelp<tSlot, tArgs...> >(this->helper_)->on(argv...);
			}


		protected:
			iEvent(){};

			std::any helper_;

	};

	template<template<typename> typename TClass, typename TCallback, typename... TArgs> requires cEvent<TClass, TCallback, TArgs...>
	class iEventHelper: public iBase{
		public:

			virtual void callback(TCallback*)		= 0;
			virtual void callbackRemove(TCallback*) = 0;
			virtual void call(TArgs...)		= 0;

		protected:
			virtual void event(iEvent*)		= 0;

		friend class iEvent;
	};

	*/
}














