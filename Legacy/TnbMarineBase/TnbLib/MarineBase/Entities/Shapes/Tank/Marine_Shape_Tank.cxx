#include <Marine_Shape_Tank.hxx>

tnbLib::marineLib::Shape_Tank::Shape_Tank
(
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theShape)
{
	// empty body
}

tnbLib::marineLib::Shape_Tank::Shape_Tank
(
	const Standard_Integer theIndex, 
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theShape)
{
	// empty body
}

tnbLib::marineLib::Shape_Tank::Shape_Tank
(
	const Standard_Integer theIndex, 
	const word & theName,
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theName, theShape)
{
	// empty body
}