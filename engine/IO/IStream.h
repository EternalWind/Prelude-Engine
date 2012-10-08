#ifndef PL_IO_INTERFACE_STREAM
#define PL_IO_INTERFACE_STREAM

#include "Core/Config.h"

#include <cstdint>

namespace pl
{
namespace IO
{
/**
  * An interface for streams.
  */
interface PRELUDE_ENGINE IStream
{
public:
	/**
	  * Reads data from the stream.
	  * @param buffer The output buffer.
	  * @param buffer_size The size of the buffer.
	  * @param bytes_to_read The number of bytes you want to read from the stream. -1 means reading as many as possible to fill up the buffer.
	  * @param offset The offset used to skip a given number of bytes in the stream.
	  * @returns The actual number of read bytes.
	  */
	virtual unsigned read(OUT byte* buffer, unsigned buffer_size, int bytes_to_read = -1, unsigned offset = 0) = 0;

	/**
	  * Writes data to the stream.
	  * @param buffer The input buffer.
	  * @param buffer_size The size of the buffer.
	  * @param bytes_to_write The number of bytes you want to write to the stream. -1 means writing all the data in the buffer to the stream.
	  * @param offset The offset used to skip a given number of bytes in the buffer.
	  * @returns The actual number of written bytes.
	  */
	virtual unsigned write(const IN byte* buffer, unsigned buffer_size, int bytes_to_write = -1, unsigned offset = 0) = 0;

	virtual IStream& operator << (const IN byte& data) = 0;
	virtual IStream& operator << (const IN byte2& data) = 0;
	virtual IStream& operator << (const IN byte4& data) = 0;
	virtual IStream& operator << (const IN byte8& data) = 0;

	virtual IStream& operator >> (OUT byte& data) = 0;
	virtual IStream& operator >> (OUT byte2& data) = 0;
	virtual IStream& operator >> (OUT byte4& data) = 0;
	virtual IStream& operator >> (OUT byte8& data) = 0;

	virtual ~IStream() = 0 {}
};

} // End of namespace IO

} // End of namespace pl

#endif