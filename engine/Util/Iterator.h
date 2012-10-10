#ifndef PL_UTIL_ITERATOR
#define PL_UTIL_ITERATOR

#include "Core/Config.h"

namespace Prelude 
{
namespace Util 
{

// Iterator Type

/**
  * Tag for InputIterator
  */
struct InputIteratorTag {};

/**
  * Tag for OutputIterator
  */
struct OuputIteratorTag {};

/**
  * Tag for ForwardIterator
  * ForwardIterator has read-write access ability
  */
struct ForwardIteratorTag : public InputIteratorTag {};

/**
  * Tag for BidirectIterator
  * BidirectIterator can access both forward and backward
  */
struct BidirectIteratorTag : public ForwardIteratorTag {};

/**
  * Tag for RandomIterator
  * RandomIterator can access randomly
  */
struct RandomIteratorTag : public BidirectIteratorTag {};


/**
  * Default Iterator
  */
template <class IterType, 
		  class T, 
		  class DistanceType = ptrdiff_t, 
	      class PointerType = T*, 
		  class ReferenceType = T&>
struct Iterator
{
	typedef IterType		IteratorType;
	typedef T				ValueType;
	typedef PointerType		Pointer;
	typedef ReferenceType	Reference;
	typedef DistanceType	Difference;	
};

/**
  * Iterator-traits tool
  * Traits the property of Iterator<I>
  */
template <class I>
struct IteratorTraits
{
	typedef typename I::IteratorType		IteratorType;
	typedef typename I::ValueType			ValueType;
	typedef typename I::Pointer				Pointer;
	typedef typename I::Reference			Reference;
	typedef typename I::Difference			Difference;
};

template <class T>
struct IteratorTraits<T*> 
{
	typedef RandomIteratorTag		IteratorType;
	typedef T						ValueType;
	typedef T*						Pointer;
	typedef T&						Reference;
	typedef ptrdiff_t				Difference;
};

template <class T>
struct IteratorTraits<const T*>
{
	typedef RandomIteratorTag		IteratorType;
	typedef T						ValueType;
	typedef const T*				Pointer;
	typedef const T&				Reference;
	typedef ptrdiff_t				Difference;
};

} // end of namespace Util

} // end of namespace Prelude

#endif