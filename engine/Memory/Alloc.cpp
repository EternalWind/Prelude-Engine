#include "Memory/Alloc.h"

namespace Prelude 
{
namespace Memory 
{

// MallocAlloc
void (*MallocAlloc::mOomAllocHandler)() = 0;

void* MallocAlloc::allocate(size_t bytes) 
{
	void *result = malloc(bytes);
	if (!result) 
	{
		result = oomAlloc(bytes);
	}
	return result;
}

void MallocAlloc::deallocate(void *p, size_t bytes) 
{
	free(p);
}

void* MallocAlloc::reallocate(void *p, size_t old_size, size_t new_size) 
{
	void *result = malloc(new_size);
	if (!result) 
	{
		result = oomRealloc(p, new_size);
	}
	return result;
}

void* MallocAlloc::oomAlloc(size_t bytes) 
{
	void *result;

	for (; ; ) 
	{
		if (!mOomAllocHandler) 
		{
			PL_THROW_BAD_ALLOC; 
		}
		mOomAllocHandler();
		result = malloc(bytes);
		if (result)
		{
			break;
		}
	}
	return result;
}

void* MallocAlloc::oomRealloc(void *p, size_t bytes) 
{
	void *result;

	for (; ; ) 
	{
		if (!mOomAllocHandler) 
		{
			PL_THROW_BAD_ALLOC;
		}
		mOomAllocHandler();
		result = realloc(p, bytes);
		if (result) 
		{
			break;
		}
	}
	return result;
}

void (*MallocAlloc::setOomAllocHandler(void(*f)()))() 
{
	void (*origin)() = mOomAllocHandler;
	mOomAllocHandler = f;
	return origin;
}

// DefaultAlloc
char* DefaultAlloc::mBeginFree = 0;
char* DefaultAlloc::mEndFree = 0;
size_t DefaultAlloc::mHeapSize = 0;

DefaultAlloc::obj* volatile \
	DefaultAlloc::mFreeList[DefaultAlloc::E_LIST_SIZE] = \
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

size_t DefaultAlloc::__roundUp(size_t bytes) 
{
	return ((bytes + E_ALIGN - 1) & ~(E_ALIGN - 1));
}

size_t DefaultAlloc::__freeListIndex(size_t bytes) 
{
	return (bytes + E_ALIGN - 1) / E_ALIGN - 1;
}

size_t DefaultAlloc::getHeapSize() 
{
	return mHeapSize;
}

void* DefaultAlloc::allocate(size_t bytes) 
{
	if (bytes > E_MAX_BLOCK_SIZE) 
	{
		return MallocAlloc::allocate(bytes);
	}

	obj * volatile * my_free_list;
	obj * result;

	my_free_list = mFreeList + __freeListIndex(bytes);

	if (*my_free_list) 
	{
		result = *my_free_list;			
		*my_free_list = result->next_free_block;
	} 
	else
	{
		return __refill(__roundUp(bytes));
	}

	return result;
}

void* DefaultAlloc::__refill(size_t bytes) 
{
	obj * volatile * my_free_list;
	obj *result, *current_block, *next_block;
	size_t nsize = 20;

	char *pool = __memoryPoolAlloc(bytes, nsize); 
	result = (obj*)pool;
	if (nsize == 1) 
	{
		return result;
	}

	// *my_free_list points to the current free list
	my_free_list = mFreeList + __freeListIndex(bytes);
	*my_free_list = next_block = (obj*)(pool + bytes);

	for (int i = 1; ; ++i) 
	{
		current_block = next_block;
		next_block = (obj*)((char*)current_block + bytes);
		if (i == nsize - 1) 
		{
			current_block->next_free_block = 0;
			break;
		}
		current_block->next_free_block = next_block;
	}

	return result;
}

char* DefaultAlloc::__memoryPoolAlloc(size_t unit, size_t& nsize) 
{
	size_t bytes_left = mEndFree - mBeginFree;
	size_t total_bytes = unit * nsize; 
	char *result;

	// enough space 
	if (total_bytes <= bytes_left) 
	{
		result = mBeginFree;
		mBeginFree += total_bytes;
		return result;
	} 
	else if (unit <= bytes_left)  // not less than 1 unit 
	{
		nsize = bytes_left / unit;
		result = mBeginFree;
		mBeginFree += (nsize * unit);
		return result;
	} 
	else
	{
		obj * volatile * my_free_list;

		if (bytes_left > 0) 
		{
			my_free_list = mFreeList + __freeListIndex(bytes_left);
			/*obj *p = (obj*)mBeginFree;
			p->next_free_block = *my_free_list;
			*my_free_list = p;
			*/
			((obj*)mBeginFree)->next_free_block = *my_free_list;
			*my_free_list = (obj*)mBeginFree;
		}

		size_t bytes_to_get = total_bytes * 2 + __roundUp(mHeapSize >> 4);
		mBeginFree = (char*)malloc(bytes_to_get);
		// If alloc failed, find whether there are any free blocks in existed mFreeList
		if (!mBeginFree) 
		{
			for (size_t now = unit + E_ALIGN; now <= E_MAX_BLOCK_SIZE; now += E_ALIGN) 
			{
				my_free_list = mFreeList + __freeListIndex(now);
				if (*my_free_list) 
				{
					mBeginFree = (char*)(*my_free_list);
					*my_free_list = (*my_free_list)->next_free_block;
					mEndFree = mBeginFree + now;
					return __memoryPoolAlloc(unit, nsize);
				}
			}
			// Oooops, seems can't allocate any more
			bytes_to_get = unit * 2;
			mBeginFree = (char*)MallocAlloc::allocate(bytes_to_get);
		}
		mEndFree = mBeginFree + bytes_to_get;
		mHeapSize += bytes_to_get;
		return __memoryPoolAlloc(unit, nsize);
	}
}

void DefaultAlloc::deallocate(void *p, size_t bytes) 
{
	if (bytes > E_MAX_BLOCK_SIZE) 
	{
		MallocAlloc::deallocate(p, bytes);
		return;
	}

	obj *q = (obj*)p;
	obj * volatile * my_free_list = mFreeList + __freeListIndex(bytes);
	q->next_free_block = *my_free_list;
	*my_free_list = q;
}

void* DefaultAlloc::reallocate(void *p, size_t old_size, size_t new_size) 
{
	if (new_size > E_MAX_BLOCK_SIZE && old_size > E_MAX_BLOCK_SIZE)  
	{   // Not in mFreeList  
		return realloc(p, new_size);
	}
	if (__roundUp(new_size) == __roundUp(old_size)) 
	{   // Points to the same block
		return p;
	}

	size_t copy_size = new_size < old_size ? new_size : old_size;
	void *result = allocate(new_size);
	memcpy(result, p, copy_size);
	deallocate(p, old_size);
	return result;
}

} // end of namespace Memory

} // end of namespace Prelude