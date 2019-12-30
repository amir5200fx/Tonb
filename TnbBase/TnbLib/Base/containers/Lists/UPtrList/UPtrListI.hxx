#pragma once
#include <error.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
tnbLib::label tnbLib::UPtrList<T>::size() const
{
	return ptrs_.size();
}


template<class T>
bool tnbLib::UPtrList<T>::empty() const
{
	return ptrs_.empty();
}


template<class T>
void tnbLib::UPtrList<T>::resize(const label newSize)
{
	this->setSize(newSize);
}


template<class T>
bool tnbLib::UPtrList<T>::set(const label i) const
{
	return ptrs_[i] != NULL;
}

template<class T>
T* tnbLib::UPtrList<T>::set(const label i, T* ptr)
{
	T* old = ptrs_[i];
	ptrs_[i] = ptr;
	return old;
}

template<class T>
tnbLib::Xfer<tnbLib::UPtrList<T>> tnbLib::UPtrList<T>::xfer()
{
	return xferMove(*this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
const T& tnbLib::UPtrList<T>::operator[](const label i) const
{
	if (!ptrs_[i])
	{
		FatalErrorIn("UPtrList::operator[] const")
			<< "hanging pointer, cannot dereference"
			<< abort(FatalError);
	}

	return *(ptrs_[i]);
}


template<class T>
T& tnbLib::UPtrList<T>::operator[](const label i)
{
	if (!ptrs_[i])
	{
		FatalErrorIn("UPtrList::operator[]")
			<< "hanging pointer, cannot dereference"
			<< abort(FatalError);
	}

	return *(ptrs_[i]);
}


template<class T>
const T* tnbLib::UPtrList<T>::operator()(const label i) const
{
	return ptrs_[i];
}


// * * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * //

template<class T>
tnbLib::UPtrList<T>::iterator::iterator(T** ptr)
	:
	ptr_(ptr)
{}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator==(const iterator& iter) const
{
	return ptr_ == iter.ptr_;
}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator!=(const iterator& iter) const
{
	return ptr_ != iter.ptr_;
}

template<class T>
T& tnbLib::UPtrList<T>::iterator::operator*()
{
	return **ptr_;
}

template<class T>
T& tnbLib::UPtrList<T>::iterator::operator()()
{
	return operator*();
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator++()
{
	++ptr_;
	return *this;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator++(int)
{
	iterator tmp = *this;
	++ptr_;
	return tmp;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator--()
{
	--ptr_;
	return *this;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator--(int)
{
	iterator tmp = *this;
	--ptr_;
	return tmp;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator+=(label n)
{
	ptr_ += n;
	return *this;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::operator+(const typename UPtrList<T>::iterator& iter, label n)
{
	typename UPtrList<T>::iterator tmp = iter;
	return tmp += n;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::operator+(label n, const typename UPtrList<T>::iterator& iter)
{
	typename UPtrList<T>::iterator tmp = iter;
	return tmp += n;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::iterator::operator-=(label n)
{
	ptr_ -= n;
	return *this;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::operator-(const typename UPtrList<T>::iterator& iter, label n)
{
	typename UPtrList<T>::iterator tmp = iter;
	return tmp -= n;
}

template<class T>
tnbLib::label tnbLib::operator-
(
	const typename UPtrList<T>::iterator& iter1,
	const typename UPtrList<T>::iterator& iter2
	)
{
	return (iter1.ptr_ - iter2.ptr_) / sizeof(T*);
}

template<class T>
T& tnbLib::UPtrList<T>::iterator::operator[](label n)
{
	return *(*this + n);
}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator<(const iterator& iter) const
{
	return ptr_ < iter.ptr_;
}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator>(const iterator& iter) const
{
	return ptr_ > iter.ptr_;
}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator<=(const iterator& iter) const
{
	return ptr_ <= iter.ptr_;
}

template<class T>
bool tnbLib::UPtrList<T>::iterator::operator>=(const iterator& iter) const
{
	return ptr_ >= iter.ptr_;
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::begin()
{
	return ptrs_.begin();
}

template<class T>
typename tnbLib::UPtrList<T>::iterator
tnbLib::UPtrList<T>::end()
{
	return ptrs_.end();
}


// ************************************************************************* //