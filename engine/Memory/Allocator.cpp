#include "Memory/Allocator.h"

namespace pl
{
namespace Memory
{

void * Allocator::allocate(size_t bytes)
{
	return Alloc::allocate(bytes);
}

void * Allocator::allocate() 
{
	return Alloc::allocate(4);
}

void* Allocator::reallocate(void * p, size_t old_size, size_t new_size) 
{
	return Alloc::reallocate(p, old_size, new_size);
}

void Allocator::deallocate(void * p, size_t bytes) 
{
	Alloc::deallocate(p, bytes);
}

} // end of namespace Memory

} // end of namespace pl