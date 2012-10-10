#ifndef PL_UTIL_ENUMERATOR
#define PL_UTIL_ENUMERATOR

#include "Util/Iterator.h"

namespace Prelude
{
namespace Util
{

template <class Iter>
class Enumerator
{
public:
	typedef typename IteratorTraits<Iter>::ValueType ValueType;
	typedef typename IteratorTraits<Iter>::Reference Reference;
	typedef typename IteratorTraits<Iter>::Pointer Pointer;
	typedef Iter Iterator;

	/**
	  * Default Constructor
	  */
	Enumerator();

	/**
	  * Constructor
	  * @param iter_begin Begin of iterator
	  * @param iter_end End of iterator
	  */
	Enumerator(Iter begin, Iter end);

	/**
	  * Constructor
	  * @param container Container which is enumerable
	  */
	template <class Y>
	Enumerator(const Y& container);

	/**
	  * Return if there are elements still haven't been visited
	  * @returns If there are elements still haven't been visited
	  */
	bool next();

	/**
	  * Reload operator ->
	  */
	Pointer operator->() const;

	/**
	  * Reload operator ->
	  */
	Reference operator*() const;

	/**
	  * Get the current value of this enumerator
	  * @returns Current value of this enumerator
	  */
	Reference val() const;


private:
	
	Iterator mCurPtr;	      //!< Current pointer
	Iterator mThisEnd;        //!< End of this enumerator
	bool mStartedFlag;         //!< Flag for whether this enumerator is switched on 
};

template <class Iter>
Enumerator<Iter>::Enumerator(): 
	mStartedFlag(false),
	mCurPtr(Iter()),
	mThisEnd(mCurPtr)
{
}

template <class Iter>
Enumerator<Iter>::Enumerator(Iter begin, Iter end):
	mStartedFlag(false),
	mCurPtr(begin),
	mThisEnd(end)
{
}

template <class Iter>
bool Enumerator<Iter>::next()
{
	if (mCurPtr == mThisEnd) 
	{
		return false;
	}
	// Check if enumerator has been switched on
	if (!mStartedFlag)
	{
		mStartedFlag = true;	
		return true;
	}
	++mCurPtr;

	return (mCurPtr != mThisEnd);
}

template <class Iter>
typename Enumerator<Iter>::Pointer
	Enumerator<Iter>::operator->() const
{
	return &(*mCurPtr);
}

template <class Iter>
typename Enumerator<Iter>::Reference
	Enumerator<Iter>::operator*() const
{
	return *mCurPtr;
}

template <class Iter>
typename Enumerator<Iter>::Reference
	Enumerator<Iter>::val() const 
{
	return *mCurPtr;
}


} // End of namespace Util

} // End of namespace Prelude

#endif