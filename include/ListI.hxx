#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::List<T>::List()
{}


template<class T>
tnbLib::autoPtr<tnbLib::List<T> > tnbLib::List<T>::clone() const
{
	return autoPtr<List<T> >(new List<T>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
const tnbLib::List<T>& tnbLib::List<T>::null()
{
	return zero;
}


template<class T>
void tnbLib::List<T>::resize(const label newSize)
{
	this->setSize(newSize);
}


template<class T>
void tnbLib::List<T>::resize(const label newSize, const T& a)
{
	this->setSize(newSize, a);
}


template<class T>
T& tnbLib::List<T>::newElmt(const label i)
{
	if (i >= this->size())
	{
		setSize(2 * this->size());
	}

	return UList<T>::operator[](i);
}


template<class T>
void tnbLib::List<T>::size(const label n)
{
	UList<T>::size_ = n;
}


template<class T>
tnbLib::label tnbLib::List<T>::size() const
{
	return UList<T>::size_;
}


template<class T>
tnbLib::Xfer< tnbLib::List<T> > tnbLib::List<T>::xfer()
{
	return xferMove(*this);
}


template<class T>
void tnbLib::List<T>::append(const UList<T>& lst)
{
	if (this == &lst)
	{
		FatalErrorIn
		(
			"List<T>::append(const UList<T>&)"
		) << "attempted appending to self" << abort(FatalError);
	}

	label nextFree = this->size();
	setSize(nextFree + lst.size());

	forAll(lst, elemI)
	{
		this->operator[](nextFree++) = lst[elemI];
	}
}


template<class T>
void tnbLib::List<T>::append(const UIndirectList<T>& lst)
{
	label nextFree = this->size();
	setSize(nextFree + lst.size());

	forAll(lst, elemI)
	{
		this->operator[](nextFree++) = lst[elemI];
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::List<T>::operator=(const T& t)
{
	UList<T>::operator=(t);
}