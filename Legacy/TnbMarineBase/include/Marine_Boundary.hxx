#pragma once
#ifndef _Marine_Boundary_Header
#define _Marine_Boundary_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Global_AccessMethod.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	template<class EntityType>
	class Cad_BlockEntity;

	class TModel_Surface;

	class Marine_Boundary
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Marine_Boundary>
	{

		typedef Cad_BlockEntity<TModel_Surface> surfBlock;

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<surfBlock>>
			theSurfaces_;

	protected:

		TnbMarine_EXPORT Marine_Boundary();

		TnbMarine_EXPORT Marine_Boundary
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_Boundary
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

	public:

		virtual ~Marine_Boundary()
		{}

		TnbMarine_EXPORT Standard_Integer NbBlocks() const;

		const auto& SurfaceBlocks() const
		{
			return theSurfaces_;
		}

		TnbMarine_EXPORT std::vector<std::shared_ptr<surfBlock>>
			RetrieveBlocks() const;

		TnbMarine_EXPORT void ImportBlock
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<surfBlock>& theBlock
		);

		TnbMarine_EXPORT void RemoveBlock(const Standard_Integer theIndex);

		TnbMarine_EXPORT void RetrieveBlocksTo
		(
			std::vector<std::shared_ptr<surfBlock>>& theBlocks
		) const;
		
		//- Macros
	};
}

#endif // !_Marine_Boundary_Header
