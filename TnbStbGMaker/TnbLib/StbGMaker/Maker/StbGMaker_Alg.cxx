#include <StbGMaker_Alg.hxx>

#include <Entity3d_Polygon.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_xDistb.hxx>
#include <Cad2d_Modeler.hxx>
#include <Cad_Tools.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Ring.hxx>
#include <Marine_SectTools.hxx>
#include <StbGMaker_WP.hxx>
#include <StbGMaker_Edge.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#ifdef DebugInfo
#undef DebugInfo
#endif

#include <Geom_Plane.hxx>

void tnbLib::StbGMaker_Alg::ImportWP
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<StbGMaker_WP>&& theWP
)
{
	auto paired = std::make_pair(theIndex, std::move(theWP));
	auto insert = theWorkingPlanes_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn("void tnbLib::StbGMaker_Alg::ImportWP(Args...)")
			<< "duplicate data: " << theIndex << endl
			<< abort(FatalError);
	}
}

std::shared_ptr<tnbLib::StbGMaker_WP>
tnbLib::StbGMaker_Alg::RemoveWP
(
	const Standard_Integer theIndex
)
{
	auto iter = theWorkingPlanes_.find(theIndex);
	if (iter IS_EQUAL theWorkingPlanes_.end())
	{
		FatalErrorIn("std::shared_ptr<tnbLib::StbGMaker_WP> tnbLib::StbGMaker_Alg::RemoveWP(Args...)")
			<< "the wp is not int the tree: " << theIndex << endl
			<< abort(FatalError);
	}

	auto item = std::move(iter->second);
	theWorkingPlanes_.erase(iter);

	return std::move(item);
}

Standard_Integer
tnbLib::StbGMaker_Alg::AddWP
(
	const std::shared_ptr<StbGMaker_WP>&& theWp
)
{
	theWp->Index() = WpCounter().RetrieveIndex();
	theWp->Name() = "wp. nb. " + theWp->Index();

	ImportWP(theWp->Index(), std::move(theWp));
	return theWp->Index();
}

#include <gp_Pln.hxx>
#include <GeomAPI_IntSS.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopExp_Explorer.hxx>

Standard_Integer
tnbLib::StbGMaker_Alg::CreateWpFromShape
(
	const TopoDS_Shape & theShape,
	const Standard_Real x,
	const Marine_SectionType t
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
		return CreateWorkingPlane(x);
	}

	auto tedges = Cad_Tools::RetrieveEdges(alg.Shape());
	auto curves = Cad_Tools::RetrieveParaCurves(tedges, ax);
	auto t_curves = Marine_SectTools::CurveCreator(curves, t);
	auto edges = Pln_Tools::RetrieveEdges(t_curves);

	std::vector<std::shared_ptr<Pln_Edge>> edges3d;
	edges3d.reserve(edges.size());
	for (auto& x : edges)
	{
		if (x->IsRing())
		{
			auto ring = std::dynamic_pointer_cast<Pln_Ring>(x);
			Debug_Null_Pointer(ring);

			auto edge = std::make_shared<StbGMaker_Edge<Pln_Ring>>(std::move(*ring));
			Debug_Null_Pointer(edge);

			edges3d.push_back(std::move(edge));
		}
		else
		{
			auto edge = std::make_shared<StbGMaker_Edge<Pln_Edge>>(std::move(*x));
			Debug_Null_Pointer(edge);

			edges3d.push_back(std::move(edge));
		}
		
	}

	/*auto geoInfo = std::make_shared<Geo_ApprxCurve_Info>();
	Debug_Null_Pointer(geoInfo);

	Geom_Plane plane3d(plane);
	for (const auto& x : edges3d)
	{
		Debug_Null_Pointer(x);
		x->Approx(geoInfo);

		auto x3 = std::dynamic_pointer_cast<StbGMaker_Edge>(x);
		Debug_Null_Pointer(x3);

		auto poly = std::make_shared<Entity3d_Polygon>();
		auto& pts = poly->Points();

		Debug_Null_Pointer(x->Mesh());
		const auto& mesh = x->Mesh();

		pts.reserve(mesh->NbPoints());
		for (const auto& pt : mesh->Points())
		{
			auto pt3 = plane3d.Value(pt.X(), pt.Y());
			pts.push_back(std::move(pt3));
		}

		x3->SetMesh3d(std::move(poly));
	}*/

	//auto wp = std::make_shared<StbGMaker_WP>(x);
	auto wp = MakeWP(x);
	Debug_Null_Pointer(wp);

	const auto& md = wp->Modify();
	md->Import(edges3d);

	return AddWP(std::move(wp));
}

std::shared_ptr<tnbLib::Entity3d_Chain> 
tnbLib::StbGMaker_Alg::Mesh
(
	const Standard_Integer theIndex
) const
{
	auto wp = SelectWP(theIndex);
	Debug_Null_Pointer(wp);

	auto mesh = wp->MakeMesh();
	return std::move(mesh);
}

std::vector<std::shared_ptr<tnbLib::Entity3d_Chain>> tnbLib::StbGMaker_Alg::Mesh() const
{
	return std::vector<std::shared_ptr<Entity3d_Chain>>();
}

std::shared_ptr<tnbLib::StbGMaker_WP> 
tnbLib::StbGMaker_Alg::SelectWP
(
	const Standard_Integer theIndex
) const
{
	auto iter = theWorkingPlanes_.find(theIndex);
	if (iter IS_EQUAL theWorkingPlanes_.end())
	{
		FatalErrorIn("std::shared_ptr<tnbLib::StbGMaker_WP> tnbLib::StbGMaker_Alg::RemoveWP(Args...)")
			<< "the wp is not int the tree: " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::vector<std::shared_ptr<tnbLib::StbGMaker_WP>> 
tnbLib::StbGMaker_Alg::RetrieveWPs() const
{
	std::vector<std::shared_ptr<StbGMaker_WP>> WPs;
	RetrieveWPsTo(WPs);
	return std::move(WPs);
}

Standard_Integer 
tnbLib::StbGMaker_Alg::CreateWorkingPlane
(
	const Standard_Real x
)
{
	//auto wp = std::make_shared<StbGMaker_WP>(x);
	auto wp = MakeWP(x);
	Debug_Null_Pointer(wp);

	return AddWP(std::move(wp));
}

#include <algorithm>

namespace tnbLib
{
	static bool SortFunc
	(
		const std::shared_ptr<StbGMaker_WP>& theWp0, 
		const std::shared_ptr<StbGMaker_WP>& theWp1
	)
	{
		Debug_Null_Pointer(theWp0);
		Debug_Null_Pointer(theWp1);

		return theWp0->X() < theWp1->X();
	}
}

void tnbLib::StbGMaker_Alg::CreateWorkingPlanes
(
	const Geo_xDistb & theX
)
{
	for (const auto x : theX.Values())
	{
		CreateWorkingPlane(x);
	}
}

void tnbLib::StbGMaker_Alg::RetrieveWPsTo
(
	std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs
) const
{
	theWPs.reserve(theWorkingPlanes_.size());
	for (const auto& x : theWorkingPlanes_)
	{
		Debug_Null_Pointer(x.second);
		theWPs.push_back(x.second);
	}
}

void tnbLib::StbGMaker_Alg::SortWPs
(
	std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs
)
{
	std::sort(theWPs.begin(), theWPs.end(), &SortFunc);
}

void tnbLib::StbGMaker_Alg::CheckSort
(
	const std::vector<std::shared_ptr<StbGMaker_WP>>& theWPs, 
	const char * theFunName
)
{
	auto x0 = RealFirst();
	for (const auto& x : theWPs)
	{
		Debug_Null_Pointer(x);
		if (x->X() < x0)
		{
			FatalErrorIn(theFunName)
				<< "the vector is not sorted!" << endl
				<< abort(FatalError);
		}
		x0 = x->X();
	}
}