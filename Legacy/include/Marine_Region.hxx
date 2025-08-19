#pragma once
#ifndef _Marine_Region_Header
#define _Marine_Region_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <Marine_Module.hxx>

#include <memory>
#include <map>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Boundary;
	class Marine_Physics;
	class Cad3d_TModel;

	class Marine_Region
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Marine_Region>
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<Marine_Boundary>>
			theBoundaries_;

		std::shared_ptr<Cad3d_TModel> theModel_;
		std::shared_ptr<Marine_Physics> thePhysics_;

	protected:

		TnbMarine_EXPORT Marine_Region();

		TnbMarine_EXPORT Marine_Region
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT Marine_Region
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

	public:

		virtual ~Marine_Region()
		{}

		TnbMarine_EXPORT Standard_Integer NbBoundaries() const;

		const auto& Boundaries() const
		{
			return theBoundaries_;
		}

		const auto& Model() const
		{
			return theModel_;
		}

		const auto& Physics() const
		{
			return thePhysics_;
		}

		TnbMarine_EXPORT std::vector<std::shared_ptr<Marine_Boundary>>
			RetrieveBoundaries() const;

		TnbMarine_EXPORT void ImportToBoundaries
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<Marine_Boundary>& theBoundary
		);

		TnbMarine_EXPORT void RemoveFromBoundaries
		(
			const Standard_Integer theIndex
		);

		TnbMarine_EXPORT void RetrieveBoundariesTo
		(
			std::vector<std::shared_ptr<Marine_Boundary>>& theBoudaries
		) const;

		void SetModel(const std::shared_ptr<Cad3d_TModel>& theModel)
		{
			theModel_ = theModel;
		}

		void SetPhysics(const std::shared_ptr<Marine_Physics>& thePhysics)
		{
			thePhysics_ = thePhysics;
		}

	};
}

#endif // !_Marine_Region_Header
