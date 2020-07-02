#pragma once
#ifndef _StbGMaker_HullCreator_Header
#define _StbGMaker_HullCreator_Header

#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_HullCreator
		: public StbGMaker_Alg
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Shape_Hull>
			theHull_;

	public:

		StbGMaker_HullCreator()
		{}

		StbGMaker_HullCreator
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		StbGMaker_HullCreator
		(
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		)
			: theHull_(theHull)
		{}

		StbGMaker_HullCreator
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		);

		StbGMaker_HullCreator
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<marineLib::Shape_Hull>& theHull
		);

		const auto& Shape() const
		{
			return theHull_;
		}

		Standard_Integer
			CreateWorkingPlane
			(
				const Standard_Real x
			) override;
	};
}

#endif // !_StbGMaker_HullCreator_Header
