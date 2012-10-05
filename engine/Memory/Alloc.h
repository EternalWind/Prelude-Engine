#ifndef PL_MEMORY_ALLOC
#define PL_MEMORY_ALLOC

#ifndef __PL_THROW_BAD_ALLOC
#include <iostream> 
#define __PL_THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1);
#endif

namespace pl 
{
namespace Memory 
{
/**
  * A lower-class allocator attempt to allocate more than 128 bytes memory
  * Out-of-memory measure is included
  */
class __malloc_alloc 
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
	void (*set_oom_alloc_handler(void(*f)()))() 
	{
		void (*origin)() = oom_alloc_handler;
		oom_alloc_handler = f;
		return origin;
	}

private:

	/**
	  * Out-of-memory allocate function
	  * @param bytes Size of allocated bytes
	  * @returns A new block of memory
	  */
	static void* oom_alloc(size_t bytes);

	/**
	  * Out-of-memory reallocate function
	  * @param p Pointer to be reallocated
	  * @param bytes Size of reallocated bytes
	  */
	static void* oom_realloc(void *p, size_t bytes);

	static void (*oom_alloc_handler)(); //!<  

};


/**
  * Default allocator that only allocate not large than 128bytes memory
  */
class __default_alloc 
{
public:
	static void* allocate(size_t bytes);

	static void deallocate(void *p, size_t bytes);

	static void* reallocate(void *p, size_t old_size, size_t new_size);

	static size_t get_heap_size();

	enum { __ALIGN = 8 };
	enum { __MAX_BLOCK_SIZE = 128 };
	enum { __LIST_SIZE = __MAX_BLOCK_SIZE / __ALIGN };

private:

	union obj 
	{
		union obj* next_free_block;
		char cdata[1];
	};

	static obj * volatile free_list[__LIST_SIZE];		//!< arrays of pointers to the free blocks

	static char* begin_free;							//!< begin of memory pool
	static char* end_free;								//!< end of memory pool
	static size_t heap_size;							//!< size of alloc-heap

	/**
	  * Refill the free_list 
	  * @param bytes Size of block needed to be refilled
	  * @returns A block of new-allocate memory
	  */
	static void* refill(size_t bytes);

	/**
	  * Call when free_list is out of memory, returns a continuous piece of memory
	  * @param unit Size of memory block
	  * @param nsize Counts of blocks to get
	  * @returns a piece of continous memory
	  */
	static char* memory_pool_alloc(size_t unit, size_t& nsize);

	static size_t ROUND_UP(size_t bytes);

	/**
	  * Returns free_list index
	  * @param bytes Size of memory block
	  * @returns free_list index
	  */
	static size_t FREELIST_INDEX(size_t bytes);
};

} // end of namespace Memory

} // end of namespace pl

#endif