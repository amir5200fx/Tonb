#include <Marine_WireFrameShape_Shape.hxx>

tnbLib::marineLib::WireFrameShape_Shape::WireFrameShape_Shape
(
	const Standard_Integer theIndex
)
	: Marine_WireFrameShape(theIndex)
{
	// empty body
}

tnbLib::marineLib::WireFrameShape_Shape::WireFrameShape_Shape
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_WireFrameShape(theIndex, theName)
{
	// empty body
}