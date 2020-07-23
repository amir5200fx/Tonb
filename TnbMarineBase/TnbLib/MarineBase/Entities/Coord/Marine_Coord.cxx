#include <Marine_Coord.hxx>

tnbLib::Marine_Coord::Marine_Coord
(
	const Pnt3d & theCoord
)
	: Marine_Entity(0, "coordinate")
	, theCoord_(theCoord)
{
	// empty body
}

tnbLib::Marine_Coord::Marine_Coord
(
	Pnt3d && theCoord
)
	: Marine_Entity(0, "coordinate")
	, theCoord_(std::move(theCoord))
{
	// empty body
}

tnbLib::Marine_Coord::Marine_Coord
(
	const Standard_Integer theIndex,
	const word & theName,
	const Pnt3d & theCoord
)
	: Marine_Entity(theIndex, theName)
	, theCoord_(theCoord)
{
	// empty body
}

tnbLib::Marine_Coord::Marine_Coord
(
	const Standard_Integer theIndex,
	const word & theName, 
	Pnt3d && theCoord
)
	: Marine_Entity(theIndex, theName)
	, theCoord_(std::move(theCoord))
{
	// empty body
}