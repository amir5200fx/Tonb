#include <ShipModeler_Basic_HullMaker.hxx>

#include <Geo_xDistb.hxx>
#include <Cad2d_Modeler.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_VesselHull.hxx>
#include <ShipModeler_Basic_WPlane.hxx>

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

#include <vector>

void tnbLib::shipModelerLib::Basic_HullMaker::ImportHull
(
	const Marine_VesselHull& theHull, 
	const Geo_xDistb & theX
)
{
	for (const auto x : theX.Values())
	{
		CreatePlane(theHull, x);
	}
}

void tnbLib::shipModelerLib::Basic_HullMaker::CreatePlane
(
	const Marine_VesselHull& theHull, 
	const Standard_Real theX
)
{
	Basic_Maker::CreatePlane(theHull.Shape(), theX);
}
