#ifndef PL_UTIL_ITERATOR
#define PL_UTIL_ITERATOR

#include "Core/Config.h"

namespace pl 
{
namespace Util 
{

struct InputIteratorTag {};
struct OuputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template <class Category, 
		  class T, 
		  class Distance = ptrdiff_t, 
	      class Pointer = T*, 
		  class Reference = T&>
struct Iterator
{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Distance	difference_type;	
};

template <class I>
struct IteratorTraits
{
	typedef typename I::iterator_category	iterator_category;
	typedef typename I::value_type			value_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;
	typedef typename I::difference_type		difference_type;
};

template <class T>
struct IteratorTraits<T*> 
{
	typedef RandomAccessIteratorTag		iterator_category;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef ptrdiff_t					difference_type;
};

template <class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag		iterator_category;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef ptrdiff_t					difference_type;
};

} // end of namespace Util

} // end of namespace pl

#endif