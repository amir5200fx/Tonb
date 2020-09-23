#pragma once
#ifndef _StbGMaker_GeometricSailCreator_noShape_Header
#define _StbGMaker_GeometricSailCreator_noShape_Header

#include <StbGMaker_GeometricSailCreator.hxx>
#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class GeometricSailCreator_noShape
			: public StbGMaker_GeometricSailCreator
			, public StbGMaker_Alg
		{

			/*Private Data*/

		public:

			GeometricSailCreator_noShape()
			{}

			GeometricSailCreator_noShape
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

			Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			stbGmakerLib::sailCreatotType Type() const override;

			void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

#endif // !_StbGMaker_GeometricSailCreator_noShape_Header
