#include "Memory/Alloc.h"

namespace pl 
{
namespace Memory 
{

// __malloc_alloc
void (*__malloc_alloc::oom_alloc_handler)() = 0;

void* __malloc_alloc::allocate(size_t bytes) 
{
	void *result = malloc(bytes);
	if (!result) 
	{
		result = oom_alloc(bytes);
	}
	return result;
}

void __malloc_alloc::deallocate(void *p, size_t bytes) 
{
	free(p);
}

void* __malloc_alloc::reallocate(void *p, size_t old_size, size_t new_size) 
{
	void *result = malloc(new_size);
	if (!result) 
	{
		result = oom_realloc(p, new_size);
	}
	return result;
}

void* __malloc_alloc::oom_alloc(size_t bytes) 
{
	void *result;

	for (; ; ) 
	{
		if (!oom_alloc_handler) 
		{
			__PL_THROW_BAD_ALLOC; 
		}
		oom_alloc_handler();
		result = malloc(bytes);
		if (result)
		{
			break;
		}
	}
	return result;
}

void* __malloc_alloc::oom_realloc(void *p, size_t bytes) 
{
	void *result;

	for (; ; ) 
	{
		if (!oom_alloc_handler) 
		{
			__PL_THROW_BAD_ALLOC;
		}
		oom_alloc_handler();
		result = realloc(p, bytes);
		if (result) 
		{
			break;
		}
	}
	return result;
}

// __default_alloc
char* __default_alloc::begin_free = 0;
char* __default_alloc::end_free = 0;
size_t __default_alloc::heap_size = 0;

__default_alloc::obj* volatile \
	__default_alloc::free_list[__default_alloc::__LIST_SIZE] = \
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

size_t __default_alloc::ROUND_UP(size_t bytes) 
{
	return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));
}

size_t __default_alloc::FREELIST_INDEX(size_t bytes) 
{
	return (bytes + __ALIGN - 1) / __ALIGN - 1;
}

size_t __default_alloc::get_heap_size() 
{
	return heap_size;
}

void* __default_alloc::allocate(size_t bytes) 
{
	if (bytes > __MAX_BLOCK_SIZE) 
	{
		return __malloc_alloc::allocate(bytes);
	}

	obj * volatile * my_free_list;
	obj * result;

	my_free_list = free_list + FREELIST_INDEX(bytes);

	if (*my_free_list) 
	{
		result = *my_free_list;			
		*my_free_list = result->next_free_block;
	} 
	else
	{
		return refill(ROUND_UP(bytes));
	}

	return result;
}

void* __default_alloc::refill(size_t bytes) 
{
	obj * volatile * my_free_list;
	obj *result, *current_block, *next_block;
	size_t nsize = 20;

	char *pool = memory_pool_alloc(bytes, nsize); 
	result = (obj*)pool;
	if (nsize == 1) 
	{
		return result;
	}

	// *my_free_list points to the current free list
	my_free_list = free_list + FREELIST_INDEX(bytes);
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

char* __default_alloc::memory_pool_alloc(size_t unit, size_t& nsize) 
{
	size_t bytes_left = end_free - begin_free;
	size_t total_bytes = unit * nsize; 
	char *result;

	// enough space 
	if (total_bytes <= bytes_left) 
	{
		result = begin_free;
		begin_free += total_bytes;
		return result;
	} 
	else if (unit <= bytes_left)  // not less than 1 unit 
	{
		nsize = bytes_left / unit;
		result = begin_free;
		begin_free += (nsize * unit);
		return result;
	} 
	else
	{
		obj * volatile * my_free_list;

		if (bytes_left > 0) 
		{
			my_free_list = free_list + FREELIST_INDEX(bytes_left);
			/*obj *p = (obj*)begin_free;
			p->next_free_block = *my_free_list;
			*my_free_list = p;
			*/
			((obj*)begin_free)->next_free_block = *my_free_list;
			*my_free_list = (obj*)begin_free;
		}

		size_t bytes_to_get = total_bytes * 2 + ROUND_UP(heap_size >> 4);
		begin_free = (char*)malloc(bytes_to_get);
		// If alloc failed, find whether there are any free blocks in existed free_list
		if (!begin_free) 
		{
			for (size_t now = unit + __ALIGN; now <= __MAX_BLOCK_SIZE; now += __ALIGN) 
			{
				my_free_list = free_list + FREELIST_INDEX(now);
				if (*my_free_list) 
				{
					begin_free = (char*)(*my_free_list);
					*my_free_list = (*my_free_list)->next_free_block;
					end_free = begin_free + now;
					return memory_pool_alloc(unit, nsize);
				}
			}
			// Oooops, seems can't allocate any more
			bytes_to_get = unit * 2;
			begin_free = (char*)__malloc_alloc::allocate(bytes_to_get);
		}
		end_free = begin_free + bytes_to_get;
		heap_size += bytes_to_get;
		return memory_pool_alloc(unit, nsize);
	}
}

void __default_alloc::deallocate(void *p, size_t bytes) 
{
	if (bytes > __MAX_BLOCK_SIZE) 
	{
		__malloc_alloc::deallocate(p, bytes);
		return;
	}

	obj *q = (obj*)p;
	obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes);
	q->next_free_block = *my_free_list;
	*my_free_list = q;
}

void* __default_alloc::reallocate(void *p, size_t old_size, size_t new_size) 
{
	if (new_size > __MAX_BLOCK_SIZE && old_size > __MAX_BLOCK_SIZE)  
	{   // Not in free_list  
		return realloc(p, new_size);
	}
	if (ROUND_UP(new_size) == ROUND_UP(old_size)) 
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

} // end of namespace pl