#pragma once
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
	theBucket_.push_back(theObject);
}

template<class T>
inline void tnbLib::Geo3d_BalPrTreeBucket<T>::Insert(T && theObject)
{
	theBucket_.push_back(std::move(theObject));
}

template<class T>
inline void tnbLib::Geo3d_BalPrTreeBucket<T>::Remove(const T & theObject)
{
	theBucket_.remove(theObject);
}