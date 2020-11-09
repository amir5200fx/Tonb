#pragma once
#ifndef _StbGMaker_GeometricSailCreator_Plane_Header
#define _StbGMaker_GeometricSailCreator_Plane_Header

#include <StbGMaker_GeometricSailCreator.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	namespace stbGmakerLib
	{

		class GeometricSailCreator_Plane
			: public StbGMaker_GeometricSailCreator
		{

			/*Private Data*/

			std::shared_ptr<Cad2d_Plane> thePlane_;

			Standard_Real theZbar_;


			DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

			GeometricSailCreator_Plane()
			{}

		public:

			GeometricSailCreator_Plane
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			GeometricSailCreator_Plane
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);

			GeometricSailCreator_Plane
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			GeometricSailCreator_Plane
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);

			GeometricSailCreator_Plane
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			GeometricSailCreator_Plane
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);


			auto zBar() const
			{
				return theZbar_;
			}

			const auto& Plane() const
			{
				return thePlane_;
			}

			stbGmakerLib::sailCreatotType Type() const override;

			void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

#endif // !_StbGMaker_GeometricSailCreator_Plane_Header
