#include <Marine_Shape_Sail.hxx>

tnbLib::marineLib::Shape_Sail::Shape_Sail
(
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theShape)
{
	// empty body
}

tnbLib::marineLib::Shape_Sail::Shape_Sail
(
	const Standard_Integer theIndex, 
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theShape)
{
	// empty body
}

tnbLib::marineLib::Shape_Sail::Shape_Sail
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theName, theShape)
{
	// empty body
}