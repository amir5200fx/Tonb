#include <Marine_Shape.hxx>

tnbLib::Marine_Shape::Marine_Shape
(
	const TopoDS_Shape& theShape
)
	: Marine_CoordinatedEntity(0, "shape")
	, theShape_(theShape)
{}

tnbLib::Marine_Shape::Marine_Shape
(
	const Standard_Integer theIndex,
	const TopoDS_Shape& theShape
)
	: Marine_CoordinatedEntity(theIndex, "shape")
	, theShape_(theShape)
{}

tnbLib::Marine_Shape::Marine_Shape
(
	const Standard_Integer theIndex,
	const word& theName,
	const TopoDS_Shape& theShape
)
	: Marine_CoordinatedEntity(theIndex, theName)
	, theShape_(theShape)
{}