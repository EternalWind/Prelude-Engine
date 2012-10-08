#ifndef PL_EVENT_INTERFACE_EVENT_MANAGER
#define PL_EVENT_INTERFACE_EVENT_MANAGER

#include "Core/Config.h"
#include "Event/EventType.h"
#include "Event/IEvent.h"
#include "Event/IEventListener.h"

#include <memory>

using namespace std;

namespace pl
{
namespace Event
{
/**
  * An interface for event managers.
  */
interface PRELUDE_ENGINE IEventManager
{
public:
	/**
	  * Validate a given event type.
	  * @param The given event type to validate.
	  * @returns Whether the given event type is valid or not. An event is valid if it's not registered or registered but having the same type name as the first registered event of the same id. Both situations require the type name is not empty or null.
	  */
	virtual bool validateEventType(const EventType& type) const = 0;

	/**
	  * Pushes an event into the event queue.
	  * @param event The enqueuing event.
	  */
	virtual void queueEvent(const EventSP event) = 0;

	/**
	  * Eliminates the oldest event or all the events of a given event type in the event queue.
	  * @param type The given event type.
	  * @param all Whether only eliminates one event or all of them.
	  * @returns Whether at least one event is eliminated.
	  */
	virtual bool eliminateEvent(const EventType& type, bool all = false) = 0;

	/**
	  * Dispatches events to appropriate event listeners.
	  * @param time_limit The maximal time for dispatching events(No matter how short the given time is, at least one event will be totally dispatched). 0 means infinite.
	  * @returns Whether all the events in the queue has been dispatched or not.
	  */
	virtual bool dispatch(const clock_t time_limit = 0) = 0;

	/**
	  * Triggers an event immediately without queuing it.
	  * @param event The event to trigger.
	  * @returns Whether the event has been consumed by one of the listeners. Note that not being consumed doesn't mean not being processed.
	  */
	virtual bool triggerEvent(const EventSP event) = 0;

	/**
	  * Registers a listener to the event manager.
	  * @param listener The listener to register.
	  * @returns Whether the listener has been registered successfully or not.
	  */
	virtual bool registerListener(const EventListenerSP listener) = 0;

	/**
	  * Unregisters a listener from the event manager.
	  * @param listener The listener to unregister.
	  * @returns Whether the listener has been unregistered successfully or not.
	  */
	virtual bool unregisterListener(const EventListenerSP listener) = 0;

	virtual ~IEventManager() = 0 {}
};

typedef shared_ptr<IEventManager> EventManagerSP;

} // End of namespace Event

} // End of namespace pl

#endif