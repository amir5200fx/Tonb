#include <ShipModeler_Basic_TankMaker.hxx>

#include <Geo_xDistb.hxx>
#include <Marine_VesselTank.hxx>

void tnbLib::shipModelerLib::Basic_TankMaker::ImportHull
(
	const Marine_VesselTank & theTank,
	const Geo_xDistb & theX
)
{
	for (const auto x : theX.Values())
	{
		CreatePlane(theTank, x);
	}
}

void tnbLib::shipModelerLib::Basic_TankMaker::CreatePlane
(
	const Marine_VesselTank & theTank, 
	const Standard_Real theX
)
{
	CreatePlane(theTank.Shape(), theX);
}