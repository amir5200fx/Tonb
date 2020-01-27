#pragma once
#include <Global_Macros.hxx>
#include <error.hxx>
#include <OSstream.hxx>
namespace tnbLib
{

	template<class EntityType>
	typename Cad_BlockEntity<EntityType>::indexedMap::iterator
		Cad_BlockEntity<EntityType>::SelectEntity
		(
			const Standard_Integer theIndex
		) const
	{
		auto iter = theEntities_.find(theIndex);
		if (iter IS_EQUAL theEntities_.end())
		{
			FatalErrorIn("void SelectEntity(const Standard_Integer theIndex) const")
				<< "The Entity is NOT in the List" << endl
				<< abort(FatalError);
		}
		return std::move(iter);
	}

	template<class EntityType>
	void Cad_BlockEntity<EntityType>::Add
	(
		const std::shared_ptr<EntityType>& theEntity
	)
	{
		auto insert = 
			theEntities_.insert(std::make_pair(theEntity->Index(), theEntity));
		if (insert.second IS_EQUAL Standard_False)
		{
			FatalErrorIn("void Add(const std::shared_ptr<EntityType>& theEntity)")
				<< "Duplicate Data" << endl
				<< abort(FatalError);
		}
	}

	template<class EntityType>
	void Cad_BlockEntity<EntityType>::Remove
	(
		const std::shared_ptr<EntityType>& theEntity
	)
	{
		auto iter = theEntities_.find(theEntity->Index());
		if (iter IS_EQUAL theEntities_.end())
		{
			FatalErrorIn("void Remove(const std::shared_ptr<EntityType>& theEntity)")
				<< "Not found the entity"
				<< abort(FatalError);
		}
		theEntities_.erase(iter);
	}

}