#include <ShipModeler_Basic_Tools.hxx>

#include <Entity3d_Box.hxx>
#include <Geo_UniDistb.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Marine_Body.hxx>
#include <Marine_TankBody.hxx>
#include <ShipModeler_Basic_WPlane.hxx>
#include <ShipModeler_Basic_Tank.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Bnd_Box.hxx>
#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

std::shared_ptr<tnbLib::Geo_xDistb>
tnbLib::shipModelerLib::Basic_Tools::UniformDistribution
(
	const TopoDS_Shape & theShape,
	const Standard_Integer nbSegments
)
{
	Entity3d_Box b = Cad_Tools::BoundingBox(Cad_Tools::BoundingBox(theShape));
	const auto[dx, dy, dz] = b.Length();

	const auto d = 1.0e-6*dx;
	const auto x0 = b.P0().X() + d;
	const auto x1 = b.P1().X() - d;

	auto distb = UniformDistribution(x0, x1, nbSegments);
	return std::move(distb);
}

std::shared_ptr<tnbLib::Geo_xDistb> 
tnbLib::shipModelerLib::Basic_Tools::UniformDistribution
(
	const Standard_Real x0, 
	const Standard_Real x1,
	const Standard_Integer nbSegments
)
{
	if (nbSegments < 5)
	{
		FatalErrorIn("std::shared_ptr<Geo_xDistb> UniformDistribution(const Standard_Real, const Standard_Real, const Standard_Integer)")
			<< "the min. nb. of segments must be greater than 5" << endl
			<< abort(FatalError);
	}

	auto distb = std::make_shared<Geo_UniDistb>(nbSegments);
	Debug_Null_Pointer(distb);

	Debug_If_Condition(x1 <= x0);

	distb->SetLower(x0);
	distb->SetUpper(x1);

	distb->Perform();
	Debug_If_Condition_Message(NOT distb->IsDone(), "the algorithm is not performed!");

	return std::move(distb);
}

std::shared_ptr<tnbLib::shipModelerLib::Basic_WPlane> 
tnbLib::shipModelerLib::Basic_Tools::CreateWorkingPlane
(
	const TopoDS_Shape & theShape, 
	const gp_Ax2& theAx,
	const Standard_Real x
)
{
	BRepAlgoAPI_Section alg;
	alg.ComputePCurveOn1(Standard_True);
	alg.SetRunParallel(Standard_True);
	alg.Init2(theShape);
	alg.Approximation(Standard_True);

	const auto& ax2 = theAx;

	gp_Ax2 syst0(ax2.Location(), ax2.XDirection(), ax2.YDirection());
	const auto x0 = syst0.Location().Z();
	const auto ax = syst0.Translated(gp_Vec(x - x0, 0, 0));

	gp_Pln plane(ax);

	alg.Init1(plane);
	alg.Build();

	if (alg.Shape().IsNull())
	{
		FatalErrorIn("std::shared_ptr<Basic_WPlane> CreateWorkingPlane(const TopoDS_Shape& theShape, const gp_Ax2& theAx, const Standard_Real x)")
			<< "unable to calculate the intersection between the shape and the plane" << endl
			<< abort(FatalError);
	}

	auto tedges = Cad_Tools::RetrieveEdges(alg.Shape());
	auto curves = Cad_Tools::RetrieveParaCurves(tedges, ax);

	auto edges = Pln_Tools::RetrieveEdges(curves);

	auto wp = std::make_shared<shipModelerLib::Basic_WPlane>(x);
	Debug_Null_Pointer(wp);

	const auto& md = wp->Modify();
	md->Import(edges);
	return std::move(wp);
}

std::vector<std::shared_ptr<tnbLib::shipModelerLib::Basic_WPlane>>
tnbLib::shipModelerLib::Basic_Tools::CreateWorkingPlanes
(
	const TopoDS_Shape & theShape,
	const gp_Ax2& theAx,
	const Geo_xDistb & theDistb
)
{
	std::vector<std::shared_ptr<Basic_WPlane>> planes;
	planes.reserve(theDistb.Size());
	for (const auto x : theDistb.Values())
	{
		auto wp = CreateWorkingPlane(theShape, theAx, x);
		Debug_Null_Pointer(wp);

		planes.push_back(std::move(wp));
	}
	return std::move(planes);
}

std::shared_ptr<tnbLib::shipModelerLib::Basic_Tank> 
tnbLib::shipModelerLib::Basic_Tools::CreateTank
(
	const std::vector<std::shared_ptr<Basic_WPlane>>& theShape
)
{
	return std::shared_ptr<Basic_Tank>();
}