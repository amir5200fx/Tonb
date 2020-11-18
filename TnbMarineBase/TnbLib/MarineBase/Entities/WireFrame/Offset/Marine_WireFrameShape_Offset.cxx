#include <Marine_WireFrameShape_Offset.hxx>

tnbLib::marineLib::WireFrameShape_Offset::WireFrameShape_Offset
(
	const Standard_Integer theIndex
)
	: Marine_WireFrameShape(theIndex)
{
	// empty body
}

tnbLib::marineLib::WireFrameShape_Offset::WireFrameShape_Offset
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: Marine_WireFrameShape(theIndex, theName)
{
	// empty body
}