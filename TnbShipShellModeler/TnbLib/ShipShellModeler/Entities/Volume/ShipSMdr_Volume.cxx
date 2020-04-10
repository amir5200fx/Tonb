#include <ShipSMdr_Volume.hxx>

tnbLib::ShipSMdr_Volume::ShipSMdr_Volume()
{
}

tnbLib::ShipSMdr_Volume::ShipSMdr_Volume
(
	const Standard_Integer theIndex
)
	: ShipSMdr_Entity(theIndex)
{
}

tnbLib::ShipSMdr_Volume::ShipSMdr_Volume
(
	const Standard_Integer theIndex, 
	const word & theName
)
	: ShipSMdr_Entity(theIndex, theName)
{
}