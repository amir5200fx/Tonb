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

			Standard_Boolean IsSymmetric_;

			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_Shape>(*this);
				ar & IsSymmetric_;
			}

		protected:

			Shape_Hull()
				: IsSymmetric_(Standard_False)
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

			auto IsSymmetric() const
			{
				return IsSymmetric_;
			}

			void SetSymmetric(const Standard_Boolean symm)
			{
				IsSymmetric_ = symm;
			}
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::Shape_Hull);

#endif // !_Marine_Shape_Hull_Header
