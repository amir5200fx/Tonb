#pragma once
#ifndef _Cad_BlockEntity_Header
#define _Cad_BlockEntity_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	template<class EntityType>
	class Cad_BlockEntity
	{

		typedef std::map
			<
			Standard_Integer,
			std::shared_ptr<EntityType>
			> indexedMap;

		/*Private Data*/

		indexedMap theEntities_;

		//- private functions

		indexedMap::iterator SelectEntity(const Standard_Integer theIndex) const;

		std::shared_ptr<Cad_BlockEntity<EntityType>> Split(const std::vector<indexedMap::iterator>& theEntities);

		void Add(const std::shared_ptr<EntityType>& theEntity);

		void Remove(const std::shared_ptr<EntityType>& theEntity);


	public:

		auto NbEntities() const
		{
			return (Standard_Integer)theEntities_.size();
		}

		const auto& Entities() const
		{
			return theEntities_;
		}

		void RetrieveEntitiesTo(std::vector<std::shared_ptr<EntityType>>& theEntities) const;

		void Print(Standard_OStream& Ostream = cout) const;
	};
}

#include <Cad_BlockEntityI.hxx>

#endif // !_Cad_BlockEntity_Header
