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
	Event(const clock_t time_stamp, const EventType type, const shared_ptr<EventData> data = nullptr);

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

    EventType getEventType() const;

    void setEventData(const shared_ptr<EventData> data);

    shared_ptr<EventData> getEventData() const;

	~Event();

protected:
	clock_t mTimeStamp;
    EventType mType;
    shared_ptr<EventData> mData;
};

typedef shared_ptr<Event> EventSP;

} // End of namespace Event

} // End of namespace Prelude

#endif