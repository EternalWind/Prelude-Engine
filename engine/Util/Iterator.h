#ifndef PL_UTIL_ITERATOR
#define PL_UTIL_ITERATOR

#include "Core/Config.h"
#include "Util/TypeTraits.h"

namespace pl 
{
namespace Util 
{

struct input_iterator_tag {};
struct ouput_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Category, 
		  class T, 
		  class Distance = ptrdiff_t, 
	      class Pointer = T*, 
		  class Reference = T&>
struct iterator
{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Distance	difference_type;	
};

template <class I>
struct iterator_traits
{
	typedef typename I::iterator_category	iterator_category;
	typedef typename I::value_type			value_type;
	typedef typename I::pointer				pointer;
	typedef typename I::reference			reference;
	typedef typename I::difference_type		difference_type;
};

template <class T>
struct iterator_traits<T*> 
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef ptrdiff_t					difference_type;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef ptrdiff_t					difference_type;
};

} // end of namespace Util

} // end of namespace pl

#endif