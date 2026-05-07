#pragma once
#ifndef _Marine_Model_LateralPlnSail_Header
#define _Marine_Model_LateralPlnSail_Header

#include <Marine_Model_PlnSail.hxx>
#include <Entity2d_TriangulationFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Marine_Model_SailTools;

	namespace marineLib
	{

		class Model_LateralPlnSail
			: public Model_PlnSail
		{

			friend Marine_Model_SailTools;

			/*Private Data*/

			std::shared_ptr<Cad2d_Plane> thePlane_;

			std::shared_ptr<Entity2d_Triangulation> theTriangulation_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbMarine_EXPORT);


			auto& TriangulationRef()
			{
				return theTriangulation_;
			}

			void SetTriangulation(std::shared_ptr<Entity2d_Triangulation>&& t)
			{
				theTriangulation_ = std::move(t);
			}


		protected:

			//- default constructor

			Model_LateralPlnSail()
			{}

		public:


			//- constructors

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<Cad2d_Plane>& thePlane
			);

			TnbMarine_EXPORT Model_LateralPlnSail
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<Cad2d_Plane>&& thePlane
			);


			//- public functions and operators

			const auto& Plane() const
			{
				return thePlane_;
			}

			auto HasTriangulation() const
			{
				return (Standard_Boolean)theTriangulation_;
			}

			const auto& Triangulation() const
			{
				return theTriangulation_;
			}

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::lateral_plane;
			}

			Standard_Boolean IsTwoDimApprox() const
			{
				return Standard_True;
			}

			//- static functions

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_LateralPlnSail);

#endif // !_Marine_Model_LateralPlnSail_Header
