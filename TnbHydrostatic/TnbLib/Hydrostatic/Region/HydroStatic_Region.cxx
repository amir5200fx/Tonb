#include <HydroStatic_Region.hxx>

#include <Cad_Tools.hxx>
#include <HydroStatic_Boundary.hxx>
#include <HydroStatic_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

tnbLib::HydroStatic_Region::HydroStatic_Region()
{
}

tnbLib::HydroStatic_Region::HydroStatic_Region
(
	const Standard_Integer theIndex
)
	: Marine_Region(theIndex)
{
}

tnbLib::HydroStatic_Region::HydroStatic_Region
(
	const Standard_Integer theIndex,
	const word & theName
)
	: Marine_Region(theIndex, theName)
{
}

//void tnbLib::HydroStatic_Region::SetBoundaries()
//{
//	
//	auto farBoundaries = RetrieveFarBoundaries();
//	auto hullBoundaries = RetrieveHullBoundaries();
//	auto sailBoundaries = RetrieveSailBoundaries();
//	auto tankBoundaries = RetrieveTankBoundaries();
//
//	auto farSurfaces = HydroStatic_Tools::RetrieveSurfaces(farBoundaries);
//	auto hullSurfaces = HydroStatic_Tools::RetrieveSurfaces(hullBoundaries);
//	auto sailSurfaces = HydroStatic_Tools::RetrieveSurfaces(sailBoundaries);
//	auto tankSurfaces = HydroStatic_Tools::RetrieveSurfaces(tankBoundaries);
//
//	auto farShells = Cad_Tools::TrackShells(farSurfaces);
//
//	if()
//	
//	auto hullShells = Cad_Tools::TrackShells(hullSurfaces);
//
//	auto sailShells = Cad_Tools::TrackShells(sailSurfaces);
//
//	auto tankShells = Cad_Tools::TrackShells(tankSurfaces);
//
//
//}