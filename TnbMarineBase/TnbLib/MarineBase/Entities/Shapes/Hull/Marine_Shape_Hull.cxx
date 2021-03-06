#include <Marine_Shape_Hull.hxx>

tnbLib::marineLib::Shape_Hull::Shape_Hull
(
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theShape)
	, IsSymmetric_(Standard_False)
{
	// empty body
}

tnbLib::marineLib::Shape_Hull::Shape_Hull
(
	const Standard_Integer theIndex,
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theShape)
	, IsSymmetric_(Standard_False)
{
	// empty body
}

tnbLib::marineLib::Shape_Hull::Shape_Hull
(
	const Standard_Integer theIndex,
	const word & theName,
	const TopoDS_Shape & theShape
)
	: Marine_Shape(theIndex, theName, theShape)
	, IsSymmetric_(Standard_False)
{
	// empty body
}

