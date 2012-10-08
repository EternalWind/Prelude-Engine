#ifndef PL_EVENT_BASE_EVENT
#define PL_EVENT_BASE_EVENT

#include "Core/Config.h"
#include "Event/IEvent.h"

#include <ctime>

namespace Prelude
{
namespace Event
{
/**
  * A base calss for all the events.
  */
class PRELUDE_ENGINE BaseEvent : implements IEvent
{
public:
	/**
	  * The constructor.
	  * @param time_stamp The time stamp wwhen the event occurs.
	  */
	BaseEvent(const clock_t time_stamp = 0);

	/**
	  * @see ISerializable
	  */
	void serialize(OUT IO::IStream& stream) const;

	/**
	  * @see ISerializable
	  */
	void deserialize(IN IO::IStream& stream);

	/**
	  * @see ISerializable
	  */
	string toString() const;

	clock_t getTimeStamp() const;

	virtual void onSerialize(OUT IO::IStream& stream) const = 0;

	virtual void onDeserialize(IN IO::IStream& stream) = 0;

	virtual string onToString() const = 0;

	virtual ~BaseEvent() = 0;

protected:
	clock_t mTimeStamp;
};

} // End of namespace Event

} // End of namespace Prelude

#endif