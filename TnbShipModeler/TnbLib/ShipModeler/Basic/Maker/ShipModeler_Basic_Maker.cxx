#include <ShipModeler_Basic_Maker.hxx>

#include <Cad_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Cad2d_Modeler.hxx>
#include <ShipModeler_Basic_WPlane.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

#include <vector>

std::shared_ptr<tnbLib::shipModelerLib::Basic_WPlane> 
tnbLib::shipModelerLib::Basic_Maker::RemoveWorkingPlane
(
	const Standard_Integer theIndex
)
{
	auto iter = theWorkingPlanes_.find(theIndex);
	if (iter NOT_EQUAL theWorkingPlanes_.end())
	{
		FatalErrorIn("std::shared_ptr<Basic_WPlane> RemoveWorkingPlane(const Standard_Integer)")
			<< "the working plane not found!" << endl
			<< abort(FatalError);
	}
	auto p = iter->second;
	theWorkingPlanes_.erase(iter);

	Counter().ReturnToCounter(p->Index());

	return std::move(p);
}

void tnbLib::shipModelerLib::Basic_Maker::ImportWorkingPlane
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Basic_WPlane>&& thePlane
)
{
	auto p = std::move(thePlane);
	Debug_Null_Pointer(p);

	p->SetIndex(Counter().RetrieveIndex());
	p->SetName("wp. " + std::to_string(p->Index()));

	auto insert = theWorkingPlanes_.insert(std::make_pair(theIndex, std::move(thePlane)));
	if (NOT insert.second)
	{
		FatalErrorIn("void ImportWorkingPlane(const Standard_Integer, const std::shared_ptr<Basic_WPlane>&)")
			<< "duplicate data" << endl
			<< abort(FatalError);
	}
}

void tnbLib::shipModelerLib::Basic_Maker::CreatePlane
(
	const TopoDS_Shape & theShape, 
	const Standard_Real x
)
{
	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init2(theShape);
	alg.Approximation(Standard_True);

	const auto& ax2 = Ax2();

	gp_Ax2 syst0(ax2.Location(), ax2.XDirection(), ax2.YDirection());
	const auto x0 = syst0.Location().Z();
	const auto ax = syst0.Translated(gp_Vec(x - x0, 0, 0));

	gp_Pln plane(ax);

	alg.Init1(plane);
	alg.Build();

	if (alg.Shape().IsNull())
	{
		CreateWorkingPlane(x);
		return;
	}

	auto tedges = Cad_Tools::RetrieveEdges(alg.Shape());
	auto curves = Cad_Tools::RetrieveParaCurves(tedges, ax);

	auto edges = Pln_Tools::RetrieveEdges(curves);

	auto wp = std::make_shared<shipModelerLib::Basic_WPlane>(x);
	Debug_Null_Pointer(wp);

	const auto& md = wp->Modify();
	md->Import(edges);

	ImportWorkingPlane(wp->Index(), std::move(wp));
}

void tnbLib::shipModelerLib::Basic_Maker::CreateWorkingPlane
(
	const Standard_Real x
)
{
	auto wp = std::make_shared<shipModelerLib::Basic_WPlane>(x);
	Debug_Null_Pointer(wp);

	ImportWorkingPlane(wp->Index(), std::move(wp));
}