#pragma once
#ifndef _StbGMaker_TankCreator_Header
#define _StbGMaker_TankCreator_Header

#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_TankCreator
		: public StbGMaker_Alg
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Shape_Tank> 
			theTank_;

	public:

		StbGMaker_TankCreator()
		{}

		StbGMaker_TankCreator
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		StbGMaker_TankCreator
		(
			const std::shared_ptr<marineLib::Shape_Tank>& theTank
		)
			: theTank_(theTank)
		{}

		StbGMaker_TankCreator
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<marineLib::Shape_Tank>& theTank
		);

		StbGMaker_TankCreator
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<marineLib::Shape_Tank>& theTank
		);

		const auto& Shape() const
		{
			return theTank_;
		}

		Standard_Integer 
			CreateWorkingPlane
			(
				const Standard_Real x
			) override;
	};
}

#endif // !_StbGMaker_TankCreator_Header
