#pragma once
#ifndef _Marine_Shape_Header
#define _Marine_Shape_Header

#include <Marine_CoordinatedEntity.hxx>
#include <Marine_ShapeType.hxx>
#include <Marine_Module.hxx>

#include <TopoDS_Shape.hxx>

namespace tnbLib
{

	class Marine_Shape
		: public Marine_CoordinatedEntity
	{

		/*Private Data*/

		TopoDS_Shape theShape_;


		/*private functions and operators*/

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);


		auto& ChangeShape()
		{
			return theShape_;
		}

	protected:

		Marine_Shape()
		{}

		TnbMarine_EXPORT Marine_Shape(const TopoDS_Shape& theShape);

		TnbMarine_EXPORT Marine_Shape
		(
			const Standard_Integer theIndex,
			const TopoDS_Shape& theShape
		);

		TnbMarine_EXPORT Marine_Shape
		(
			const Standard_Integer theIndex,
			const word& theName,
			const TopoDS_Shape& theShape
		);

	public:

		const auto& Shape() const
		{
			return theShape_;
		}

		virtual Marine_ShapeType Type() const = 0;

		virtual Standard_Boolean IsHull() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsTank() const
		{
			return Standard_False;
		}

		virtual Standard_Boolean IsSail() const
		{
			return Standard_False;
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Marine_Shape);

#endif // !_Marine_Shape_Header
