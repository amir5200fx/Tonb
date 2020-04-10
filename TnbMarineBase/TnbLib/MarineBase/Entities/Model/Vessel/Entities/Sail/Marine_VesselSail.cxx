#include <Marine_VesselSail.hxx>

tnbLib::Marine_VesselSail::Marine_VesselSail
(
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theShape)
{
}

tnbLib::Marine_VesselSail::Marine_VesselSail
(
	const Standard_Integer theIndex,
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theShape)
{
}

tnbLib::Marine_VesselSail::Marine_VesselSail
(
	const Standard_Integer theIndex,
	const word & theName,
	const TopoDS_Shape & theShape
)
	: Marine_VesselEntity(theIndex, theName, theShape)
{
}