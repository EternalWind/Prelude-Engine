#ifndef PL_EVENT_EVENT
#define PL_EVENT_EVENT

#include "Core/Config.h"
#include "Event/EventData.h"
#include "Event/EventType.h"
#include "IO/ISerializable.h"

#include <ctime>
#include <map>
#include <memory>

using namespace std;

namespace Prelude
{
namespace Event
{
/**
  * A base calss for all the events.
  */
class PRELUDE_ENGINE Event : implements IO::ISerializable
{
public:
	/**
	  * The constructor.
	  * @param time_stamp The time stamp when the event occurs.
	  */
	Event(const clock_t time_stamp, const EventType type, const EventDataSP data = nullptr);

	/**
	  * @see ISerializable
	  */
	virtual void serialize(OUT IO::IStream& stream) const;

	/**
	  * @see ISerializable
	  */
	virtual void deserialize(IN IO::IStream& stream);

	/**
	  * @see ISerializable
	  */
	virtual string toString() const;

	clock_t getTimeStamp() const;

    EventType getEventType() const;

    void setEventData(const EventDataSP data);

    EventDataSP getEventData() const;

	virtual ~Event();

protected:
	clock_t mTimeStamp;
    EventType mType;
    EventDataSP mData;
};

typedef shared_ptr<Event> EventSP;

} // End of namespace Event

} // End of namespace Prelude

#endif