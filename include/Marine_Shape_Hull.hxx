#pragma once
#ifndef _Marine_Shape_Hull_Header
#define _Marine_Shape_Hull_Header

#include <Marine_Shape.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Shape_Hull
			: public Marine_Shape
		{

			/*Private Data*/


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_Shape>(*this);
			}

		protected:

			Shape_Hull()
			{}

		public:

			//- constructors


			TnbMarine_EXPORT explicit Shape_Hull(const TopoDS_Shape& theShape);

			TnbMarine_EXPORT Shape_Hull
			(
				const Standard_Integer theIndex,
				const TopoDS_Shape& theShape
			);

			TnbMarine_EXPORT Shape_Hull
			(
				const Standard_Integer theIndex,
				const word& theName,
				const TopoDS_Shape& theShape
			);


			//- public functions and operators

			Marine_ShapeType Type() const override
			{
				return Marine_ShapeType::hull;
			}

			Standard_Boolean IsHull() const override
			{
				return Standard_True;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Shape_Hull);

#endif // !_Marine_Shape_Hull_Header
