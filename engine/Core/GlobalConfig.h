#ifndef PL_CORE_CORECONFIG
#define PL_CORE_CORECONFIG

#include <cstdint>

#ifdef Prelude_Engine_EXPORTS
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


#define __DeclareClass(ClassType) \
public: \
	static const size_t mObjectSize; \


#define __DefiniteClass(ClassType) \
	const size_t ClassType::mObjectSize = sizeof(ClassType);

#endif
