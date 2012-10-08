#ifndef PL_MEMORY_ALLOCATOR
#define PL_MEMORY_ALLOCATOR

#include "Memory/Alloc.h"

#include "Core/Config.h"

#ifndef __USE_DEFAULT_ALLOC
#define __USE_DEFAULT_ALLOC (1)
#endif

namespace pl 
{
namespace Memory 
{

#if __USE_DEFAULT_ALLOC
	typedef __default_alloc Alloc;
#else 
	typedef __malloc_alloc Alloc;
#endif

/**
  * A basic allocator, accepct void type
  */
class PRELUDE_ENGINE Allocator 
{
public:
	/**
	  * Allocate a piece of continuous memory
	  * @param bytes Size of memory to allocate
	  * @returns A piece of continuous memory
	  */
	static void * allocate(size_t bytes); 

	static void * allocate(); 

	/**
	  * Reallocate a piece of continuous memory
	  * @param bytes Size of memory to reallocate
	  * @returns A piece of continuous memory
	  */
	static void* reallocate(void * p, size_t old_size, size_t new_size); 

	/**
	  * Deallocate a piece of continuous memory
	  * @param p pointer of the memory to deallocate
	  * @param bytes Size of memory to deallocate
	  */
	static void deallocate(void * p, size_t bytes);

	static void deallocate(void * p);
};


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////

/**
  * Basic data allocator, allow template
  */
template <class T>
class DataAllocator
{
public:
	typedef T		value_type;
	typedef T*		pointer;
	typedef size_t	size_type;
	
	static pointer allocate(size_type n);

	static pointer allocate();

	static void deallocate(pointer p, size_type n);

	static void deallocate(pointer p);

	static pointer reallocate(pointer p, size_type old_size, size_type new_size);
};

template <class T>
typename DataAllocator<T>::pointer 
	DataAllocator<T>::allocate(typename DataAllocator<T>::size_type n)
{
	return (pointer)Alloc::allocate(sizeof(value_type) * n);
}

template <class T>
typename DataAllocator<T>::pointer 
	DataAllocator<T>::allocate()
{
	return (pointer)Alloc::allocate(sizeof(value_type));
}

template <class T>
typename DataAllocator<T>::pointer
	DataAllocator<T>::reallocate(
	typename DataAllocator<T>::pointer p,
	typename DataAllocator<T>::size_type old_size,
	typename DataAllocator<T>::size_type new_size)
{
	return (pointer)Alloc::reallocate((pointer)p, sizeof(value_type) * old_size, sizeof(value_type) * new_size);	
}

template <class T>
void DataAllocator<T>::deallocate(
	typename DataAllocator<T>::pointer p,
	typename DataAllocator<T>::size_type n)
{
	Alloc::deallocate((pointer)p, sizeof(value_type) * n);
}

template <class T>
void DataAllocator<T>::deallocate(
	typename DataAllocator<T>::pointer p)
{
	Alloc::deallocate((pointer)p, sizeof(value_type));
}

} // end of namespace Memory

} // end of namespace pl

#endif
