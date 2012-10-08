#ifndef PL_CORE_PTR_BASE
#define PL_CORE_PTR_BASE

#include "Core/Config.h"

#include "Memory/Allocator.h"

namespace Prelude
{
namespace Core
{
/**
  * Base class of Ptr<T>
  * Store original pointer and maintains a reference count of the pointer
  */
template <class T>
class PtrBase
{
	PRELUDE_OBJECT(PtrBase)
public:

	/**
	  * The construtor
	  * @param p Original pointer
	  */
	PtrBase(T * p);

	/**
	  * Return reference count
	  * @returns reference count
	  */
	int useCount();

	/**
	  * Return original pointer
	  * @returns Original pointer 
	  */
	T * get() const;

	/**
	  * Add a reference count to original pointer
	  */
	void addRef();

	/**
	  * Release a reference count of the original pointer
	  * When mRefCount is equal to 0, release the memory block
	  * @returns If mRefCount is equal to 0
	  */ 
	bool release();



private:
	T * mOrigPtr;		//!< The naked pointer
	int mRefCount;		//!< Reference count
};

template <class T>
IMPL_PRELUDE_TEMPLATE_OBJECT(PtrBase, T)

template <class T>
PtrBase<T>::PtrBase(T * p) 
{
	mOrigPtr = p;
	mRefCount = 1;
}

template <class T>
int PtrBase<T>::useCount()
{
	return mRefCount;
}

template <class T>
T * PtrBase<T>::get() const 
{
	return mOrigPtr;
}

template <class T>
void PtrBase<T>::addRef()
{
	++mRefCount;
}

template <class T>
bool PtrBase<T>::release() 
{
	if (--mRefCount == 0)
	{
		delete mOrigPtr;
		return true;
	}
	return false;
}

} // end of namespace Core

} // end of namespace Prelude
#endif