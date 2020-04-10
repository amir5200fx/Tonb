#include <Marine_VesselTank.hxx>

tnbLib::Marine_VesselTank::Marine_VesselTank
(
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theShape)
{
}

tnbLib::Marine_VesselTank::Marine_VesselTank
(
	const Standard_Integer theIndex,
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theShape)
{
}

tnbLib::Marine_VesselTank::Marine_VesselTank
(
	const Standard_Integer theIndex,
	const word & theName, 
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theName, theShape)
{
}