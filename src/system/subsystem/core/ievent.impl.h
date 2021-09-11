#pragma once

#include "api.h"
#include API_INTERFACE_IEVENT

#include <iostream>
#include <stdio.h>
#include <string>
#include <type_traits>
#include <functional>

#include "boost/signals2/signal.hpp"

using namespace std;


namespace subsystem{
	namespace core{
		template<typename TFunc>
		class Event{
				using EventSignal = boost::signals2::signal<TFunc>;
				using SlotType = typename EventSignal::slot_type;
			public:
				void destroy(){}
				template<typename TObj>
				void callback(TObj obj){
					this->signal_.connect(obj);
				}
				void callbackRemove(TFunc obj){}

				template<typename... TArgs>
				void call(TArgs... argv){
					this->signal_(argv...);
				}

			private:
				EventSignal signal_;
		};
	}
}

/*

namespace subsystem {
namespace core {

template <typename tSlot, typename... tArgs>
requires api::cEvent<tSlot, tArgs...> class Event : public api::iEvent {
public:
  using EventSignal = boost::signals2::signal<tSlot>;
  using SlotType = typename EventSignal::slot_type;

  Event(){};
  virtual ~Event(){};

  void slot(const tSlot *slot) { signal_.connect(slot); }
  void slotRemove(const tSlot *slot) {}

  void on(tArgs... argv) { signal_(argv...); }

  void Delete(){};

protected:
private:
  EventSignal signal_;
};

template <typename tSlot, typename... tArgs>
requires api::cEvent<tSlot, tArgs...> class EventHelper
    : public api::iEventHelper<tSlot, tArgs...> {
public:
  using EventImpl = Event<tSlot, tArgs...>;

  EventHelper(){};
  virtual ~EventHelper(){};

  void slot(tSlot *slotIn) override { this->pEvent_->slot(slotIn); }

  void slotRemove(tSlot *slotIn) override { this->pEvent_->slotRemove(slotIn); }

  void on(tArgs... argv) override { this->pEvent_->on(argv...); }

  void Delete() override{};

protected:
  void event(api::iEvent *pEventIn) override {
    this->pEvent_ = static_cast<EventImpl *>(pEventIn);
  }

  EventImpl *pEvent_{nullptr};
};
} // namespace core
} // namespace subsystem

void func();

namespace api {

template <typename tSlot, typename... tArgs>
requires cEvent<tSlot, tArgs...> class Impl<iEvent, tSlot, tArgs...> {
public:
  using iHelper = iEventHelper<tSlot, tArgs...>;

  static std::unique_ptr<iEvent> make() {
    std::unique_ptr<iEvent> pEvent(
        static_cast<iEvent *>(new subsystem::core::Event<tSlot, tArgs...>()));
    std::shared_ptr<iHelper> pHelper(static_cast<iHelper *>(
        new subsystem::core::EventHelper<tSlot, tArgs...>()));
    pEvent->helper(pHelper);

    return pEvent;
  }

private:
  Impl<iEvent, tSlot, tArgs...>() = delete;
  ~Impl<iEvent, tSlot, tArgs...>() = delete;
};

} // namespace api
*/
