#pragma once
#ifndef _StbGMaker_GeometricSailCreator_Shape_Header
#define _StbGMaker_GeometricSailCreator_Shape_Header

#include <StbGMaker_GeometricSailCreator.hxx>
#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class GeometricSailCreator_Shape
			: public StbGMaker_GeometricSailCreator
			, public StbGMaker_Alg
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Shape_Sail>
				theShape_;

			DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

			GeometricSailCreator_Shape()
			{}

		public:


			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const word& theName,
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);


			const auto& Shape() const
			{
				return theShape_;
			}

			TnbStbGMaker_EXPORT Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			TnbStbGMaker_EXPORT stbGmakerLib::sailCreatotType Type() const override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::GeometricSailCreator_Shape);

#endif // !_StbGMaker_GeometricSailCreator_Shape_Header
