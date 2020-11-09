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

			DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

		public:

			TankCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);

			TankCreator_Shape
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<marineLib::Shape_Tank>& theTank
			);

			const auto& Shape() const
			{
				return theTank_;
			}

			Standard_Boolean HasShape() const override
			{
				return Standard_True;
			}

			Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

#endif // !_StbGMaker_TankCreator_Shape_Header
