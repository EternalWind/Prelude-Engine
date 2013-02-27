#include "Event/Event.h"

#include <strstream>

using namespace std;

namespace Prelude
{
namespace Event
{
Event::Event(const clock_t time_stamp, const EventType type, const EventDataSP data)
	: mTimeStamp(time_stamp),
      mType(type),
      mData(data) {}

void Event::serialize(OUT IO::IStream& stream) const
{
	stream << (byte8)mTimeStamp;

    mType.serialize(stream);

    if (mData.get() != nullptr)
    {
        mData->serialize(stream);
    }
}

void Event::deserialize(IN IO::IStream& stream)
{
	stream >> (byte8&)mTimeStamp;

    mType.deserialize(stream);

    if (mData.get() != nullptr)
    {
        mData->deserialize(stream);
    }
}

string Event::toString() const
{
	strstream ss;
	string str;
		
    ss << "[" << mTimeStamp << "] " << mType.toString() << " : " << mData.get() != nullptr ? mData->toString() : "";
	ss >> str;
		
	return str;
}

clock_t Event::getTimeStamp() const
{
	return mTimeStamp;
}

EventType Event::getEventType() const
{
    return mType;
}

void Event::setEventData(const EventDataSP data)
{
    mData = data;
}

EventDataSP Event::getEventData() const
{
    return mData;
}

Event::~Event() {}

} // End of namespace Event

} // End of namespace Prelude