#pragma once
#ifndef _Marine_Model_SurfaceSail_Header
#define _Marine_Model_SurfaceSail_Header

#include <Marine_Model_PlnSail.hxx>
#include <Entity2d_TriangulationFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad_Shape;

	namespace marineLib
	{

		class Model_SurfaceSail
			: public Model_PlnSail
		{

			/*Private Data*/

			std::shared_ptr<Cad_Shape> theShape_;


			TNB_SERIALIZATION(TnbMarine_EXPORT);

		protected:

			//- default constructor

			Model_SurfaceSail()
			{}

		public:


			//- constructors

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const std::shared_ptr<Cad_Shape>& theShape
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				std::shared_ptr<Cad_Shape>&& theShape
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Cad_Shape>& theShape
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Cad_Shape>&& theShape
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const std::shared_ptr<Cad_Shape>& theShape
			);

			TnbMarine_EXPORT Model_SurfaceSail
			(
				const Standard_Integer theIndex,
				const word& theName, 
				std::shared_ptr<Cad_Shape>&& theShape
			);


			//- public functions and operators

			Marine_SailModelType SailType() const override
			{
				return Marine_SailModelType::surface;
			}

			const auto& Shape() const
			{
				return theShape_;
			}


			//- static functions

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Model_SurfaceSail);

#endif // !_Marine_Model_SurfaceSail_Header
