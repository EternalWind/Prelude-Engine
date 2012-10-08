#ifndef PL_IO_INTERFACE_SERIALIZABLE
#define PL_IO_INTERFACE_SERIALIZABLE

#include "Core/Config.h"
#include "IO/IStream.h"

#include <string>

using namespace std;

namespace pl
{
namespace IO
{
/**
  * An interface for all the serializable classes.
  */
interface PRELUDE_ENGINE ISerializable
{
public:
	/**
	  * Serializes this object.
	  * @param stream The output stream.
	  */
	virtual void serialize(OUT IStream& stream) const = 0;

	/**
	  * Deserializes an object from a given stream.
	  * @param stream The input stream.
	  */
	virtual void deserialize(IN IStream& stream) = 0;

	/**
	  * Converts this object to a string.
	  * @returns The output string.
	  */
	virtual string toString() const = 0;

	virtual ~ISerializable() = 0 {}
};

} // End of namespace IO

} // End of namespace pl

#endif