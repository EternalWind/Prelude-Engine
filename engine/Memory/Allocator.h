#ifndef PL_MEMORY_ALLOCATOR
#define PL_MEMORY_ALLOCATOR

#include "Memory/Alloc.h"

#include "Core/Config.h"

#ifndef USE_DEFAULT_ALLOC
#define USE_DEFAULT_ALLOC (1)
#endif

namespace Prelude 
{
namespace Memory 
{

#if USE_DEFAULT_ALLOC
	typedef DefaultAlloc Alloc;
#else 
	typedef MallocAlloc Alloc;
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



} // end of namespace Memory

} // end of namespace Prelude

#endif
