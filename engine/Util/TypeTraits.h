#ifndef PL_CORE_TYPE_TRAITS
#define PL_CORE_TYPE_TRAITS

#define PL_TEMPLATE_NULL template<>

namespace Prelude 
{
namespace Util 
{
/**
  * TAG for Plain-Old-Data
  * If a class has this tag, it means it can be assigned with memset() or memmove()
  */
struct TrueTypeTag {};
/**
  * TAG for Un-Plain-Old-Data
  */
struct FalseTypeTag {};


template <class Type>
struct TypeTraits 
{ 
	typedef FalseTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<bool> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<char> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<signed char> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned char> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<wchar_t> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<short> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned short> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<int> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned int> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<long> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned long> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<long long> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned long long> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<float> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<double> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<long double> 
{
	typedef TrueTypeTag SystemBasicType;
};

template <class type>
struct TypeTraits<type*> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<char*> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<signed char*> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<unsigned char*> 
{
	typedef TrueTypeTag SystemBasicType;
};

PL_TEMPLATE_NULL struct TypeTraits<const char*> 
{
	typedef TrueTypeTag SystemBasicType;
};


} // End of namespace Util

} // End of namespace Prelude

#endif