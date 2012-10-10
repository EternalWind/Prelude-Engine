#ifndef PL_MEMORY_CONSTRUCTOR
#define PL_MEMORY_CONSTRUCTOR

#include "Core/Config.h"
#include "Util/TypeTraits.h"
#include "Util/Iterator.h"

#include <new.h>
#include <cstring>

namespace Prelude
{
namespace Memory
{

/**
  * Class to hold static functions of initializations
  */
class Constructor
{
public:

	/**
	  * Basic construct function
	  * Generally it will call the default copy constructor of T
	  */
	template <class T, class Value>
	static inline void construct(T * p, const Value & val);

	/**
	  * Basic destruct function
	  * Generally it will call the 
	  * @param p pointer to destroy
	  */
	template <class T>
	static inline void destroy(T * p);

	template <class Iter>
	static inline void destroy(Iter begin, Iter end);

	/**
	  * Destroy function for char *, do nothing
	  * @param begin begin of area to destroy
	  * @param end end of area to destroy 
	  */
	static inline void destroy(char * begin, char * end) {}

	/**
	  * Fill and initialize 
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param val Init value
	  */
	template <class Iter, class Value>
	static inline void fillInit(Iter begin, Iter end, const Value & val);	

	/**
	  * Fill and initialize for char*
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param ch Init character 
	  */
	static inline void fillInit(char * begin, char * end, const char & ch);

	/**
	  * Fill and initialize n elements
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param n Number of elements
	  * @param val Init value
	  */
	template <class Iter, class Value>
	static inline void fillInitN(Iter begin, size_t n, const Value & val);	

	/**
	  * Fill and initialize n character for char*
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param n Number of character
	  * @param ch Init character 
	  */
	static inline void fillInitN(char * begin, size_t n, const char & ch);

	/**
	  * Copy and initialize
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param out Output destination
	  */
	template <class InputIter, class OutputIter>
	static inline void copyInit(InputIter begin, InputIter end, OutputIter out);

	/**
	  * Copy and initialize for char*
	  * @param begin Begin of initialized area
	  * @param end End of initialized area
	  * @param out Output destination
	  */
	static inline void copyInit(char * begin, char * end, char * out);

private:

	template <class Iter>
	static inline void __destroy(Iter begin, Iter end, Util::TrueTypeTag) {}

	template <class Iter>
	static inline void __destroy(Iter begin, Iter end, Util::FalseTypeTag);

	template <class Iter, class Value>
	static inline void __fillInit(Iter begin, Iter end, const Value & val, Util::TrueTypeTag);

	template <class Iter, class Value>
	static inline void __fillInit(Iter begin, Iter end, const Value & val, Util::FalseTypeTag);

	template <class Iter, class Value>
	static inline void __fillInitN(Iter begin, size_t n, const Value & val, Util::TrueTypeTag);

	template <class Iter, class Value>
	static inline void __fillInitN(Iter begin, size_t n, const Value & val, Util::FalseTypeTag);

	template <class InputIter, class OutputIter>
	static inline void __copyInit(InputIter begin, InputIter end, OutputIter out, Util::TrueTypeTag);

	template <class InputIter, class OutputIter>
	static inline void __copyInit(InputIter begin, InputIter end, OutputIter out, Util::FalseTypeTag);
};

template <class T, class Value>
inline void Constructor::construct(T * p, const Value & val)
{
	// Construct without new-operation
	::new (p) T(val);
}

template <class T>
inline void Constructor::destroy(T * p)
{
	p->~T();
}

template <class Iter>
inline void Constructor::destroy(Iter begin, Iter end)
{
	typedef typename Util::IteratorTraits<Iter>::ValueType type; 
	typedef typename Util::TypeTraits<type>::SystemBasicType sbt;
	__destroy(begin, end, sbt());
}

template <class Iter>
inline void Constructor::__destroy(Iter begin, Iter end, Util::FalseTypeTag)
{
	// Call the default destroy function
	for (; begin != end; ++begin)
	{
		destroy(&(*begin));
	}
}

template <class Iter, class Value>
inline void Constructor::fillInit(Iter begin, Iter end, const Value & val)
{
	typedef typename Util::IteratorTraits<Iter>::ValueType type;
	typedef typename Util::TypeTraits<type>::SystemBasicType sbt;
	__fillInit(begin, end, val, sbt());
}

template <class Iter, class Value>
inline void Constructor::__fillInit(Iter begin, Iter end, const Value & val, Util::TrueTypeTag)
{
	for (; begin != end; ++begin)
	{
		*begin = val;
	}
}

template <class Iter, class Value>
inline void Constructor::__fillInit(Iter begin, Iter end, const Value & val, Util::FalseTypeTag)
{
	for (; begin != end; ++begin)
	{
		construct(&(*begin), val);
	}
}

inline void Constructor::fillInit(char * begin, char * end, const char & ch)
{
	memset(begin, ch, size_t(end - begin));
}

template <class Iter, class Value>
inline void Constructor::fillInitN(Iter begin, size_t n, const Value & val)
{
	typedef typename Util::IteratorTraits<Iter>::ValueType type;
	typedef typename Util::TypeTraits<type>::SystemBasicType sbt;
	__fillInitN(begin, n, val, sbt());
}

template <class Iter, class Value>
inline void Constructor::__fillInitN(Iter begin, size_t n, const Value & val, Util::TrueTypeTag)
{
	for (; n > 0; --n, ++begin)
	{
		*begin = val;
	}
}

template <class Iter, class Value>
inline void Constructor::__fillInitN(Iter begin, size_t n, const Value & val, Util::FalseTypeTag)
{
	for (; n > 0; --n; ++begin)
	{
		construct(&(*begin), val);
	}
}

inline void Constructor::fillInitN(char * begin, size_t n, const char & ch)
{
	memset(begin, ch, n);
}

template <class InputIter, class OutputIter>
inline void Constructor::copyInit(InputIter begin, InputIter end, OutputIter out) 
{
	typedef typename Util::IteratorTraits<InputIter>::ValueType type;
	typedef typename Util::TypeTraits<type>::SystemBasicType sbt;
	__copyInit(begin, end, out, sbt());
}

inline void Constructor::copyInit(char * begin, char * end, char * out) 
{
	memmove(out, begin, size_t(end - begin));
}

template <class InputIter, class OutputIter>
inline void Constructor::__copyInit(InputIter begin, InputIter end, OutputIter out, Util::TrueTypeTag)
{
	// System basic type, such as int, double, float...
	typedef typename Util::IteratorTraits<InputIter>::ValueType type;
	memmove(out, begin, sizeof(type) * size_t(end - begin));
}

template <class InputIter, class OutputIter>
inline void Constructor::__copyInit(InputIter begin, InputIter end, OutputIter out, Util::FalseTypeTag)
{
	for (; begin != end; ++begin, ++out)
	{
		construct(&(*out), *begin);
	}
} 

} // End of namespace Memory

} // End of namespace Prelude

#endif