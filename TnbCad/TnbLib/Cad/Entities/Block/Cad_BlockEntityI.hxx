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
	std::shared_ptr<Cad_BlockEntity<EntityType>> 
		tnbLib::Cad_BlockEntity<EntityType>::Split
		(
			const std::vector<typename Cad_BlockEntity<EntityType>::indexedMap::iterator>& theEntities
		)
	{
		if (theEntities.empty())
		{
			return nullptr;
		}

		auto block = std::make_shared<Cad_BlockEntity<EntityType>>();
		for (const auto& x : theEntities)
		{
			block->Add(x->second);
			theEntities_.erase(x);
		}
		return std::move(block);
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

	template<class EntityType>
	void Cad_BlockEntity<EntityType>::RetrieveEntitiesTo
	(
		std::vector<std::shared_ptr<EntityType>>& theEntities
	) const
	{
		theEntities.reserve(NbEntities());

		auto iter = theEntities_.begin();	
		while (iter NOT_EQUAL theEntities_.end())
		{
			theEntities.push_back(iter->second);
			iter++;
		}
	}

	template<class EntityType>
	void Cad_BlockEntity<EntityType>::Print
	(
		Standard_OStream & Ostream
	) const
	{
		Ostream << " Nb. of Entity = " << NbEntities() << std::endl;
		Ostream << " Entity List: " << std::endl;

		auto iter = theEntities_.begin();
		while (iter NOT_EQUAL theEntities_.end())
		{
			Ostream << iter->first << "  ";
			iter++;
		}
	}
}