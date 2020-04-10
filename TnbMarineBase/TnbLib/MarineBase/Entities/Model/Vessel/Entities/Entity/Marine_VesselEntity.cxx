#include <Marine_VesselEntity.hxx>

tnbLib::Marine_VesselEntity::Marine_VesselEntity
(
	const TopoDS_Shape & theShape
)
	: theShape_(theShape)
{
}

tnbLib::Marine_VesselEntity::Marine_VesselEntity
(
	const Standard_Integer theIndex,
	const TopoDS_Shape & theShape
)
	: Marine_Entity(theIndex)
	, theShape_(theShape)
{
}

tnbLib::Marine_VesselEntity::Marine_VesselEntity
(
	const Standard_Integer theIndex,
	const word & theName,
	const TopoDS_Shape & theShape
)
	: Marine_Entity(theIndex, theName)
	, theShape_(theShape)
{
}