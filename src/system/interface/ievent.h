#pragma once

#include "api.h"
#include API_INTERFACE_IBASE

#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>
#include <any>

namespace api{
	// TSlot	- function type
	// Args		- TSlot arguments, need to virtual on(Args... argv) function

	template<typename tSlot>
	concept cSlot = std::is_function_v<tSlot>;

	template<typename tSlot, typename... Args>
	concept cEvent = cSlot<tSlot> &&  std::is_invocable_v<tSlot, Args...>;

	template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
	class iEventHelper;

	class iEvent: public iBase{
		public:


			//append slot to array
			template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
			void helper(iEventHelper<tSlot, tArgs...>* pHelperIn){
				pHelperIn->event(this);
				this->helper_ = pHelperIn;
			}

			template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
			iEventHelper<tSlot, tArgs...>* helper(){
				return std::any_cast< iEventHelper<tSlot, tArgs...>* >(this->helper_);
			}



			//append slot to array
			template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
			void slot(tSlot* slotIn){
				std::any_cast< iEventHelper<tSlot, tArgs...>* >(this->helper_)->slot(slotIn);
			}

			//remove slot from array
			template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
			void slotRemove	(tSlot* slotIn){
				std::any_cast< iEventHelper<tSlot, tArgs...>* >(this->helper_)->slotRemove(slotIn);
			}

			// call all slots
			template<typename tSlot, typename... tArgs> requires cEvent<tSlot, tArgs...>
			void on(tArgs... argv){
				std::any_cast< iEventHelper<tSlot, tArgs...>* >(this->helper_)->on(argv...);
			}


		protected:
			iEvent(){};
			virtual ~iEvent()	= default;

			std::any helper_;

	};

	template<typename tSlot, typename... tArgs>
	requires cEvent<tSlot, tArgs...>
	class iEventHelper: public iBase{
		public:

			virtual void slot(tSlot*)		= 0;
			virtual void slotRemove(tSlot*) = 0;
			virtual void on(tArgs...)		= 0;

		protected:
			virtual void event(iEvent*)		= 0;

		friend class iEvent;
	};
}














