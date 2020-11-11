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


			GeometricSailCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			GeometricSailCreator_Shape
			(
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			GeometricSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const word& theName,
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);


			const auto& Shape() const
			{
				return theShape_;
			}

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

#endif // !_StbGMaker_GeometricSailCreator_Shape_Header
