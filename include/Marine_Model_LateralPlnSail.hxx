#pragma once
#ifndef _Marine_Model_LateralPlnSail_Header
#define _Marine_Model_LateralPlnSail_Header

#include <Marine_PlnSailModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	namespace marineLib
	{

		class Model_LateralPlnSail
			: public Marine_PlnSailModel
		{

			/*Private Data*/

			std::shared_ptr<Cad2d_Plane> thePlane_;

			Standard_Real theZbar_;

		public:

			Model_LateralPlnSail
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			Model_LateralPlnSail
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);

			Model_LateralPlnSail
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			Model_LateralPlnSail
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);

			Model_LateralPlnSail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<Cad2d_Plane>& thePlane,
				Standard_Real theZbar
			);

			Model_LateralPlnSail
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<Cad2d_Plane>&& thePlane,
				Standard_Real theZbar
			);


			const auto& Plane() const
			{
				return thePlane_;
			}

			auto zBar() const
			{
				return theZbar_;
			}

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::lateral_plane;
			}

			Standard_Boolean IsTwoDimApprox() const
			{
				return Standard_True;
			}
		};
	}
}

#endif // !_Marine_Model_LateralPlnSail_Header
