#ifndef PL_MEMORY_ALLOC
#define PL_MEMORY_ALLOC

#ifndef PL_THROW_BAD_ALLOC
#include <iostream> 
#define PL_THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);
#endif

namespace Prelude 
{
namespace Memory 
{
/**
  * A lower-class allocator attempt to allocate more than 128 bytes memory
  * Out-of-memory measure is included
  */
class MallocAlloc 
{
public:
	static void* allocate(size_t bytes);

	static void deallocate(void *p, size_t bytes);

	static void* reallocate(void *p, size_t old_size, size_t new_size);

	/**
	  * Reset out-of-memory handler
	  * @param f new oom-handler
	  * @returns origin oom-handler
	  */
	void (*setOomAllocHandler(void(*f)()))();

private:

	/**
	  * Out-of-memory allocate function
	  * @param bytes Size of allocated bytes
	  * @returns A new block of memory
	  */
	static void* oomAlloc(size_t bytes);

	/**
	  * Out-of-memory reallocate function
	  * @param p Pointer to be reallocated
	  * @param bytes Size of reallocated bytes
	  */
	static void* oomRealloc(void *p, size_t bytes);

	static void (*mOomAllocHandler)(); //!<  

};


/**
  * Default allocator that only allocate not large than 128bytes memory
  */
class DefaultAlloc 
{
public:
	static void* allocate(size_t bytes);

	static void deallocate(void *p, size_t bytes);

	static void* reallocate(void *p, size_t old_size, size_t new_size);

	static size_t getHeapSize();

	enum { E_ALIGN = 8 };
	enum { E_MAX_BLOCK_SIZE = 128 };
	enum { E_LIST_SIZE = E_MAX_BLOCK_SIZE / E_ALIGN };

private:

	union obj 
	{
		union obj* next_free_block;
		char cdata[1];
	};

	static obj * volatile mFreeList[E_LIST_SIZE];		//!< arrays of pointers to the free blocks

	static char* mBeginFree;							//!< begin of memory pool
	static char* mEndFree;								//!< end of memory pool
	static size_t mHeapSize;							//!< size of alloc-heap

	/**
	  * Refill the mFreeList 
	  * @param bytes Size of block needed to be refilled
	  * @returns A block of new-allocate memory
	  */
	static void* __refill(size_t bytes);

	/**
	  * Call when mFreeList is out of memory, returns a continuous piece of memory
	  * @param unit Size of memory block
	  * @param nsize Counts of blocks to get
	  * @returns a piece of continous memory
	  */
	static char* __memoryPoolAlloc(size_t unit, size_t& nsize);

	static size_t __roundUp(size_t bytes);

	/**
	  * Returns mFreeList index
	  * @param bytes Size of memory block
	  * @returns mFreeList index
	  */
	static size_t __freeListIndex(size_t bytes);
};

} // end of namespace Memory

} // end of namespace Prelude

#endif