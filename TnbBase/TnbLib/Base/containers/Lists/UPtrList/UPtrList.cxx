#include <UPtrList.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T>
tnbLib::UPtrList<T>::UPtrList()
	:
	ptrs_()
{}


template<class T>
tnbLib::UPtrList<T>::UPtrList(const label s)
	:
	ptrs_(s, reinterpret_cast<T*>(0))
{}


template<class T>
tnbLib::UPtrList<T>::UPtrList(const Xfer<UPtrList<T> >& lst)
{
	transfer(lst());
}


template<class T>
tnbLib::UPtrList<T>::UPtrList(UPtrList<T>& a, bool reUse)
	:
	ptrs_(a.ptrs_, reUse)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void tnbLib::UPtrList<T>::setSize(const label newSize)
{
	label oldSize = size();

	if (newSize <= 0)
	{
		clear();
	}
	else if (newSize != oldSize)
	{
		ptrs_.setSize(newSize);
	}

	if (newSize > oldSize)
	{
		// set new elements to NULL
		for (register label i = oldSize; i < newSize; i++)
		{
			ptrs_[i] = NULL;
		}
	}
}


template<class T>
void tnbLib::UPtrList<T>::clear()
{
	ptrs_.clear();
}


// Transfer the contents of the argument List into this List
// and anull the argument list
template<class T>
void tnbLib::UPtrList<T>::transfer(UPtrList<T>& a)
{
	ptrs_.transfer(a.ptrs_);
}


template<class T>
void tnbLib::UPtrList<T>::reorder(const UList<label>& oldToNew)
{
	if (oldToNew.size() != size())
	{
		FatalErrorIn("UPtrList<T>::reorder(const UList<label>&)")
			<< "Size of map (" << oldToNew.size()
			<< ") not equal to list size (" << size()
			<< ")." << abort(FatalError);
	}

	List<T*> newPtrs_(ptrs_.size(), reinterpret_cast<T*>(0));

	forAll(*this, i)
	{
		label newI = oldToNew[i];

		if (newI < 0 || newI >= size())
		{
			FatalErrorIn("UPtrList<T>::reorder(const UList<label>&)")
				<< "Illegal index " << newI << nl
				<< "Valid indices are 0.." << size() - 1
				<< abort(FatalError);
		}

		if (newPtrs_[newI])
		{
			FatalErrorIn("UPtrList<T>::reorder(const UList<label>&)")
				<< "reorder map is not unique; element " << newI
				<< " already set." << abort(FatalError);
		}
		newPtrs_[newI] = ptrs_[i];
	}

	forAll(newPtrs_, i)
	{
		if (!newPtrs_[i])
		{
			FatalErrorIn("UPtrList<T>::reorder(const UList<label>&)")
				<< "Element " << i << " not set after reordering." << nl
				<< abort(FatalError);
		}
	}

	ptrs_.transfer(newPtrs_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <UPtrListIO.cxx>