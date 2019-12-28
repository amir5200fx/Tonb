#pragma once
#include <pTraits.hxx>
#include <Swap.hxx>
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * Static Members  * * * * * * * * * * * * * * //

template<class T>
const tnbLib::UList<T> tnbLib::UList<T>::zero;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::UList<T>::UList()
	:
	v_(0),
	size_(0)
{}


template<class T>
inline tnbLib::UList<T>::UList(T* __restrict v, label size)
	:
	v_(v),
	size_(size)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline const tnbLib::UList<T>& tnbLib::UList<T>::null()
{
	return zero;
}


// Reset in slicing.  HJ. 19/Oct/2008
template<class T>
inline void tnbLib::UList<T>::reset(T* __restrict v, label size)
{
	v_ = v;
	size_ = size;
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::fcIndex(const label i) const
{
	return (i == size() - 1 ? 0 : i + 1);
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::rcIndex(const label i) const
{
	return (i ? i - 1 : size() - 1);
}


// Check start is within valid range (0 ... size-1).
template<class T>
inline void tnbLib::UList<T>::checkStart(const label start) const
{
	if (start < 0 || (start && start >= size_))
	{
		FatalErrorIn("UList<T>::checkStart(const label)")
			<< "start " << start << " out of range 0 ... " << max(size_ - 1, 0)
			<< abort(FatalError);
	}
}


// Check size is within valid range (0 ... size).
template<class T>
inline void tnbLib::UList<T>::checkSize(const label size) const
{
	if (size<0 || size>size_)
	{
		FatalErrorIn("UList<T>::checkSize(const label)")
			<< "size " << size << " out of range 0 ... " << size_
			<< abort(FatalError);
	}
}


// Check index i is within valid range (0 ... size-1).
template<class T>
inline void tnbLib::UList<T>::checkIndex(const label i) const
{
	if (!size_)
	{
		FatalErrorIn("UList<T>::checkIndex(const label)")
			<< "attempt to access element from zero sized list"
			<< abort(FatalError);
	}
	else if (i < 0 || i >= size_)
	{
		FatalErrorIn("UList<T>::checkIndex(const label)")
			<< "index " << i << " out of range 0 ... " << size_ - 1
			<< abort(FatalError);
	}
}


template<class T>
inline T& tnbLib::UList<T>::first()
{
	return this->operator[](0);
}


template<class T>
inline const T& tnbLib::UList<T>::first() const
{
	return this->operator[](0);
}


template<class T>
inline T& tnbLib::UList<T>::last()
{
	return this->operator[](this->size() - 1);
}


template<class T>
inline const T& tnbLib::UList<T>::last() const
{
	return this->operator[](this->size() - 1);
}


template<class T>
inline const T* tnbLib::UList<T>::cdata() const
{
	return v_;
}


template<class T>
inline T* tnbLib::UList<T>::data()
{
	return v_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// element access
template<class T>
inline T& tnbLib::UList<T>::operator[](const label i)
{
#   ifdef FULLDEBUG
	checkIndex(i);
#   endif
	return v_[i];
}


namespace tnbLib
{

	// Template specialization for bool
	template<>
	inline const bool& UList<bool>::operator[](const label i) const
	{
		// lazy evaluation - return false for out-of-range
		if (i < size_)
		{
			return v_[i];
		}
		else
		{
			return pTraits<bool>::zero;
		}
	}

} // end of namespace tnbLib


// const element access
template<class T>
inline const T& tnbLib::UList<T>::operator[](const label i) const
{
#   ifdef FULLDEBUG
	checkIndex(i);
#   endif
	return v_[i];
}


// Allow cast to a const List<T>&
template<class T>
inline tnbLib::UList<T>::operator const tnbLib::List<T>&() const
{
	return *reinterpret_cast<const List<T>*>(this);
}


// * * * * * * * * * * * * * * STL Member Functions  * * * * * * * * * * * * //

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::begin()
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::begin() const
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::cbegin() const
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::end()
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::end() const
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::cend() const
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::rbegin()
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::rbegin() const
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::crbegin() const
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::rend()
{
	return &v_[-1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::rend() const
{
	return &v_[-1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::crend() const
{
	return &v_[-1];
}

template<class T>
inline tnbLib::label tnbLib::UList<T>::size() const
{
	return size_;
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::max_size() const
{
	return labelMax;
}


template<class T>
inline bool tnbLib::UList<T>::empty() const
{
	return !size_;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class T>
inline void tnbLib::reverse(UList<T>& ul, const label n)
{
	for (int i = 0; i < n / 2; i++)
	{
		Swap(ul[i], ul[n - 1 - i]);
	}
}

template<class T>
inline void tnbLib::reverse(UList<T>& ul)
{
	reverse(ul, ul.size());
}


// ************************************************************************* //