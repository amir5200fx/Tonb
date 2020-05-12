#include <ShipModeler_Basic_SailMaker.hxx>

#include <Geo_xDistb.hxx>
#include <Cad2d_Modeler.hxx>
#include <Pln_Tools.hxx>
#include <Cad_Tools.hxx>
#include <Marine_VesselSail.hxx>
#include <ShipModeler_Basic_WPlane.hxx>

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

#include <vector>

void tnbLib::shipModelerLib::Basic_SailMaker::ImportSail
(
	const Marine_VesselSail & theSail,
	const Geo_xDistb & theX
)
{
	for (const auto x : theX.Values())
	{
		CreatePlane(theSail, x);
	}
}

void tnbLib::shipModelerLib::Basic_SailMaker::CreatePlane
(
	const Marine_VesselSail & theSail,
	const Standard_Real x
)
{
	CreatePlane(theSail.Shape(), x);
}