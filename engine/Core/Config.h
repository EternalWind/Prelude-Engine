#ifndef PL_CORE_CONFIG
#define PL_CORE_CONFIG

#include <cstdint>

#ifdef Prelude_EXPORTS
#define PRELUDE_ENGINE __declspec(dllexport)
#else
#define PRELUDE_ENGINE __declspec(dllimport)
#endif

#define OUT
#define IN
#define interface class
#define implements public

typedef int8_t byte;
typedef int16_t byte2;
typedef int32_t byte4;
typedef int64_t byte8;


#include "Memory/Allocator.h"

#define __DeclareClass(ClassType) \
public: \
	static const size_t mObjectSize; \
	void* operator new(size_t size) \
	{ \
		return Memory::Allocator::allocate(size); \
	} \
	void operator delete(void * p) \
	{\
		Memory::Allocator::deallocate(p, ClassType::mObjectSize); \
	}


#define __DefiniteClass(ClassType) \
	const size_t ClassType::mObjectSize = sizeof(ClassType);

#endif
