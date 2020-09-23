#pragma once
#ifndef _StbGMaker_HullCreator_Shape_Header
#define _StbGMaker_HullCreator_Shape_Header

#include <StbGMaker_HullCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class HullCreator_Shape
			: public StbGMaker_HullCreator
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Shape_Hull>
				theHull_;

		public:

			HullCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Hull>& theHull
			);

			HullCreator_Shape
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<marineLib::Shape_Hull>& theHull
			);

			Standard_Boolean HasShape() const override
			{
				return Standard_True;
			}

			const auto& Shape() const
			{
				return theHull_;
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

#endif // !_StbGMaker_HullCreator_Shape_Header
