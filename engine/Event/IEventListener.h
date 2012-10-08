#ifndef PL_EVENT_INTERFACE_EVENT_LISTENER
#define E_MODULE_INTERFACE_EVENT_LISTENER

#include "Core/Config.h"
#include "Event/EventType.h"
#include "Event/IEvent.h"

#include <memory>

using namespace std;

namespace pl
{
namespace Event
{
interface PRELUDE_ENGINE IEventListener
{
public:
	virtual ~IEventListener() = 0 {}

	/**
	  * Gets the type of event this listener responds to.
	  * @returns The event type.
	  */
	virtual EventType getEventType() const = 0;

	/**
	  * Handles an incoming event.
	  * @param event The incoming event.
	  * @returns Whether the incoming event has been consumed by this listener(Prevent it from passing to the next listener) or not.
	  */
	virtual bool handleEvent(const EventSP event) = 0;

	/**
	  * Gets the name of this listener.
	  * @returns The name of this listener.
	  */
	virtual string getName() const = 0;
};

typedef shared_ptr<IEventListener> EventListenerSP;

} // End of namespace Event

} // End of namespace pl

#endif