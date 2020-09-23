#pragma once
#ifndef _StbGMaker_HullCreator_noShape_Header
#define _StbGMaker_HullCreator_noShape_Header

#include <StbGMaker_HullCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class HullCreator_noShape
			: public StbGMaker_HullCreator
		{

			/*Private Data*/

		public:

			HullCreator_noShape();

			HullCreator_noShape
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			Standard_Boolean HasShape() const override
			{
				return Standard_False;
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

#endif // !_StbGMaker_HullCreator_noShape_Header
