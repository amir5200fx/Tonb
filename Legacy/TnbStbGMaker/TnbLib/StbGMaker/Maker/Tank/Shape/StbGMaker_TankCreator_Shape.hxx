#pragma once
#ifndef _StbGMaker_TankCreator_Shape_Header
#define _StbGMaker_TankCreator_Shape_Header

#include <StbGMaker_TankCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class TankCreator_Shape
			: public StbGMaker_TankCreator
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Shape_Tank>
				theTank_;

			TNB_SERIALIZATION(TnbStbGMaker_EXPORT);

		protected:

			//- default constructor is provided for loading purposes only!

			TankCreator_Shape()
			{}

		public:

			// constructors

			TnbStbGMaker_EXPORT explicit TankCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);

			TnbStbGMaker_EXPORT TankCreator_Shape
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);


			//- public functions and operators

			const auto& Shape() const
			{
				return theTank_;
			}

			Standard_Boolean HasShape() const override
			{
				return Standard_True;
			}

			TnbStbGMaker_EXPORT Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::TankCreator_Shape);

#endif // !_StbGMaker_TankCreator_Shape_Header
