#ifndef PL_EVENT_EVENT_DATA
#define PL_EVENT_EVENT_DATA

#include "Core/Config.h"
#include "IO/ISerializable.h"

#include <memory>
#include <string>
#include <map>

using namespace std;

namespace Prelude
{
namespace Event
{
    /**
       * A base class to hold the event data.
       */
    class EventData : implements IO::ISerializable
    {
    public:
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

    protected:
        /**
           * Sets a given attribute.
           * @param name The name of the attribute to set.
           * @param value The value of the attribute to set.
           */
        template <class T>
        void setAttribute(const string name, const T value)
        {
            shared_ptr<void> temp(new T(value));
            mAttributes[name] = pair<size_t, shared_ptr<void>>(sizeof(T), temp);
        }

        /**
           * Gets an attribute value.
           * @param name The name of the attribute to get.
           * @returns The value of the attribute corresponding to the given name.
           */
        template <class T>
        T getAttribute(const string name) const
        {
            return *((shared_ptr<T>)mAttributes[name].second);
        }

    private:
        typedef pair<size_t, shared_ptr<void>> AttributeValuePair;
        typedef map<string, AttributeValuePair> AttributeTable;

        AttributeTable mAttributes; //!< The attribute table.
    };

	typedef shared_ptr<EventData> EventDataSP;

} // End of namespace Event
} // End of namespace Prelude

#endif