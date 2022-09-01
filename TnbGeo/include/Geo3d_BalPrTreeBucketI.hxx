#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class T>
inline Standard_Boolean tnbLib::Geo3d_BalPrTreeBucket<T>::IsEmpty() const
{
	return Standard_Boolean(theBucket_.empty());
}

template<class T>
inline Standard_Integer tnbLib::Geo3d_BalPrTreeBucket<T>::Size() const
{
	return Standard_Integer(theBucket_.size());
}

template<class T>
inline void tnbLib::Geo3d_BalPrTreeBucket<T>::Insert(const T & theObject)
{
	theBucket_.insert(theObject);
}

template<class T>
inline void tnbLib::Geo3d_BalPrTreeBucket<T>::Insert(T && theObject)
{
	theBucket_.insert(std::move(theObject));
}

template<class T>
inline void tnbLib::Geo3d_BalPrTreeBucket<T>::Remove(const T & theObject)
{
	auto iter = theBucket_.find(theObject);
	if (iter IS_EQUAL theBucket_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the object doesn't belong to the set." << endl
			<< abort(FatalError);
	}
	theBucket_.erase(iter);
}