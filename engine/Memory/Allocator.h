#ifndef PL_MEMORY_ALLOCATOR
#define PL_MEMORY_ALLOCATOR

#include "Memory/Alloc.h"

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
  * A simple allocator interface
  */
class Allocator 
{
public:
	/**
	  * Allocate a piece of continuous memory
	  * @param bytes Size of memory to allocate
	  * @returns A piece of continuous memory
	  */
	static void * allocate(size_t bytes) 
	{
		return Alloc::allocate(bytes);
	}

	static void * allocate() 
	{
		return Alloc::allocate(4);
	}

	/**
	  * Reallocate a piece of continuous memory
	  * @param bytes Size of memory to reallocate
	  * @returns A piece of continuous memory
	  */
	static void* reallocate(void * p, size_t old_size, size_t new_size) 
	{
		return Alloc::reallocate(p, old_size, new_size);
	}

	/**
	  * Deallocate a piece of continuous memory
	  * @param p pointer of the memory to deallocate
	  * @param bytes Size of memory to deallocate
	  */
	static void deallocate(void * p, size_t bytes) 
	{
		Alloc::deallocate(p, bytes);
	}
};

} // end of namespace Memory

} // end of namespace pl

#endif
