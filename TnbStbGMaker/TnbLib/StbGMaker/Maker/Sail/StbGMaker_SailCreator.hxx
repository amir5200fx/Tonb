#pragma once
#ifndef _StbGMaker_SailCreator_Header
#define _StbGMaker_SailCreator_Header

#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_xDistb;

	class StbGMaker_SailCreator
		: public StbGMaker_Alg
	{

		/*Private Data*/

		std::shared_ptr<marineLib::Shape_Sail> 
			theSail_;

	public:

		StbGMaker_SailCreator()
		{}

		StbGMaker_SailCreator
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		StbGMaker_SailCreator
		(
			const std::shared_ptr<marineLib::Shape_Sail>& theSail
		)
			: theSail_(theSail)
		{}

		StbGMaker_SailCreator
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<marineLib::Shape_Sail>& theSail
		);

		StbGMaker_SailCreator
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<marineLib::Shape_Sail>& theSail
		);

		const auto& Shape() const
		{
			return theSail_;
		}

		Standard_Integer
			CreateWorkingPlane
			(
				const Standard_Real x
			) override;
	};
}

#endif // !_StbGMaker_SailCreator_Header
