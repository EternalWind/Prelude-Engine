#include "Event/EventData.h"

#include <strstream>

using namespace std;

namespace Prelude
{
namespace Event
{
void EventData::serialize(OUT IO::IStream& stream) const
{
    const byte* data_ptr = nullptr;

    stream << (const byte4&)mAttributes.size();

    for (auto iter = mAttributes.begin() ; iter != mAttributes.end() ; ++iter)
    {
        uint32_t length = iter->first.length();
        data_ptr = (const byte*)iter->first.c_str();

        stream << (const byte4&)length;

        for (uint32_t i = 0 ; i < length ; ++i)
        {
            stream << data_ptr[i];
        }

        data_ptr = (const byte*)iter->second.second.get();
        length = iter->second.first;

        for (uint32_t i = 0 ; i < length ; ++i)
        {
            stream << data_ptr[i];
        }
    }
}

void EventData::deserialize(IN IO::IStream& stream)
{
    uint32_t count = 0;
    stream >> (byte4&)count;

    for (uint32_t i = 0 ; i < count ; ++i)
    {
        uint32_t length = 0;
        shared_ptr<byte> attribute_value_buffer(nullptr);
        string attribute_name;

        stream >> (byte4&)length;

        for (uint32_t i = 0 ; i < length ; ++i)
        {
            byte character;

            stream >> character;
            attribute_name += character;
        }

        stream >> (byte4&)length;
        attribute_value_buffer.reset(new byte[length]);

        for (uint32_t i = 0 ; i < length ; ++i)
        {
            stream >> attribute_value_buffer.get()[i];
        }

        mAttributes[attribute_name] = pair<size_t, shared_ptr<void>>(length, attribute_value_buffer);
    }
}

string EventData::toString() const
{
    // TODO: Figure out a way to appropriately represent the event data in a string.
    return "";
}

} // End of namespace Event
} // End of namespace Prelude