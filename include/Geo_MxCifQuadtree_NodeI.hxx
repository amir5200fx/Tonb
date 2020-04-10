#pragma once
#include <error.hxx>
#include <OSstream.hxx>
namespace tnbLib
{
	template<class T>
	std::shared_ptr<T> Geo_MxCifQuadtree_Node<T>::Remove
	(
		const Standard_Integer theIndex
	)
	{
		auto iter = theItems_.find(theIndex);
		if (iter IS_EQUAL theItems_.end())
		{
			FatalErrorIn("std::shared_ptr<T> Geo_MxCifQuadtree_Node<T>::Remove()")
				<< "the item is not in the map" << endl
				<< abort(FatalError);
		}

		auto item = std::move(iter->second);
		theItems_.erase(iter);

		return std::move(item);
	}

	template<class T>
	void Geo_MxCifQuadtree_Node<T>::Insert
	(
		const Standard_Integer theIndex, 
		const std::shared_ptr<T>& theItem
	)
	{
		auto insert = theItems_.insert(std::make_pair(theIndex, theItem));
		if (NOT insert.second)
		{
			FatalErrorIn("void Geo_MxCifQuadtree_Node<T>::Insert()")
				<< "duplicate data!" << endl
				<< abort(FatalError);
		}
	}
}