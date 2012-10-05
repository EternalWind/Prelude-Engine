#ifndef PL_CORE_CORECONFIG
#define PL_CORE_CORECONFIG

#define __DeclareClass(ClassType) \
public: \
	static const size_t mObjectSize; \


#define __DefiniteClass(ClassType) \
	const size_t ClassType::mObjectSize = sizeof(ClassType);

#endif
