#ifndef PL_EVENT_INTERFACE_EVENT
#define PL_EVENT_INTERFACE_EVENT

#include "Event/EventType.h"
#include "IO/ISerializable.h"

#include <ctime>
#include <memory>

using namespace std;

namespace Prelude
{
namespace Event
{
interface IEventManager;

/**
  * An interface for all the events. Events should not implement this interface directly. Instead, should inherit from BaseEvent.
  * @see BaseEvent
  */
interface PRELUDE_ENGINE IEvent : implements IO::ISerializable
{
public:
	/**
	  * Gets the time stamp when the event occurs.
	  * @returns The time stamp when the event occurs.
	  */
	virtual clock_t getTimeStamp() const = 0;

	/**
	  * Gets the type of the event.
	  * @returns The type of the event.
	  */
	virtual EventType getType() const = 0;

	virtual ~IEvent() = 0 {}
};

typedef shared_ptr<IEvent> EventSP;

} // End of namespace Event

} // End of namespace Prelude

#endif