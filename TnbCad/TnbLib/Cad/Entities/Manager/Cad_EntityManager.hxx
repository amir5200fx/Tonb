#pragma once
#ifndef _Cad_EntityManager_Header
#define _Cad_EntityManager_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>
#include <Global_Named.hxx>

#include <vector>
#include <list>
#include <map>
#include <memory>

namespace tnbLib
{

	// Forward Declarations
	template<class EntityType>
	class Cad_BlockEntity;

	template<class EntityType>
	class Cad_EntityManager
		: public Global_Named
	{

		typedef std::map
			<
			word, 
			std::shared_ptr<Cad_BlockEntity<EntityType>>
			> stringMapOfBlocks;

		/*Private Data*/

		stringMapOfBlocks theBlocks_;


		void Import(const word& theName, const std::shared_ptr<Cad_BlockEntity<EntityType>>& theBlock);

	public:

		Cad_EntityManager(const word& theName, const std::shared_ptr<Cad_BlockEntity<EntityType>>& theBlock);

		Standard_Integer Size() const;

		auto NbBlocks() const
		{
			return (Standard_Integer)theBlocks_.size();
		}

		Standard_Boolean HasBlock(const word& theName) const;
	};
}

#endif // !_Cad_EntityManager_Header
