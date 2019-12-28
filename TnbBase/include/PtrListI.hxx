#pragma once
#include <autoPtr.hxx>
#include <tmp.hxx>
#include <error.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
tnbLib::label tnbLib::PtrList<T>::size() const
{
	return ptrs_.size();
}


template<class T>
bool tnbLib::PtrList<T>::empty() const
{
	return ptrs_.empty();
}


template<class T>
void tnbLib::PtrList<T>::resize(const label newSize)
{
	this->setSize(newSize);
}


template<class T>
bool tnbLib::PtrList<T>::set(const label i) const
{
	return ptrs_[i] != NULL;
}


template<class T>
tnbLib::autoPtr<T> tnbLib::PtrList<T>::set(const label i, T* ptr)
{
	autoPtr<T> old(ptrs_[i]);

	ptrs_[i] = ptr;

	return old;
}


template<class T>
tnbLib::autoPtr<T> tnbLib::PtrList<T>::set
(
	const label i,
	const autoPtr<T>& aptr
)
{
	return set(i, const_cast<autoPtr<T>&>(aptr).ptr());
}


template<class T>
tnbLib::autoPtr<T> tnbLib::PtrList<T>::set
(
	const label i,
	const tmp<T>& t
)
{
	return set(i, const_cast<tmp<T>&>(t).ptr());
}


template<class T>
tnbLib::Xfer<tnbLib::PtrList<T> > tnbLib::PtrList<T>::xfer()
{
	return xferMove(*this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
const T& tnbLib::PtrList<T>::operator[](const label i) const
{
	if (!ptrs_[i])
	{
		FatalErrorIn("PtrList::operator[] const")
			<< "hanging pointer, cannot dereference"
			<< abort(FatalError);
	}

	return *(ptrs_[i]);
}


template<class T>
T& tnbLib::PtrList<T>::operator[](const label i)
{
	if (!ptrs_[i])
	{
		FatalErrorIn("PtrList::operator[]")
			<< "hanging pointer, cannot dereference"
			<< abort(FatalError);
	}

	return *(ptrs_[i]);
}


template<class T>
const T* tnbLib::PtrList<T>::operator()(const label i) const
{
	return ptrs_[i];
}


// * * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * //

template<class T>
tnbLib::PtrList<T>::iterator::iterator(T** ptr)
	:
	ptr_(ptr)
{}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator==(const iterator& iter) const
{
	return ptr_ == iter.ptr_;
}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator!=(const iterator& iter) const
{
	return ptr_ != iter.ptr_;
}

template<class T>
T& tnbLib::PtrList<T>::iterator::operator*()
{
	return **ptr_;
}

template<class T>
T& tnbLib::PtrList<T>::iterator::operator()()
{
	return operator*();
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator++()
{
	++ptr_;
	return *this;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator++(int)
{
	iterator tmp = *this;
	++ptr_;
	return tmp;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator--()
{
	--ptr_;
	return *this;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator--(int)
{
	iterator tmp = *this;
	--ptr_;
	return tmp;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator+=(label n)
{
	ptr_ += n;
	return *this;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::operator+(const typename PtrList<T>::iterator& iter, label n)
{
	typename PtrList<T>::iterator tmp = iter;
	return tmp += n;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::operator+(label n, const typename PtrList<T>::iterator& iter)
{
	typename PtrList<T>::iterator tmp = iter;
	return tmp += n;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::iterator::operator-=(label n)
{
	ptr_ -= n;
	return *this;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::operator-(const typename PtrList<T>::iterator& iter, label n)
{
	typename PtrList<T>::iterator tmp = iter;
	return tmp -= n;
}

template<class T>
tnbLib::label tnbLib::operator-
(
	const typename PtrList<T>::iterator& iter1,
	const typename PtrList<T>::iterator& iter2
	)
{
	return (iter1.ptr_ - iter2.ptr_) / sizeof(T*);
}

template<class T>
T& tnbLib::PtrList<T>::iterator::operator[](label n)
{
	return *(*this + n);
}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator<(const iterator& iter) const
{
	return ptr_ < iter.ptr_;
}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator>(const iterator& iter) const
{
	return ptr_ > iter.ptr_;
}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator<=(const iterator& iter) const
{
	return ptr_ <= iter.ptr_;
}

template<class T>
bool tnbLib::PtrList<T>::iterator::operator>=(const iterator& iter) const
{
	return ptr_ >= iter.ptr_;
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::begin()
{
	return ptrs_.begin();
}

template<class T>
typename tnbLib::PtrList<T>::iterator
tnbLib::PtrList<T>::end()
{
	return ptrs_.end();
}



// ************************************************************************* //