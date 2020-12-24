#pragma once
#ifndef _Marine_Shape_Sail_Header
#define _Marine_Shape_Sail_Header

#include <Marine_Shape.hxx>

namespace tnbLib
{

	namespace marineLib
	{

		class Shape_Sail
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

			Shape_Sail()
			{}

		public:

			//- constructors


			TnbMarine_EXPORT explicit Shape_Sail(const TopoDS_Shape& theShape);

			TnbMarine_EXPORT Shape_Sail
			(
				const Standard_Integer theIndex,
				const TopoDS_Shape& theShape
			);

			TnbMarine_EXPORT Shape_Sail
			(
				const Standard_Integer theIndex,
				const word& theName,
				const TopoDS_Shape& theShape
			);


			//- public functions and operators

			Marine_ShapeType Type() const override
			{
				return Marine_ShapeType::sail;
			}

			Standard_Boolean IsSail() const override
			{
				return Standard_True;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Shape_Sail);

#endif // !_Marine_Shape_Sail_Header
