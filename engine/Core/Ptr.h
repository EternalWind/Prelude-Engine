#ifndef PL_CORE_PTR
#define PL_CORE_PTR

#include "Core/Config.h"
#include "Core/PtrBase.h"

namespace pl
{
namespace Core
{

/**
  * Global smart pointer
  * A simpler shared pointer
  */
template<class T>
class Ptr 
{
public:
	/**
	  * Default constructor
	  */
    Ptr();

	/**
	  * Construtor
	  * @param p original pointer
	  */
	Ptr(T * p);

	/**
	  * Constructor
	  * @param p Original pointer
	  */
	template <class Y> explicit Ptr(Y * p);

	/**
	  * Copy constructor
	  * @param rhs Copy instance
	  */
	explicit Ptr(const Ptr<T> & rhs); 

	/**
	  * Copy constructor of other type
	  * @param rhs Copy instance
	  */
	template <class Y>
	explicit Ptr(const Ptr<Y> & rhs);

	/**
	  * Default destructor
	  */
	~Ptr();

	/**
	  * Return original pointer
	  * @returns Original pointer
	  */
	T * get() const;

	/**
	  * Return if the original pointer is null
	  * @returns If the original pointer is null
	  */
	bool isNull() const;

	/**
	  * Return use_count of the pointer
	  * @returns use_count of the pointer
	  */
	int useCount() const;

	/**
	  * Return if this pointer is unique
	  * @returns If this pointer is unique
	  */
	bool unique() const;

	/**
	  * Reset the current pointer to null
	  */
	void reset();

	/**
	  * Reset the current pointer
	  * @param p new pointer to be set
	  */
	template <class Y> 
	void reset(Y * p);

	template <class Y> 
	void reset(const Ptr<Y> & rhs);

	/**
	  * Swap the pointer to other one
	  * @param The pointer to swap
	  */
	void swap(Ptr<T> & rhs);

	/**
	  * Overload operator(=)
	  */
	Ptr<T> & operator=(const Ptr<T> & rhs);

	/**
	  * Overload operator(=) of other type
	  */
	template <class Y>
	Ptr<T> & operator=(const Ptr<Y> & rhs);

	/**
	  * Overload operator(==)
	  */ 
	template <class Y>
	bool operator==(const Ptr<Y> & rhs) const;

	/**
	  * Overload operator (!=)
	  */ 
	template <class Y>
	bool operator!=(const Ptr<Y> & rhs) const;

	/**
	  * Overload operator(!)
	  */
	bool operator!() const;

	/**
	  * Overload operator(->)
	  */
	T * operator->() const;

	/**
	  * Overload operator(*)
	  */
	T & operator*() const;

private:
	PtrBase<T>* mBaseCount;						//!< Base counter handler of Ptr
	template<class Y> friend class Ptr;  //!< Friend class 
};

template <class T>
Ptr<T>::Ptr(): mBaseCount(nullptr) {}

template <class T>
Ptr<T>::Ptr(T * p)
	: mBaseCount(nullptr)
{
	if (p != nullptr)
	{
		mBaseCount = new PtrBase<T>(p);
	}
}

template <class T>
template <class Y> 
Ptr<T>::Ptr(Y * p)
	: mBaseCount(nullptr) 
{
	if (p != nullptr)
	{
		mBaseCount = new PtrBase<T>((T*)p);
	}
}

template <class T>
Ptr<T>::Ptr(const Ptr & rhs) 
	: mBaseCount(nullptr)
{
	if (!rhs.isNull()) 
	{
		mBaseCount = rhs.mBaseCount;
		mBaseCount->addRef();
	}
}

template <class T>
template <class Y> 
Ptr<T>::Ptr(const Ptr<Y> & rhs)
	: mBaseCount(nullptr)
{
	if (!rhs.isNull()) 
	{
		mBaseCount = (PtrBase<T>*)(rhs.mBaseCount);
		mBaseCount->addRef();
	}
}

template <class T>
Ptr<T>::~Ptr()
{
	this->reset();
}

template <class T>
T * Ptr<T>::get() const 
{
	if (mBaseCount != nullptr) 
	{
		return mBaseCount->get();
	}
	return nullptr;
}

template <class T>
bool Ptr<T>::isNull() const 
{
	return (mBaseCount == nullptr);
}

template <class T>
int Ptr<T>::useCount() const 
{
	return (mBaseCount == nullptr ? 0 : mBaseCount->useCount());
}

template <class T>
bool Ptr<T>::unique() const 
{
	return this->useCount() == 1;	
}

template <class T>
void Ptr<T>::reset()
{
	if (mBaseCount != nullptr) 
	{
		bool result = mBaseCount->release();
		if (result)
		{
			delete mBaseCount;
		}
		mBaseCount = nullptr;
	}
}

template <class T>
template <class Y>
void Ptr<T>::reset(Y * p) 
{
	this->reset();
	if (p != nullptr)
	{
		mBaseCount = new PtrBase<T>((T*)p);
	}
}

template <class T>
template <class Y> 
void Ptr<T>::reset(const Ptr<Y> & rhs) 
{
	this->reset();		
	if (!rhs.isNull())
	{
		mBaseCount = (PtrBase<T>*)(rhs.mBaseCount);
		mBaseCount->addRef();
	}
}

template <class T>
void Ptr<T>::swap(Ptr<T> & rhs)
{
	std::swap(this->mBaseCount, rhs.mBaseCount);
}

template <class T>
Ptr<T> & Ptr<T>::operator=(const Ptr<T> & rhs)
{
	this->reset();
	if (!rhs.isNull()) 
	{
		mBaseCount = rhs.mBaseCount;
		mBaseCount->addRef();
	}
	return *this;
}

template <class T>
template <class Y>
Ptr<T> & Ptr<T>::operator=(const Ptr<Y> & rhs)
{
	this->reset();
	if (!rhs.isNull()) 
	{
		mBaseCount = (PtrBase<T>*)(rhs.mBaseCount);
		mBaseCount->addRef();
	}
	return *this;
}

template <class T>
template <class Y>
bool Ptr<T>::operator==(const Ptr<Y> & rhs) const
{
	return this->get() == rhs.get();
}

template <class T>
template <class Y>
bool Ptr<T>::operator!=(const Ptr<Y> & rhs) const
{
	return this->get() != rhs.get();
}

template <class T>
bool Ptr<T>::operator!() const
{
	return this->isNull();
}

template <class T>
T * Ptr<T>::operator->() const 
{
	return this->get();
}

template <class T>
T & Ptr<T>::operator*() const 
{
	return *(this->get());
}

} // end of namespace Core

} // end of namespace pl
#endif