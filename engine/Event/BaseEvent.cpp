#include "Event/BaseEvent.h"

#include <strstream>

using namespace std;

namespace Prelude
{
namespace Event
{
BaseEvent::BaseEvent(const clock_t time_stamp)
	: mTimeStamp(time_stamp) {}

void BaseEvent::serialize(OUT IO::IStream& stream) const
{
	stream << (byte8)mTimeStamp;

	onSerialize(stream);
}

void BaseEvent::deserialize(IN IO::IStream& stream)
{
	stream >> (byte8&)mTimeStamp;

	onDeserialize(stream);
}

string BaseEvent::toString() const
{
	strstream ss;
	string str;
		
	ss << "[" << mTimeStamp << "] " << onToString();
	ss >> str;
		
	return str;
}

clock_t BaseEvent::getTimeStamp() const
{
	return mTimeStamp;
}

BaseEvent::~BaseEvent() {}

} // End of namespace Event

} // End of namespace Prelude