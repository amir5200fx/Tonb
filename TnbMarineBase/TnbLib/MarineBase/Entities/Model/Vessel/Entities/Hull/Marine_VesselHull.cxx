#include <Marine_VesselHull.hxx>

tnbLib::Marine_VesselHull::Marine_VesselHull
(
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theShape)
{
}

tnbLib::Marine_VesselHull::Marine_VesselHull
(
	const Standard_Integer theIndex,
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theShape)
{
}

tnbLib::Marine_VesselHull::Marine_VesselHull
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theName, theShape)
{
}