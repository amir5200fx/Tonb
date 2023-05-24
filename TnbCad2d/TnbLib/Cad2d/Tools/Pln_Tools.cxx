#include <Pln_Tools.hxx>

#include <Geo_AdTree.hxx>
#include <Geo_PrTree.hxx>
#include <Geo_CurveIntegrand.hxx>
#include <Geo_CurveIntegrand_Function.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Geo_ItemSort.hxx>
#include <Adt_AvlTree.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Modeler_Corner.hxx>
#include <Cad2d_Modeler_Tools.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Geo_BoxTools.hxx>
#include <NumAlg_AdaptiveInteg.hxx>

#include <gp_Pln.hxx>
#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom_Plane.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dConvert.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <BRep_Tool.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shape.hxx>
#include <Precision.hxx>

Standard_Real 
tnbLib::Pln_Tools::CalcPrecision
(
	const Pln_Vertex & theVtx
)
{
	if (theVtx.IsOrphan())
	{
		return 0;
	}
	if (theVtx.IsRingPoint())
	{
		return 0;
	}
	const auto& coord = theVtx.Coord();
	Standard_Real tol = RealLast();
	for (const auto& x : theVtx.RetrieveEdges())
	{
		auto edge = x.lock();
		Debug_Null_Pointer(edge);

		const auto& curve = edge->Curve();
		auto p0 = curve->FirstCoord();
		auto p1 = curve->LastCoord();

		auto d = std::sqrt(std::min(p0.SquareDistance(coord), p1.SquareDistance(coord)));
		if (d <= tol)
		{
			tol = d;
		}
	}
	return tol;
}

Standard_Boolean 
tnbLib::Pln_Tools::IsBounded
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	return (Standard_Boolean)Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
}

Standard_Boolean 
tnbLib::Pln_Tools::IsManifold
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	auto nodes = RetrieveVertices(theEdges);
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsManifold())
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::Pln_Tools::IsValidToRetrieveWires
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	return IsManifold(theEdges);
}

Standard_Real 
tnbLib::Pln_Tools::Length
(
	const Geom2d_Curve& theCurve,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Geo_CurveIntegrand<Geom2d_Curve> integrand(theCurve);
	Geo_CurveIntegrand_Function<Geom2d_Curve, void, false>
		function(integrand);

	NumAlg_AdaptiveInteg<Geo_CurveIntegrand_Function<Geom2d_Curve, void, false>>
		alg(function, theCurve.FirstParameter(), theCurve.LastParameter(), *theInfo);

	alg.Perform();

	if (NOT alg.IsDone())
	{
		FatalErrorIn("Standard_Real Length(Args...)")
			<< "the integration is not performed!" << endl
			<< abort(FatalError);
	}

	return theInfo->Result();
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Pln_Tools::UniformDiscrete
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Integer nbSeg
)
{
	if (NOT Pln_Tools::IsBounded(theCurve))
	{
		FatalErrorIn("void Pln_CurveTools::UniformDiscrete(Args...)")
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
	const auto du = (theCurve->LastParameter() - theCurve->FirstParameter()) 
		/ (Standard_Real)nbSeg;
	const auto u0 = theCurve->FirstParameter();

	std::vector<Pnt2d> pts;
	pts.reserve(nbSeg + 1);

	for (auto i = 0; i <= nbSeg; i++)
	{
		auto pt = theCurve->Value(u0 + i * du);
		pts.push_back(std::move(pt));
	}

	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::Pln_Tools::UniformDiscrete
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1,
	const Standard_Integer nbSeg
)
{
	const auto du = (theU1 - theU0)
		/ (Standard_Real)nbSeg;
	const auto u0 = theU0;

	std::vector<Pnt2d> pts;
	pts.reserve(nbSeg + 1);

	for (auto i = 0; i <= nbSeg; i++)
	{
		auto pt = theCurve->Value(u0 + i * du);
		pts.push_back(std::move(pt));
	}

	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}

std::shared_ptr<tnbLib::Pln_CmpEdge> 
tnbLib::Pln_Tools::MakeCompoundEdge
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	auto pln = std::make_shared<Pln_CmpEdge>();

	/*if (theEdges.size() IS_EQUAL 1)
	{
		pln->Insert(theEdges[0]);

		return std::move(pln);
	}*/

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		pln->Insert(x);
	}

	/*pln->Insert(theEdges[0]);

	forThose(Index, 1, theEdges.size() - 1)
	{
		if (theEdges[Index]->Vtx0() NOT_EQUAL theEdges[Index - 1]->Vtx1())
		{
			FatalErrorIn("std::shared_ptr<Pln_CmpEdge> MakeCompoundEdge(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)")
				<< "Unable to make compound edge" << endl
				<< abort(FatalError);
		}

		pln->Insert(theEdges[Index]);
	}*/

	return std::move(pln);
}

std::pair<Handle(Geom2d_Curve), Handle(Geom2d_Curve)> 
tnbLib::Pln_Tools::Split
(
	const Standard_Real x, 
	const Handle(Geom2d_Curve)& theCurve
)
{
#ifdef _DEBUG
	if (NOT IsBounded(theCurve))
	{
		FatalErrorIn(FunctionSIG)
			<< "the curve is not bounded!" << endl
			<< abort(FatalError);
	}
#endif // _DEBUG

	const auto fp = theCurve->FirstParameter();
	const auto lp = theCurve->LastParameter();
	if (NOT INSIDE(x, fp, lp))
	{
		FatalErrorIn(FunctionSIG)
			<< "The Parameter is out of valid range: " << x << endl
			<< " - First parameter: " << fp << endl
			<< " - Last Parameter: " << lp << endl
			<< abort(FatalError);
	}
	if (auto trimmed = Handle(Geom2d_TrimmedCurve)::DownCast(theCurve))
	{
		auto geom = trimmed->BasisCurve();
		Debug_Null_Pointer(geom);

		auto c0 = Pln_CurveTools::Trim(geom, fp, x);
		auto c1 = Pln_CurveTools::Trim(geom, x, lp);

		auto t = std::make_pair(std::move(c0), std::move(c1));
		return std::move(t);
	}
	else
	{
		auto c0 = Pln_CurveTools::Trim(theCurve, fp, x);
		auto c1 = Pln_CurveTools::Trim(theCurve, x, lp);

		auto t = std::make_pair(std::move(c0), std::move(c1));
		return std::move(t);
	}
}

std::shared_ptr<tnbLib::Entity2d_Polygon> 
tnbLib::Pln_Tools::MergeApproxWire
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& theCurves,
	const Standard_Real theTol
)
{
	static auto first_point = [](const std::vector<std::shared_ptr<Entity2d_Polygon>>::const_iterator& iter)
	{
		Debug_If_Condition((*iter)->Points().empty());
		return (*iter)->Points().at(0);
	};
	std::vector<Pnt2d> pts;
#ifdef _DEBUG
	if (NOT theCurves.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "the list is empty" << endl
			<< abort(FatalError);
	}
#else
	if (theCurves.empty())
	{
		auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
		return std::move(poly);
	}
#endif // _DEBUG
	auto iter = theCurves.begin();
	pts = (*iter)->Points();
	if (theCurves.size() IS_EQUAL 1)
	{
		auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
		return std::move(poly);
	}
	iter++;
	while (iter NOT_EQUAL theCurves.end())
	{
		const auto& p0 = pts.at(pts.size() - 1);
		const auto p1 = first_point(iter);
		if (p0.Distance(p1) <= theTol)
		{
			auto inner = (*iter)->Points().begin();
			inner++;
			while (inner NOT_EQUAL(*iter)->Points().end())
			{
				pts.push_back(inner->Coord());
				inner++;
			}
		}
		else
		{
			for (const auto& x : (*iter)->Points())
			{
				pts.push_back(x);
			}
		}
		iter++;
	}
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(pts), 0);
	return std::move(poly);
}

namespace tnbLib
{

	inline Standard_Real CalcMaxPrec
	(
		const Pnt2d& theM,
		const Pnt2d& theP0, 
		const Pnt2d& theP1
	)
	{
		const auto dis0 = theM.Distance(theP0);
		const auto dis1 = theM.Distance(theP1);
		return 1.005*MAX(dis0, dis1);
	}
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::MakeWire
(
	const std::shared_ptr<Pln_Ring>& theRing
)
{
	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(1);

	edges.push_back(theRing);

	auto cmpEdge = MakeCompoundEdge(edges);
	Debug_Null_Pointer(cmpEdge);

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	return std::move(wire);
}

std::shared_ptr<tnbLib::Pln_Wire>
tnbLib::Pln_Tools::MakeWire
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
	const Standard_Real theMaxTol
)
{
	if (theCurves.empty())
	{
		FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
			<< "the list of the curves is empty!" << endl
			<< abort(FatalError);
	}
	
	if (theCurves.size() IS_EQUAL 1)
	{
		const auto& c = theCurves[0];
		if (c->FirstCoord().Distance(c->LastCoord()) > theMaxTol)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
				<< "the curve is not formed a wire; max tolerance = " << theMaxTol << endl
				<< abort(FatalError);
		}

		auto v = std::make_shared<Pln_Vertex>(1, c->FirstCoord());
		Debug_Null_Pointer(v);

		auto ring = std::make_shared<Pln_Ring>(v, c);
		Debug_Null_Pointer(ring);

		ring->SetIndex(1);

		auto info = std::make_shared<Geo_ApprxCurve_Info>();
		Debug_Null_Pointer(info);

		auto box = ring->BoundingBox(0);

		info->SetAngle(3.0);
		info->SetApprox(1.0E-3 * box.Diameter());
		info->SetMinSize(1.0E-4 * box.Diameter());

		info->SetMaxNbSubdivision(10);
		info->SetInitNbSubdivision(3);

		info->SetNbSamples(4);

		ring->Approx(info);

		auto wire = MakeWire(ring);

		return std::move(wire);
	}

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	vertices.reserve(theCurves.size());

	auto p0 = theCurves[theCurves.size() - 1]->LastCoord();
	auto p1 = theCurves[0]->FirstCoord();

	if (p0.Distance(p1) > theMaxTol)
	{
		FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
			<< "the curves are not formed a wire; max tolerance = " << theMaxTol << endl
			<< " Distane = " << p0.Distance(p1) << endl
			<< abort(FatalError);
	}

	auto m = MEAN(p0, p1);

	Standard_Integer K = 0;
	auto v = std::make_shared<Pln_Vertex>(++K, m);
	Debug_Null_Pointer(v);

	v->SetPrecision(CalcMaxPrec(m, p0, p1));
	vertices.push_back(std::move(v));

	auto iter = theCurves.begin();

	Debug_Null_Pointer((*iter));
	p0 = (*iter)->LastCoord();

	iter++;

	while (iter NOT_EQUAL theCurves.end())
	{
		Debug_Null_Pointer((*iter));
		p1 = (*iter)->FirstCoord();

		if (p0.Distance(p1) > theMaxTol)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
				<< "the curves are not formed a wire; max tolerance = " << theMaxTol << endl
				<< abort(FatalError);
		}

		m = MEAN(p0, p1);

		auto v = std::make_shared<Pln_Vertex>(++K, m);
		Debug_Null_Pointer(v);

		v->SetPrecision(CalcMaxPrec(m, p0, p1));
		vertices.push_back(std::move(v));

		p0 = (*iter)->LastCoord();

		iter++;
	}

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(theCurves.size());

	K = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		auto i0 = K;
		auto i1 = (K + 1) % theCurves.size();

		const auto& v0 = vertices[i0];
		const auto& v1 = vertices[i1];

		auto edge = std::make_shared<Pln_Segment>(v0, v1, x);
		Debug_Null_Pointer(edge);

		K++;

		edge->SetIndex(K);

		edges.push_back(std::move(edge));
	}

	auto cmpEdge = MakeCompoundEdge(edges);
	Debug_Null_Pointer(cmpEdge);

	auto box = RetrieveBoundingBox(*cmpEdge);

	auto info = std::make_shared<Geo_ApprxCurve_Info>();
	Debug_Null_Pointer(info);

	info->SetAngle(3.0);
	info->SetApprox(1.0E-3 * box.Diameter());
	info->SetMinSize(1.0E-4 * box.Diameter());

	info->SetMaxNbSubdivision(10);
	info->SetInitNbSubdivision(3);

	info->SetNbSamples(4);

	for (const auto& x : cmpEdge->Edges())
	{
		Debug_Null_Pointer(x);
		x->Approx(info);
	}

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	/*for (const auto& x : cmpEdge->Edges())
	{
		Debug_Null_Pointer(x);
		x->ClearMesh();
	}*/

	return std::move(wire);
}

namespace tnbLib
{

	Pnt2d GetCoord
	(
		const Pln_Curve& curve,
		const Standard_Boolean sense,
		const Standard_Integer id
	)
	{
		if (id IS_EQUAL 0)
		{
			if (sense)
			{
				auto pt = curve.FirstCoord();
				return std::move(pt);
			}
			else
			{
				auto pt = curve.LastCoord();
				return std::move(pt);
			}
		}
		else
		{
			if (sense)
			{
				auto pt = curve.LastCoord();
				return std::move(pt);
			}
			else
			{
				auto pt = curve.FirstCoord();
				return std::move(pt);
			}
		}
	}
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::MakeWire
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves, 
	const std::vector<Standard_Boolean>& theSense, 
	const Standard_Real theMaxTol
)
{
	auto info = std::make_shared<Geo_ApprxCurve_Info>();
	Debug_Null_Pointer(info);

	/*info->SetNbSamples(3);
	info->SetAngle(2.5);
	info->SetApprox(1.0E-2);
	info->SetMinSize(1.0e-3);
	info->SetInitNbSubdivision(2);*/

	auto box = BoundingBox(theCurves);

	info->SetAngle(3.0);
	info->SetApprox(1.0E-3 * box.Diameter());
	info->SetMinSize(1.0E-4 * box.Diameter());

	info->SetMaxNbSubdivision(10);
	info->SetInitNbSubdivision(3);

	info->SetNbSamples(4);

	auto wire = MakeWire(theCurves, theSense, info, theMaxTol);
	return std::move(wire);
}

Standard_Boolean 
tnbLib::Pln_Tools::IsOnEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx,
	const std::shared_ptr<Pln_Segment>& theEdge
)
{
	if (theEdge->Vtx0() IS_EQUAL theVtx)
	{
		return Standard_True;
	}	
	if (theEdge->Vtx1() IS_EQUAL theVtx)
	{
		return Standard_True;
	}
	return Standard_False;
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Tools::CommonVertex
(
	const std::shared_ptr<Pln_Segment>& theEdge0,
	const std::shared_ptr<Pln_Segment>& theEdge1
)
{
	Debug_Null_Pointer(theEdge0);
	Debug_Null_Pointer(theEdge1);

	const auto& v0 = theEdge0->Vtx0();
	const auto& v1 = theEdge0->Vtx1();

	if (IsOnEdge(v0, theEdge1))
	{
		return v0;
	}
	if (IsOnEdge(v1, theEdge1))
	{
		return v1;
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::MakeEdge
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto curve = std::make_shared<Pln_Curve>(theCurve);
	Debug_Null_Pointer(curve);

	auto v0 = std::make_shared<Pln_Vertex>(0, curve->FirstCoord());
	auto v1 = std::make_shared<Pln_Vertex>(1, curve->LastCoord());
	Debug_Null_Pointer(v0);
	Debug_Null_Pointer(v1);

	auto edge = std::make_shared<Pln_Segment>(std::move(v0), std::move(v1), std::move(curve));
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::MakeEdge
(
	const std::shared_ptr<Pln_Curve>& theCurve
)
{
	auto curve = theCurve;
	Debug_Null_Pointer(curve);

	auto v0 = std::make_shared<Pln_Vertex>(0, curve->FirstCoord());
	auto v1 = std::make_shared<Pln_Vertex>(1, curve->LastCoord());
	Debug_Null_Pointer(v0);
	Debug_Null_Pointer(v1);

	auto edge = std::make_shared<Pln_Segment>(std::move(v0), std::move(v1), std::move(curve));
	return std::move(edge);
	
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::MakeEdge
(
	std::shared_ptr<Pln_Curve>&& theCurve
)
{
	auto curve = std::move(theCurve);
	Debug_Null_Pointer(curve);

	auto v0 = std::make_shared<Pln_Vertex>(0, curve->FirstCoord());
	auto v1 = std::make_shared<Pln_Vertex>(1, curve->LastCoord());
	Debug_Null_Pointer(v0);
	Debug_Null_Pointer(v1);

	auto edge = std::make_shared<Pln_Segment>(std::move(v0), std::move(v1), std::move(curve));
	return std::move(edge);
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::MakeWire
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const std::vector<Standard_Boolean>& theSense, 
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo, 
	const Standard_Real theMaxTol
)
{
	if (theCurves.empty())
	{
		FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
			<< "the list of the curves is empty!" << endl
			<< abort(FatalError);
	}

	if (NOT theInfo)
	{
		FatalErrorIn(FunctionSIG)
			<< "the approx. curve info is null" << endl
			<< abort(FatalError);
	}

	if (theCurves.size() IS_EQUAL 1)
	{
		const auto& c = theCurves[0];

		auto p0 = c->FirstCoord();
		auto p1 = c->LastCoord();

		auto m = MEAN(p0, p1);

		if (p0.Distance(p1) > theMaxTol)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
				<< "the wire is not formed by the curve; max tolerance = " << theMaxTol << endl
				<< "tol = " << p0.Distance(p1) << endl
				<< abort(FatalError);
		}

		auto v = std::make_shared<Pln_Vertex>(1, m);
		Debug_Null_Pointer(v);

		v->SetPrecision(MAX(m.Distance(p0), m.Distance(p1)));

		auto ring = std::make_shared<Pln_Ring>(v, c, theSense[0]);
		Debug_Null_Pointer(ring);

		ring->SetIndex(1);
		ring->Approx(theInfo);

		v->InsertToEdges(ring->Index(), ring);

		auto wire = MakeWire(ring);

		ring->SetWire(wire);

		return std::move(wire);
	}

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	vertices.reserve(theCurves.size());

	auto p0 = GetCoord(*theCurves[theCurves.size() - 1], theSense[theSense.size() - 1], 1);

	forThose(Index, 0, theCurves.size() - 1)
	{
		auto p1 = GetCoord(*theCurves[Index], theSense[Index], 0);
		if (p0.Distance(p1) > theMaxTol)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
				<< "the wire is not formed by the curves; max tolerance = " << theMaxTol << endl
				<< "tol = " << p0.Distance(p1) << endl
				<< abort(FatalError);
		}

		auto m = MEAN(p0, p1);

		auto v = std::make_shared<Pln_Vertex>(Index + 1, m);
		Debug_Null_Pointer(v);

		v->SetPrecision(MAX(m.Distance(p0), m.Distance(p1)));

		vertices.push_back(std::move(v));

		p0 = GetCoord(*theCurves[Index], theSense[Index], 1);
	}

	auto cmpEdge = std::make_shared<Pln_CmpEdge>();
	Debug_Null_Pointer(cmpEdge);

	auto& edges = cmpEdge->ChangeEdges();
	edges.reserve(theCurves.size());

	Standard_Integer K = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		const auto& v0 = vertices[K];
		const auto& v1 = vertices[(K + 1) % theCurves.size()];

		auto edge = std::make_shared<Pln_Segment>(v0, v1, x, theSense[K]);
		Debug_Null_Pointer(edge);

		edge->SetIndex(++K);
		edge->Approx(theInfo);

		v0->InsertToEdges(edge->Index(), edge);
		v1->InsertToEdges(edge->Index(), edge);

		edges.push_back(std::move(edge));
	}

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->SetWire(wire);
	}

	return std::move(wire);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Pln_Tools::MakePlane
(
	const std::shared_ptr<Pln_Wire>& theWire, 
	const gp_Ax2 & theAx
)
{
	auto plane = Cad2d_Plane::MakePlane(theWire, nullptr, theAx);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Tools::RetrieveBoundingBox
(
	const Pln_Wire & theWire
)
{
	if (NOT theWire.CmpEdge())
	{
		FatalErrorIn("Entity2d_Box Pln_Tools::RetrieveBoundingBox(const Pln_Wire & theWire)")
			<< "Invalid Wire: not has any cmpEdge" << endl
			<< abort(FatalError);
	}
	auto box = RetrieveBoundingBox(*theWire.CmpEdge());
	return std::move(box);
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Tools::RetrieveBoundingBox
(
	const Pln_CmpEdge & theEdge
)
{
	auto box = RetrieveBoundingBox(theEdge.Edges());
	return std::move(box);
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Tools::RetrieveBoundingBox
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	if (theEdges.empty())
	{
		FatalErrorIn("Entity2d_Box Pln_Tools::RetrieveBoundingBox(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)")
			<< "empty list" << endl
			<< abort(FatalError);
	}
	auto iter = theEdges.begin();

	Debug_Null_Pointer((*iter)->Curve());
	auto box = (*iter)->Curve()->BoundingBox(0);

	iter++;

	while (iter NOT_EQUAL theEdges.end())
	{
		Debug_Null_Pointer((*iter)->Curve());
		box = Entity2d_Box::Union(box, (*iter)->Curve()->BoundingBox(0));

		iter++;
	}
	return std::move(box);
}

//std::shared_ptr<tnbLib::Pln_Edge> 
//tnbLib::Pln_Tools::MakeEdges
//(
//	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
//)
//{
//	if (theCurves.empty())
//	{
//		FatalErrorIn("std::shared_ptr<Pln_Edge> MakeEdges(const std::vector<std::shared_ptr<Pln_Curve>>& theCurves)")
//			<< "the list is empty from the curves!" << endl
//			<< abort(FatalError);
//	}
//
//	std::vector<std::shared_ptr<Pln_Edge>> edgeList;
//
//}

std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
tnbLib::Pln_Tools::RetrieveVertices(const Pln_Wire & theWire)
{
	auto vertices = RetrieveVertices(theWire.Edges());
	return std::move(vertices);
}

std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
tnbLib::Pln_Tools::RetrieveVertices
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	Adt_AvlTree<std::shared_ptr<Pln_Vertex>> compact;
	compact.SetComparableFunction(&Pln_Vertex::IsLess);

	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		compact.InsertIgnoreDup(x->Vertex(Pln_Edge::edgePoint::first));
		compact.InsertIgnoreDup(x->Vertex(Pln_Edge::edgePoint::last));
	}

	if (compact.Size() < theEdges.size())
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Pln_Vertex>> list;
	compact.RetrieveTo(list);

	return std::move(list);
}

std::vector<std::shared_ptr<tnbLib::Pln_Segment>> 
tnbLib::Pln_Tools::RetrieveSegments
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	std::vector<std::shared_ptr<Pln_Segment>> segments;
	segments.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		auto seg = std::dynamic_pointer_cast<Pln_Segment>(x);
		if (NOT seg)
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge is not segment" << endl
				<< abort(FatalError);
		}
		segments.push_back(std::move(seg));
	}
	return std::move(segments);
}

std::shared_ptr<Geom2dAPI_InterCurveCurve>
tnbLib::Pln_Tools::Intersection
(
	const Handle(Geom2d_Curve)& theCurve0,
	const Handle(Geom2d_Curve)& theCurve1,
	const Standard_Real theTol
)
{
	auto trimmed0 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve0);
	if (NOT trimmed0)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto trimmed1 = Handle(Geom2d_BoundedCurve)::DownCast(theCurve1);
	if (NOT trimmed1)
	{
		FatalErrorIn("Handle(Geom2dAPI_InterCurveCurve) Intersection(const Handle(Geom2d_Curve)& theCurve0, const Handle(Geom2d_Curve)& theCurve1, const Standard_Real theTol = 1.0E-6)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto Inter = std::make_shared<Geom2dAPI_InterCurveCurve>(theCurve0, theCurve1, theTol);
	Debug_Null_Pointer(Inter);

	return std::move(Inter);
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Tools::Intersection
(
	const std::shared_ptr<Pln_Segment>& theEdge0,
	const std::shared_ptr<Pln_Segment>& theEdge1
)
{
	const auto& v0 = theEdge0->Vtx0();
	const auto& v1 = theEdge0->Vtx1();

	const auto& q0 = theEdge1->Vtx0();
	const auto& q1 = theEdge1->Vtx1();

	if (v0 IS_EQUAL q0)
		return v0;
	if (v0 IS_EQUAL q1)
		return v0;
	if (v1 IS_EQUAL q0)
		return v1;
	if (v1 IS_EQUAL q1)
		return v1;
	return nullptr;
}

Handle(Geom2d_Curve)
tnbLib::Pln_Tools::ConvertToTrimmedCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1
)
{
	Debug_Null_Pointer(theCurve);
	if (theU0 IS_EQUAL theU1)
	{
		FatalErrorIn(FunctionSIG)
			<< "the two parameters are equal" << endl
			<< " - U0 = " << theU0 << endl
			<< " - U1 = " << theU1 << endl
			<< abort(FatalError);
	}
	Handle(Geom2d_Curve) trimmed =
		new Geom2d_TrimmedCurve(theCurve, theU0, theU1, Standard_True, Standard_False);
	return std::move(trimmed);
}

Handle(Geom2d_Curve)
tnbLib::Pln_Tools::ConvertToBSpline
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("Handle(Geom2d_Curve) ConvertToBSpline(const Handle(Geom2d_Curve)& theCurve)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto bspline = Geom2dConvert::CurveToBSplineCurve(theCurve);
	return std::move(bspline);
}

std::shared_ptr<tnbLib::Entity2d_Triangulation>
tnbLib::Pln_Tools::ParametricTriangulation
(
	const Pnt2d & theP0,
	const Pnt2d & theP1,
	const Standard_Integer theNx,
	const Standard_Integer theNy
)
{
	if (theNx < 2)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (theNy < 2)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	const auto Dx = theP1.X() - theP0.X();
	const auto Dy = theP1.Y() - theP0.Y();

	const auto dx = Dx / (Standard_Real)theNx;
	const auto dy = Dy / (Standard_Real)theNy;

	auto tri = std::make_shared<Entity2d_Triangulation>();
	Debug_Null_Pointer(tri);

	auto& pts = tri->Points();
	pts.reserve(theNx*theNy);

	auto& indices = tri->Connectivity();
	indices.reserve((theNx - 1)*(theNy - 1) * 2);

	Standard_Integer k = 0;
	for (auto i = 0; i < theNx; i++)
	{
		for (auto j = 0; j < theNy; j++)
		{
			auto P0 = theP0 + Pnt2d(i*dx, j*dy);
			/*auto P1 = P0 + Pnt2d(dx, 0);
			auto P2 = P0 + Pnt2d(dx, dy);
			auto P3 = P0 + Pnt2d(0, dy);*/
			//cout << i << ", " << j << "  " << P0 << std::endl;
			pts.push_back(std::move(P0));
		}
	}

	for (auto i = 0; i < theNx - 1; i++)
	{
		for (auto j = 0; j < theNy - 1; j++)
		{
			auto i0 = j * theNx + i + 1;
			auto i1 = j * theNx + i + 2;
			auto i2 = (j + 1)*theNx + i + 2;

			auto j0 = i0;
			auto j1 = i2;
			auto j2 = (j + 1)*theNx + i + 1;

			connectivity::triple I0, I1;
			I0.Value(0) = i0;
			I0.Value(1) = i1;
			I0.Value(2) = i2;

			I1.Value(0) = j0;
			I1.Value(1) = j1;
			I1.Value(2) = j2;

			indices.push_back(std::move(I0));
			indices.push_back(std::move(I1));
		}
	}
	return std::move(tri);
}

tnbLib::Entity2d_Box
tnbLib::Pln_Tools::BoundingBox
(
	const Bnd_Box2d & theBox
)
{
	Standard_Real Xmin, Xmax;
	Standard_Real Ymin, Ymax;

	theBox.Get(Xmin, Ymin, Xmax, Ymax);

	Entity2d_Box box(Pnt2d(Xmin, Ymin), Pnt2d(Xmax, Ymax));
	return std::move(box);
}

Bnd_Box2d
tnbLib::Pln_Tools::BoundingBox
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("Handle(Geom2d_Curve) ConvertToBSpline(const Handle(Geom2d_Curve)& theCurve)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	auto box = BoundingBox
	(
		theCurve,
		trimmed->FirstParameter(),
		trimmed->LastParameter()
	);
	return std::move(box);
}

Bnd_Box2d
tnbLib::Pln_Tools::BoundingBox
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1
)
{
	Bnd_Box2d b;
	BndLib_Add2dCurve::Add(theCurve, theU0, theU1, 0, b);

	return std::move(b);
}

tnbLib::Entity2d_Box 
tnbLib::Pln_Tools::BoundingBox
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
)
{
	auto iter = theCurves.begin();
	auto b = (*iter)->BoundingBox(0);
	iter++;
	while (iter NOT_EQUAL theCurves.end())
	{
		b = Geo_BoxTools::Union(b, (*iter)->BoundingBox(0));
		iter++;
	}
	return std::move(b);
}

tnbLib::Entity2d_Box
tnbLib::Pln_Tools::BoundingBox
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	auto b = BoundingBox(RetrieveCurves(theEdges));
	return std::move(b);
}

void tnbLib::Pln_Tools::SplitCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theX,
	Handle(Geom2d_Curve)& theC0,
	Handle(Geom2d_Curve)& theC1
)
{
	/*auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
	if (NOT trimmed)
	{
		FatalErrorIn("void SplitCurve(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theX, Handle(Geom2d_Curve)& theC0, Handle(Geom2d_Curve)& theC1)")
			<< "Invalid Data: the surface is not bounded!" << endl
			<< " - first, convert the surface to RectangularTrimmedSurface then convert it to BSpline" << endl
			<< abort(FatalError);
	}

	if (NOT INSIDE(theX, theCurve->FirstParameter(), theCurve->LastParameter()))
	{
		FatalErrorIn("void SplitCurve(const Handle(Geom2d_Curve)& theCurve, const Standard_Real theX, Handle(Geom2d_Curve)& theC0, Handle(Geom2d_Curve)& theC1)")
			<< "Invalid Parameter: " << theX << endl
			<< " - First parameter: " << theCurve->FirstParameter() << endl
			<< " - Last parameter: " << theCurve->LastParameter() << endl
			<< abort(FatalError);
	}*/

	auto[c0, c1] = Split(theX, theCurve);

	auto first = theCurve->FirstParameter();
	auto last = theCurve->LastParameter();

	if (theX > first)
	{
		//theC0 = Pln_Tools::ConvertToTrimmedCurve(theCurve, first, theX);
		theC0 = c0;
	}
	else
	{
#ifdef _DEBUG
		WarningInFunction 
			<< "the c0 curve is null!" << endl;
#endif // _DEBUG
		theC0 = nullptr;
	}
	
	if (last > theX)
	{
		//theC1 = Pln_Tools::ConvertToTrimmedCurve(theCurve, theX, last);
		theC1 = c1;
	}
	else
	{
#ifdef _DEBUG
		WarningInFunction
			<< "the c0 curve is null!" << endl;
#endif // _DEBUG
		theC1 = nullptr;
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::Pln_Tools::RetrieveCurves
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		curves.push_back(x->Curve());
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Curve>>
tnbLib::Pln_Tools::RetrieveCurves
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves
)
{
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theCurves.size());

	Standard_Integer K = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		if (NOT Pln_Tools::IsBounded(x))
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Wire>> Pln_Tools::RetrieveWires(Args....)")
				<< "the curve is not bounded" << endl
				<< abort(FatalError);
		}

		curves.push_back(std::make_shared<Pln_Curve>(++K, x));
	}
	return std::move(curves);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::Pln_Tools::RetrieveEdges
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves
)
{
	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	std::vector<std::shared_ptr<Pln_Vertex>> ringVertices;

	std::vector<Handle(Geom2d_Curve)> closed;
	std::vector<Handle(Geom2d_Curve)> curves;
	Standard_Integer k = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		if (x->IsClosed())
		{
			auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
			Debug_Null_Pointer(v0);

			ringVertices.push_back(std::move(v0));
			closed.push_back(x);

			continue;
		}

		if (
			x->Value(x->FirstParameter()).Distance(x->Value(x->LastParameter())) 
			<= Precision::Confusion()
			)

		{
			auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
			Debug_Null_Pointer(v0);

			ringVertices.push_back(std::move(v0));
			closed.push_back(x);

			continue;
		}

		auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
		Debug_Null_Pointer(v0);

		vertices.push_back(std::move(v0));

		auto v1 = std::make_shared<Pln_Vertex>(++k, x->Value(x->LastParameter()));
		Debug_Null_Pointer(v1);

		vertices.push_back(std::move(v1));
		curves.push_back(x);
	}

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(theCurves.size());

	k = 0;
	size_t i = 0;
	for (const auto& x : closed)
	{
		Debug_Null_Pointer(x);
		Debug_If_Condition_Message(NOT Pln_Tools::IsBounded(x), "the curve is not bounded!");

		auto curve = std::make_shared<Pln_Curve>(k + 1, std::move(x));
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Ring>(std::move(ringVertices[i++]), std::move(curve));
		Debug_Null_Pointer(edge);

		edge->SetIndex(++k);
		edges.push_back(std::move(edge));
	}

	i = 0;
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		Debug_If_Condition_Message(NOT Pln_Tools::IsBounded(x), "the curve is not bounded!");
		auto curve = std::make_shared<Pln_Curve>(k + 1, std::move(x));
		Debug_Null_Pointer(curve);

		auto edge = std::make_shared<Pln_Segment>(std::move(vertices[2 * i]), std::move(vertices[2 * i + 1]), std::move(curve));
		Debug_Null_Pointer(edge);

		edge->SetIndex(++k);
		edges.push_back(std::move(edge));

		++i;
	}

	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::Pln_Tools::RetrieveEdges
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
)
{
	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	std::vector<std::shared_ptr<Pln_Vertex>> ringVertices;

	std::vector<std::shared_ptr<Pln_Curve>> closed;
	std::vector<std::shared_ptr<Pln_Curve>> curves;
	Standard_Integer k = 0;
	for (const auto& x : theCurves)
	{
		Debug_Null_Pointer(x);

		if (x->Geometry()->IsClosed())
		{
			auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
			Debug_Null_Pointer(v0);

			ringVertices.push_back(std::move(v0));
			closed.push_back(x);

			continue;
		}

		if (
			x->Value(x->FirstParameter()).Distance(x->Value(x->LastParameter()))
			<= Precision::Confusion()
			)

		{
			auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
			Debug_Null_Pointer(v0);

			ringVertices.push_back(std::move(v0));
			closed.push_back(x);

			continue;
		}

		auto v0 = std::make_shared<Pln_Vertex>(++k, x->Value(x->FirstParameter()));
		Debug_Null_Pointer(v0);

		vertices.push_back(std::move(v0));

		auto v1 = std::make_shared<Pln_Vertex>(++k, x->Value(x->LastParameter()));
		Debug_Null_Pointer(v1);

		vertices.push_back(std::move(v1));
		curves.push_back(x);
	}

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.reserve(theCurves.size());

	k = 0;
	size_t i = 0;
	for (const auto& x : closed)
	{
		Debug_Null_Pointer(x);
		auto edge = std::make_shared<Pln_Ring>(std::move(ringVertices[i++]), x);
		Debug_Null_Pointer(edge);

		edge->SetIndex(++k);
		edges.push_back(std::move(edge));
	}

	i = 0;
	for (const auto& x : curves)
	{
		Debug_Null_Pointer(x);
		auto edge = std::make_shared<Pln_Segment>(std::move(vertices[2 * i]), std::move(vertices[2 * i + 1]), x);
		Debug_Null_Pointer(edge);

		edge->SetIndex(++k);
		edges.push_back(std::move(edge));

		++i;
	}

	return std::move(edges);
}

namespace tnbLib
{

	namespace retrieveWires
	{

		struct Vertex
		{

			typedef Pnt2d ptType;

			Standard_Integer Index;
			Pnt2d Coord;

			Standard_Real Prec;

			std::weak_ptr<Vertex> Pair;

			Vertex(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Index(theIndex), Coord(theCoord)
				, Prec(0)
			{}

			static const Pnt2d& GetCoord(const std::shared_ptr<Vertex>& theVtx)
			{
				Debug_Null_Pointer(theVtx);
				return theVtx->Coord;
			}
		};

		struct Edge
		{

			Standard_Integer Index;

			std::shared_ptr<Vertex> Vtx0;
			std::shared_ptr<Vertex> Vtx1;

			std::shared_ptr<Pln_Curve> Curve;

			Edge
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Vertex>& theVtx0,
				const std::shared_ptr<Vertex>& theVtx1
			)
				: Index(theIndex), Vtx0(theVtx0), Vtx1(theVtx1)
			{}
		};

		static std::vector<std::shared_ptr<Edge>> 
			RetrieveUnMergedEdges
			(
				const std::vector<std::shared_ptr<Pln_Curve>>& theCurves
			)
		{
			std::vector<std::shared_ptr<Edge>> edges;
			Standard_Integer nbVertices = 0;
			Standard_Integer nbEdges = 0;
			for (const auto& x : theCurves)
			{
				Debug_Null_Pointer(x);

				auto P0 = x->FirstCoord();
				auto P1 = x->LastCoord();

				auto vtx0 = std::make_shared<Vertex>(++nbVertices, P0);
				auto vtx1 = std::make_shared<Vertex>(++nbVertices, P1);

				Debug_Null_Pointer(vtx0);
				Debug_Null_Pointer(vtx1);

				auto edge = std::make_shared<Edge>(++nbEdges, vtx0, vtx1);
				Debug_Null_Pointer(edge);

				edge->Curve = x;

				edges.push_back(std::move(edge));
			}
			return std::move(edges);
		}

		static std::vector<std::shared_ptr<Vertex>> 
			RetrieveUnMergedVerticesFromEdges
			(
				const std::vector<std::shared_ptr<Edge>>& theEdges
			)
		{
			std::vector<std::shared_ptr<Vertex>> vertices;
			vertices.reserve(2 * theEdges.size());

			for (const auto& x : theEdges)
			{
				Debug_Null_Pointer(x);
				vertices.push_back(x->Vtx0);
				vertices.push_back(x->Vtx1);
			}
			return std::move(vertices);
		}

		static void MergeVertices
		(
			const std::vector<std::shared_ptr<Edge>>& theEdges,
			const Standard_Real theTol,
			const Standard_Real theRadius
		)
		{
			auto unMergedVertices = 
				RetrieveUnMergedVerticesFromEdges(theEdges);

			std::vector<Pnt2d> pts;
			pts.reserve(unMergedVertices.size());

			for (const auto& x : unMergedVertices)
			{
				Debug_Null_Pointer(x);
				pts.push_back(x->Coord);
			}

			auto domain = Entity2d_Box::BoundingBoxOf(pts);

			Geo_PrTree<std::shared_ptr<Vertex>> search;
			search.SetGeometryCoordFunc(&Vertex::GetCoord);
			search.SetGeometryRegion(domain.OffSet(1.0E-3*domain.Diameter()));

			for (const auto& x : unMergedVertices)
			{
				Debug_Null_Pointer(x);

				std::vector<std::shared_ptr<Vertex>> candidates;
				search.GeometrySearch
				(Entity2d_Box(x->Coord - Pnt2d(theRadius, theRadius), x->Coord + Pnt2d(theRadius, theRadius)),
					candidates);

				if (candidates.empty())
				{
					search.InsertToGeometry(x);
				}
				else
				{
					auto minDis = RealLast();
					std::shared_ptr<Vertex> found = nullptr;

					for (const auto& vtx : candidates)
					{
						Debug_Null_Pointer(vtx);
						auto dis = Distance(vtx->Coord, x->Coord);

						if (dis < minDis)
						{
							minDis = dis;
							found = vtx;
						}
					}

					if (minDis <= theTol)
					{
						search.RemoveFromGeometry(found);

						x->Pair = found;
						found->Pair = x;

						x->Prec = minDis;
					}
					else
					{
						search.InsertToGeometry(x);
					}
				}
			}

			{ // info scope
				/*std::cout << "tree size: " << search.Size() << std::endl;
				std::cout << "tol: " << theTol << std::endl;

				std::vector<std::shared_ptr<Vertex>> items;
				search.RetrieveFromGeometryTo(items);

				for (const auto& x : items)
				{
					std::cout << "pt = " << x->Coord << std::endl;
				}

				if (items.size())
				{
					std::cout << Distance(items[0]->Coord, items[1]->Coord) << std::endl;
				}
				std::cout << std::endl;*/
			}
			/*if (search.Size())
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire! tree size = "<< search.Size() << endl
					<< abort(FatalError);
			}*/
		}



		static std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
			RetrieveMergedVertices
			(
				const std::vector<std::shared_ptr<Edge>>& theEdges
			)
		{
			std::map<Standard_Integer, std::shared_ptr<Vertex>> pairdVertices;
			for (const auto& x : theEdges)
			{
				Debug_Null_Pointer(x);

				const auto& vtx0 = x->Vtx0;
				Debug_Null_Pointer(vtx0);

				auto insert0 = pairdVertices.insert(std::make_pair(vtx0->Index, vtx0));
				if (NOT insert0.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data: " << vtx0->Index << endl
						<< abort(FatalError);
				}

				const auto& vtx1 = x->Vtx1;
				Debug_Null_Pointer(vtx1);

				auto insert1 = pairdVertices.insert(std::make_pair(vtx1->Index, vtx1));
				if (NOT insert1.second)
				{
					FatalErrorIn(FunctionSIG)
						<< "duplicate data: " << vtx0->Index << endl
						<< abort(FatalError);
				}
			}

			std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
				vertices;

			Standard_Integer nbVertices = 0;

			auto iter = pairdVertices.begin();
			while (iter NOT_EQUAL pairdVertices.end())
			{
				const auto& x = iter->second;

				auto pair = x->Pair.lock();
				if (pair)
				{
					Debug_Null_Pointer(pair);

					pairdVertices.erase(pair->Index);

					auto M = MEAN(x->Coord, pair->Coord);
					auto vtx = std::make_shared<Pln_Vertex>(++nbVertices, M);
					Debug_Null_Pointer(vtx);

					vtx->SetPrecision(x->Prec);

					auto insert0 = vertices.insert(std::make_pair(x->Index, vtx));
					if (NOT insert0.second)
					{
						FatalErrorIn(FunctionSIG)
							<< "duplicate data: " << x->Index << endl
							<< abort(FatalError);
					}

					auto insert1 = vertices.insert(std::make_pair(pair->Index, vtx));
					if (NOT insert1.second)
					{
						FatalErrorIn(FunctionSIG)
							<< "duplicate data: " << pair->Index << endl
							<< abort(FatalError);
					}
				}
				else
				{
					auto vtx = std::make_shared<Pln_Vertex>(++nbVertices, x->Coord);
					Debug_Null_Pointer(vtx);

					auto insert = vertices.insert(std::make_pair(x->Index, vtx));
					if (NOT insert.second)
					{
						FatalErrorIn(FunctionSIG)
							<< "duplicate data: " << x->Index << endl
							<< abort(FatalError);
					}
				}
				iter++;
			}

			return std::move(vertices);
		}

		static std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Edge>>& theEdges, 
				const std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>& theVertices,
				const Standard_Boolean approx = Standard_True
			)
		{
			std::vector<std::shared_ptr<Pln_Edge>> edges;
			edges.reserve(theEdges.size());

			Standard_Integer nbEdges = 0;
			for (const auto& x : theEdges)
			{
				Debug_Null_Pointer(x);

				Debug_Null_Pointer(x->Vtx0);
				Debug_Null_Pointer(x->Vtx1);

				auto v0 = x->Vtx0->Index;
				auto v1 = x->Vtx1->Index;

				const auto& vtx0 = theVertices.at(v0);
				const auto& vtx1 = theVertices.at(v1);

				auto apxInfo = std::make_shared<Geo_ApprxCurve_Info>();
				Debug_Null_Pointer(apxInfo);

				const auto d = x->Curve->BoundingBox(0).Diameter();

				apxInfo->SetAngle(3.0);
				apxInfo->SetApprox(1.0E-3 * d);
				apxInfo->SetMinSize(1.0E-4 * d);

				apxInfo->SetMaxNbSubdivision(10);
				apxInfo->SetInitNbSubdivision(3);

				apxInfo->SetNbSamples(4);

				if (vtx0 IS_EQUAL vtx1)
				{
					auto edge = std::make_shared<Pln_Ring>(++nbEdges, "", vtx0);
					Debug_Null_Pointer(edge);

					x->Curve->SetIndex(nbEdges);
					edge->SetCurve(x->Curve);
					if (approx) edge->Approx(apxInfo);
					vtx0->InsertToEdges(edge->Index(), edge);

					edges.push_back(std::move(edge));
				}
				else
				{
					auto edge = std::make_shared<Pln_Segment>(++nbEdges, "", vtx0, vtx1);
					Debug_Null_Pointer(edge);

					vtx0->InsertToEdges(edge->Index(), edge);
					vtx1->InsertToEdges(edge->Index(), edge);

					x->Curve->SetIndex(nbEdges);
					edge->SetCurve(x->Curve);
					if (approx) edge->Approx(apxInfo);
					edges.push_back(std::move(edge));
				}	
			}
			return std::move(edges);
		}

		static std::pair<std::shared_ptr<Pln_Vertex>, std::shared_ptr<Pln_Edge>>
			Next
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const std::shared_ptr<Pln_Edge>& thePrior,
				const Standard_Boolean throwExp
			)
		{
			if (throwExp)
			{
				if (theVtx->IsRingPoint())
				{
					FatalErrorIn(FunctionSIG)
						<< "Invalid Wire: the wire is not manifold" << endl
						<< " nb. of edges: " << theVtx->NbEdges() << endl
						<< abort(FatalError);
				}

				if (theVtx->NbEdges() NOT_EQUAL 2)
				{
					FatalErrorIn(FunctionSIG)
						<< "Invalid Wire: the wire is not manifold" << endl
						<< " nb. of edges: " << theVtx->NbEdges() << endl
						<< abort(FatalError);
				}
			}
			else
			{
				if (theVtx->IsRingPoint())
				{
					std::shared_ptr<Pln_Vertex> vtx;
					std::shared_ptr<Pln_Edge> edge;
					auto paired = std::make_pair(std::move(vtx), std::move(edge));
					return std::move(paired);
				}

				if (theVtx->NbEdges() NOT_EQUAL 2)
				{
					std::shared_ptr<Pln_Vertex> vtx;
					std::shared_ptr<Pln_Edge> edge;
					auto paired = std::make_pair(std::move(vtx), std::move(edge));
					return std::move(paired);
				}	
			}

			std::vector<std::weak_ptr<Pln_Edge>> wEdges;
			theVtx->RetrieveEdgesTo(wEdges);

			std::shared_ptr<Pln_Edge> edge;
			if (thePrior)
			{
				auto e0 = wEdges[0].lock();
				auto e1 = wEdges[1].lock();

				if (e0 NOT_EQUAL thePrior)
				{
					edge = e0;
				}
				else
				{
					edge = e1;
				}
			}
			else
			{
				edge = wEdges[0].lock();
			}

			Debug_Null_Pointer(edge);

			if (edge->Vertex(Pln_Edge::edgePoint::first) NOT_EQUAL theVtx)
			{
				auto pair = std::make_pair(edge->Vertex(Pln_Edge::edgePoint::first), edge);
				return std::move(pair);
			}
			else if (edge->Vertex(Pln_Edge::edgePoint::last) NOT_EQUAL theVtx)
			{
				auto pair = std::make_pair(edge->Vertex(Pln_Edge::edgePoint::last), edge);
				return std::move(pair);
			}

			FatalErrorIn(FunctionSIG)
				<< "Invalid Data" << endl
				<< abort(FatalError);
			auto pair = std::make_pair(edge->Vertex(Pln_Edge::edgePoint::first), edge);
			return pair;
		}

		static std::vector<std::shared_ptr<Pln_Edge>>
			TrackWire
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const Standard_Boolean throwExp
			)
		{
			std::vector<std::shared_ptr<Pln_Edge>> edges;

			auto[vtx, edge] = Next(theVtx, nullptr, throwExp);
			if (NOT throwExp)
			{
				if (NOT vtx)
				{
					return std::vector<std::shared_ptr<Pln_Edge>>();
				}
			}
			edges.push_back(std::move(edge));

			while (vtx NOT_EQUAL theVtx)
			{
				auto[ivtx, iedge] = Next(vtx, edges.at(edges.size() - 1), throwExp);
				if (NOT throwExp)
				{
					if (NOT vtx)
					{
						return std::vector<std::shared_ptr<Pln_Edge>>();
					}
				}
				edges.push_back(std::move(iedge));
				vtx = ivtx;
			}
			return std::move(edges);
		}
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Pln_Tools::RetrieveMergedEdges
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const Standard_Real theTol,
	const Standard_Real theRadius
)
{
	auto segments = retrieveWires::RetrieveUnMergedEdges(theCurves);
	auto unMergedVertices = retrieveWires::RetrieveUnMergedVerticesFromEdges(segments);

	retrieveWires::MergeVertices(segments, theTol, theRadius);

	auto mergedVerticesMap = retrieveWires::RetrieveMergedVertices(segments);

	auto edges = retrieveWires::RetrieveEdges(segments, mergedVerticesMap);
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>>
tnbLib::Pln_Tools::RetrieveMergedEdges
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
	const Standard_Real theTol,
	const Standard_Real theRadius
)
{
	if (theRadius < theTol)
	{
		FatalErrorIn(FunctionSIG)
			<< "the radius must be lesser than the tolerance." << endl
			<< " - Tolerance: " << theTol << endl
			<< " - Radius: " << theRadius << endl
			<< abort(FatalError);
	}

	std::map<size_t, std::shared_ptr<Entity2d_Polygon>> polyMap;
	size_t k = 0;
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		if (NOT x->Mesh())
		{
			FatalErrorIn(FunctionSIG)
				<< "the edge doesn't have mesh!" << endl
				<< abort(FatalError);
		}
		auto paired = std::make_pair(k++, x->Mesh());
		polyMap.insert(std::move(paired));
	}

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		curves.push_back(x->Curve());
	}
	auto segments = retrieveWires::RetrieveUnMergedEdges(curves);
	auto unMergedVertices = retrieveWires::RetrieveUnMergedVerticesFromEdges(segments);

	retrieveWires::MergeVertices(segments, theTol, theRadius);

	auto mergedVerticesMap = retrieveWires::RetrieveMergedVertices(segments);

	auto edges = retrieveWires::RetrieveEdges(segments, mergedVerticesMap, Standard_False);
	k = 0;
	for (const auto& x : edges)
	{
		const auto& mesh = polyMap[k++];
		x->Mesh() = mesh;
	}
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>>
tnbLib::Pln_Tools::RetrieveWires
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto curves = RetrieveCurves(theCurves);
	auto wires = Pln_Tools::RetrieveWires(curves, theMinTol, theMaxTol);
	return std::move(wires);
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
tnbLib::Pln_Tools::RetrieveWires
(
	const std::vector<std::shared_ptr<Pln_Curve>>& theCurves,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto edges = RetrieveMergedEdges(theCurves, theMinTol, theMaxTol);

	Adt_AvlTree<std::shared_ptr<Pln_Vertex>>
		vertexMap;
	vertexMap.SetComparableFunction(&Pln_Vertex::IsLess);
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		vertexMap.InsertIgnoreDup(x->Vertex(Pln_Edge::edgePoint::first));
		vertexMap.InsertIgnoreDup(x->Vertex(Pln_Edge::edgePoint::last));
	}

	std::vector<std::shared_ptr<tnbLib::Pln_Wire>> wires;
	while (NOT vertexMap.IsEmpty())
	{
		std::shared_ptr<Pln_Vertex> root;
		vertexMap.Root(root);

		auto wire = RetrieveWire(root);
		Debug_Null_Pointer(wire);

		for (const auto& x : wire->RetrieveVertices())
		{
			Debug_Null_Pointer(x);
			vertexMap.Remove(x);
		}

		wires.push_back(wire);
	}
	return std::move(wires);
}

//std::shared_ptr<tnbLib::Pln_Wire> 
//tnbLib::Pln_Tools::FillGaps
//(
//	const std::shared_ptr<Pln_Wire>& theWire,
//	const Standard_Real tol
//)
//{
//	static auto calcGap = [](const std::shared_ptr<Pln_Edge>& edge0, const std::shared_ptr<Pln_Edge>& edge1)
//	{
//		auto p0 = edge0->LastCoord(edge0->Sense());
//		auto p1 = edge1->FirstCoord(edge1->Sense());
//		auto t = std::make_tuple(p0.Distance(p1), std::move(p0), std::move(p1));
//		return std::move(t);
//	};
//
//	const auto& cmpEdge = theWire->CmpEdge();
//	Debug_Null_Pointer(cmpEdge);
//	const auto& edges = cmpEdge->Edges();
//
//	std::vector<std::shared_ptr<Pln_Curve>> curves;
//	std::vector<Standard_Boolean> senses;
//	for (size_t i = 1; i < edges.size(); i++)
//	{
//		const auto& edge0 = edges[i - 1];
//		const auto& edge1 = edges[i];
//
//		Debug_Null_Pointer(edge0);
//		Debug_Null_Pointer(edge1);
//
//		curves.push_back(edge0->Curve());
//		senses.push_back(edge0->Sense());
//
//		auto[gap, p0, p1] = calcGap(edge0, edge1);
//		if (gap < tol)
//		{
//			auto curve = std::make_shared<Pln_Curve>(Pln_CurveTools::MakeSegment(p0, p1));
//			curves.push_back(std::move(curve));
//			senses.push_back(Standard_True);
//		}
//	}
//	curves.push_back(LastItem(edges)->Curve());
//	senses.push_back(LastItem(edges)->Sense());
//
//	if (curves.size() IS_EQUAL edges.size())
//	{
//		return theWire;
//	}
//	else
//	{
//		auto wire=
//	}
//}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::RetrieveWire
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	auto cmpEdge = RetrieveCompoundEdge(theVtx);
	if (NOT cmpEdge)
	{
		return nullptr;
	}

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	for (const auto& x : cmpEdge->Edges())
	{
		Debug_Null_Pointer(x);
		x->SetWire(wire);
	}

	return std::move(wire);
}

std::shared_ptr<tnbLib::Pln_CmpEdge> 
tnbLib::Pln_Tools::RetrieveCompoundEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	if (theVtx->IsRingPoint())
	{
		auto cmpEdge = std::make_shared<Pln_CmpEdge>();
		Debug_Null_Pointer(cmpEdge);

		std::vector<std::weak_ptr<Pln_Edge>> wEdges;
		theVtx->RetrieveEdgesTo(wEdges);

		cmpEdge->Insert(wEdges[0].lock());

		return std::move(cmpEdge);
	}

	auto edges = retrieveWires::TrackWire(theVtx, Standard_False);
	if (edges.size())
	{
		auto cmpEdge = std::make_shared<Pln_CmpEdge>();
		Debug_Null_Pointer(cmpEdge);

		cmpEdge->ChangeEdges() = std::move(edges);

		SameSense(cmpEdge);
		return std::move(cmpEdge);
	}
	else
	{
		return nullptr;
	}
}

void tnbLib::Pln_Tools::SameSense
(
	const std::shared_ptr<Pln_CmpEdge>& theEdge
)
{
	const auto& edges = theEdge->Edges();

	if (edges.size() < 2)
	{
		return;
	}

	if (edges.size() IS_EQUAL 2)
	{
		auto edge0 = edges.at(0);
		auto edge1 = edges.at(1);

		if (edge0->LastVtx() IS_EQUAL edge1->FirstVtx())
		{
			return;
		}
		else
		{
			edge1->Reverse(Standard_True);
			return;
		}
	}
	else
	{
		auto iter = edges.begin();
		auto edge0 = (*iter);

		iter++;

		while (iter NOT_EQUAL edges.end())
		{
			auto edge1 = (*iter);

			std::shared_ptr<Pln_Vertex> vtx;
			if (NOT Pln_Edge::IsConnected(edge0, edge1, vtx))
			{
				FatalErrorIn("void tnbLib::Pln_Tools::SameSense(const std::shared_ptr<Pln_CmpEdge>& theEdge)")
					<< "Invalid CmpEdge: the two edges are not connected!" << endl
					<< abort(FatalError);
			}

			auto indx0 = edge0->GetPoint(vtx);
			auto indx1 = edge1->GetPoint(vtx);

			if (indx0 NOT_EQUAL Pln_Edge::edgePoint::last)
			{
				edge0->Reverse(Standard_True);
			}

			if (indx1 NOT_EQUAL Pln_Edge::edgePoint::first)
			{
				edge1->Reverse(Standard_True);
			}

			if (edge0->Vertex(Pln_Edge::edgePoint::last) NOT_EQUAL edge1->Vertex(Pln_Edge::edgePoint::first))
			{
				FatalErrorIn("void tnbLib::Pln_Tools::SameSense(const std::shared_ptr<Pln_CmpEdge>& theEdge)")
					<< "Invalid CmpEdge: the two edges are not consecutive" << endl
					<< abort(FatalError);
			}

			iter++;

			edge0 = edge1;
		}
	}
}

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::RetrieveOuterWire
(
	const std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	if (theWires.empty())
	{
		return nullptr;
	}

	if (theWires.size() IS_EQUAL 1)
	{
		if (theWires[0]->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
		{
			theWires[0]->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
		}

		return theWires[0];
	}

	auto iter = theWires.begin();
	auto outer = (*iter);
	Debug_Null_Pointer(outer);

	iter++;

	auto maxBox = outer->BoundingBox(0);

	while (iter NOT_EQUAL theWires.end())
	{
		auto wire = (*iter);
		Debug_Null_Pointer(wire);

		auto box = wire->BoundingBox(0);

		if (Entity2d_Box::IsInside(maxBox, box))
		{
			maxBox = box;
			outer = wire;
		}

		iter++;
	}

	for (const auto& x : theWires)
	{
		if(x IS_EQUAL outer)
			continue;

		Debug_Null_Pointer(x);
		if (NOT Entity2d_Box::IsInside(x->BoundingBox(0), maxBox))
		{
			return nullptr;
		}
	}

	if (outer->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
	{
		outer->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
	}
	return std::move(outer);
}

namespace tnbLib
{

	namespace plnLib
	{

		static Standard_Boolean 
			CheckInner
			(
				const std::vector<std::shared_ptr<Pln_Wire>>& theInners, 
				const std::shared_ptr<Pln_Wire>& theWire
			)
		{
			const auto b = theWire->BoundingBox(0);
			for (const auto& x : theInners)
			{
				Debug_Null_Pointer(x);
				if (Entity2d_Box::IsInside(b, x->BoundingBox(0)))
				{
					return Standard_True;
				}
			}
			return Standard_False;
		}

		static void RetrieveInnerOuterWires
		(
			std::list<std::shared_ptr<Pln_Wire>>& theWires,
			std::shared_ptr<Pln_Wire>& theOuter,
			std::vector<std::shared_ptr<Pln_Wire>>& theInners
		)
		{
			if (theWires.size() IS_EQUAL 1)
			{
				theOuter = theWires.front();
				theWires.pop_front();
				return;
			}

			theOuter = theWires.front();
			theWires.pop_front();

			const auto outerBox = theOuter->BoundingBox(0);

			std::vector<std::list<std::shared_ptr<Pln_Wire>>::iterator> removes;
			auto iter = theWires.begin();
			while (iter NOT_EQUAL theWires.end())
			{
				const auto& x = (*iter);
				if (Entity2d_Box::IsInside(x->BoundingBox(0), outerBox))
				{
					if (NOT CheckInner(theInners, x))
					{
						theInners.push_back(x);
						removes.push_back(iter);
					}
				}

				iter++;
			}

			for (const auto& x : removes)
			{
				theWires.erase(x);
			}
		}
	}
}

std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> 
tnbLib::Pln_Tools::RetrievePlanes
(
	const std::vector<std::shared_ptr<Pln_Wire>>& theWires,
	const gp_Ax2& theAx
)
{
	auto wires = theWires;
	SortWires(wires);

	std::list<std::shared_ptr<Pln_Wire>> wireList;
	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		wireList.push_back(x);
	}

	Standard_Integer K = 0;
	std::vector<std::shared_ptr<Cad2d_Plane>> planes;
	while (NOT wireList.empty())
	{
		std::shared_ptr<Pln_Wire> outer;
		auto inners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
		Debug_Null_Pointer(inners);

		plnLib::RetrieveInnerOuterWires(wireList, outer, *inners);

		if (NOT outer)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> Pln_Tools::RetrievePlanes(Args...)")
				<< "Invalid section" << endl
				<< abort(FatalError);
		}

		if (outer->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
		{
			outer->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);
		}

		if (inners->empty())
		{
			auto pln = Cad2d_Plane::MakePlane(outer, nullptr, theAx);
			Debug_Null_Pointer(pln);

			pln->SetIndex(++K);

			planes.push_back(std::move(pln));
		}
		else
		{
			for (const auto& x : *inners)
			{
				Debug_Null_Pointer(x);
				if (x->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CW)
				{
					x->ApplyOrientation(Pln_Orientation::Pln_Orientation_CW);
				}
			}

			auto pln = Cad2d_Plane::MakePlane(outer, inners);
			Debug_Null_Pointer(pln);

			pln->SetIndex(++K);

			planes.push_back(std::move(pln));
		}
	}
	return std::move(planes);
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Tools::NextNode
(
	const std::shared_ptr<Pln_Vertex>& theNode,
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	Debug_Null_Pointer(theNode);
	Debug_Null_Pointer(theEdge);

	const auto& v0 = theEdge->Vertex(Pln_Edge::edgePoint::first);
	const auto& v1 = theEdge->Vertex(Pln_Edge::edgePoint::last);

	if (v0 IS_EQUAL theNode)
	{
		return v1;
	}
	if (v1 IS_EQUAL theNode)
	{
		return v0;
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::NextEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge,
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	const auto edges = theVtx->RetrieveEdges();
	if (edges.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "the vertex is not manifold" << endl
			<< abort(FatalError);
	}

	if (edges[0].lock() IS_EQUAL theEdge)
	{
		return edges[1].lock();
	}
	if (edges[1].lock() IS_EQUAL theEdge)
	{
		return edges[0].lock();
	}
	FatalErrorIn(FunctionSIG)
		<< "Unable to find the next edge" << endl
		<< abort(FatalError);
	return nullptr;
}

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::Pln_Edge>>,
	std::shared_ptr<tnbLib::Pln_Vertex>, 
	std::shared_ptr<tnbLib::Pln_Vertex>
> 
tnbLib::Pln_Tools::MarchOnEdges
(
	const std::shared_ptr<Pln_Vertex>& theVtx, 
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	auto v0 = theVtx;
	auto nextEdge = theEdge;

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.push_back(nextEdge);

	auto nextVtx = Pln_Tools::NextNode(theVtx, nextEdge);
	while (nextVtx->IsManifold())
	{
		nextEdge = Pln_Tools::NextEdge(nextEdge, nextVtx);
		edges.push_back(nextEdge);

		nextVtx = Pln_Tools::NextNode(nextVtx, nextEdge);
	}

	auto v1 = nextVtx;
	auto t = std::make_tuple(std::move(edges), std::move(v0), std::move(v1));
	return std::move(t);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::ForwardEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	theVtx->RetrieveEdgesTo(edges);

	for (const auto& x : edges)
	{
		auto edge = x.lock();
		Debug_Null_Pointer(edge);

		if (edge->FirstVtx() IS_EQUAL theVtx)
			return std::move(edge);
	}
	return nullptr;
}

std::shared_ptr<tnbLib::Pln_Edge>
tnbLib::Pln_Tools::BackwardEdge
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	std::vector<std::weak_ptr<Pln_Edge>> edges;
	theVtx->RetrieveEdgesTo(edges);

	for (const auto& x : edges)
	{
		auto edge = x.lock();
		Debug_Null_Pointer(edge);

		if (edge->LastVtx() IS_EQUAL theVtx)
			return std::move(edge);
	}
	return nullptr;
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Pln_Tools::MakeConsecutive
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges,
	const Standard_Real theTol
)
{
	auto edges = 
		cad2dLib::Modeler_Tools::MakeConsecutive(theEdges, theTol);
	return std::move(edges);
}

namespace tnbLib
{
	namespace plnLib
	{

		static Standard_Boolean LessDiameterSize
		(
			const std::shared_ptr<Pln_Wire>& theWire0,
			const std::shared_ptr<Pln_Wire>& theWire1
		)
		{
			Debug_Null_Pointer(theWire0);
			Debug_Null_Pointer(theWire1);

			const auto b0 = theWire0->BoundingBox(0);
			const auto b1 = theWire1->BoundingBox(0);

			return -b0.SquareDiameter() < -b1.SquareDiameter();
		}
	}
}

void tnbLib::Pln_Tools::SortWires
(
	std::vector<std::shared_ptr<Pln_Wire>>& theWires
)
{
	if (theWires.size() IS_EQUAL 1)
	{
		return;
	}

	Geo_ItemSort<std::shared_ptr<Pln_Wire>>
		sort(&plnLib::LessDiameterSize);
	sort.Perform(theWires);
}

std::shared_ptr<tnbLib::Pln_Vertex> 
tnbLib::Pln_Tools::Vertex
(
	const std::shared_ptr<Pln_Entity>& theEnt
)
{
	auto ent = std::dynamic_pointer_cast<Pln_Vertex>(theEnt);
	return std::move(ent);
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Pln_Tools::Edge
(
	const std::shared_ptr<Pln_Entity>& theEnt
)
{
	auto ent = std::dynamic_pointer_cast<Pln_Edge>(theEnt);
	return std::move(ent);
}

std::shared_ptr<tnbLib::Pln_Curve> 
tnbLib::Pln_Tools::Curve
(
	const std::shared_ptr<Pln_Entity>& theEnt
)
{
	auto ent = std::dynamic_pointer_cast<Pln_Curve>(theEnt);
	return std::move(ent);
}

std::shared_ptr<tnbLib::Pln_Ring>
tnbLib::Pln_Tools::Ring
(
	const std::shared_ptr<Pln_Entity>& theEnt
)
{
	auto ent = std::dynamic_pointer_cast<Pln_Ring>(theEnt);
	return std::move(ent);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Pln_Tools::Plane
(
	const std::shared_ptr<Pln_Entity>& theEnt
)
{
	auto ent = std::dynamic_pointer_cast<Cad2d_Plane>(theEnt);
	return std::move(ent);
}

std::vector<TopoDS_Edge> 
tnbLib::Pln_Tools::RetrieveEdges
(
	const TopoDS_Shape & theEdges
)
{
	std::vector<TopoDS_Edge> edges;
	for
		(
			TopExp_Explorer explorer(theEdges, TopAbs_EDGE);
			explorer.More();
			explorer.Next()
			)
	{
		auto edge = TopoDS::Edge(explorer.Current());
		if (NOT edge.IsNull())
		{
			edges.push_back(edge);
		}
	}
	return std::move(edges);
}

std::shared_ptr<tnbLib::Entity2d_Chain>
tnbLib::Pln_Tools::RetrieveTriangulation
(
	const Pln_Edge & theEdge
)
{
	if (NOT theEdge.Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge is not discretized!" << endl
			<< abort(FatalError);
	}
	auto tri = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(tri);

	tri->Points() = theEdge.Mesh()->Points();
	tri->Connectivity() = dualConnectivityList_Chain(theEdge.Mesh()->NbPoints() - 1);
	return std::move(tri);
}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Pln_Tools::RetrieveTriangulation
(
	const Pln_Wire & theWire
)
{
	auto tri = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(tri);

	for (const auto& x : theWire.Edges())
	{
		Debug_Null_Pointer(x);

		auto t = RetrieveTriangulation(*x);
		Debug_Null_Pointer(t);

		auto& tRef = *t;
		tri->Add(std::move(tRef));
	}
	return std::move(tri);
}

std::vector<Handle(Geom2d_Curve)> 
tnbLib::Pln_Tools::RetrieveParaCurves
(
	const std::vector<TopoDS_Edge>& theEdges, 
	const gp_Ax2 & theSystem
)
{
	Handle(Geom_Plane) plane = new Geom_Plane(gp_Pln(theSystem));
	Debug_Null_Pointer(plane);

	TopLoc_Location loc;

	std::vector<Handle(Geom2d_Curve)> curves;
	curves.reserve(theEdges.size());

	for (const auto& x : theEdges)
	{
		Standard_Real first, last;
		auto curve = BRep_Tool::CurveOnPlane(x, plane, loc, first, last);

		if (curve.IsNull())
		{
			FatalErrorIn("std::vector<Handle(Geom2d_Curve)> Marine_CmpSection::RetrieveParaCurves(Args...)")
				<< "Failed to Calculate the parametric curve" << endl
				<< abort(FatalError);
		}

		curves.push_back(std::move(curve));
	}
	return std::move(curves);
}

void tnbLib::Pln_Tools::ChangeVertex
(
	const std::shared_ptr<Pln_Ring>& theRing, 
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	Debug_Null_Pointer(theRing);
	theRing->VtxRef() = theVtx;
}

void tnbLib::Pln_Tools::ChangeVertex
(
	const std::shared_ptr<Pln_Segment>& theSeg,
	const std::shared_ptr<Pln_Vertex>& theV0,
	const std::shared_ptr<Pln_Vertex>& theV1
)
{
	Debug_Null_Pointer(theSeg);
	theSeg->Vtx0Ref() = theV0;
	theSeg->Vtx1Ref() = theV1;
}

void tnbLib::Pln_Tools::ChangeVertex
(
	const std::shared_ptr<Pln_Ring>& theRing,
	std::shared_ptr<Pln_Vertex>&& theVtx
)
{
	Debug_Null_Pointer(theRing);
	theRing->VtxRef() = std::move(theVtx);
}

void tnbLib::Pln_Tools::ChangeVertex
(
	const std::shared_ptr<Pln_Segment>& theSeg,
	std::shared_ptr<Pln_Vertex>&& theV0,
	std::shared_ptr<Pln_Vertex>&& theV1
)
{
	Debug_Null_Pointer(theSeg);
	theSeg->Vtx0Ref() = std::move(theV0);
	theSeg->Vtx1Ref() = std::move(theV1);
}

void tnbLib::Pln_Tools::RetrieveInnerOuterWires
(
	std::list<std::shared_ptr<Pln_Wire>>& theWires,
	std::shared_ptr<Pln_Wire>& theOuter,
	std::vector<std::shared_ptr<Pln_Wire>>& theInners
)
{
	if (theWires.size() IS_EQUAL 1)
	{
		theOuter = theWires.front();
		theWires.pop_front();
		return;
	}

	theOuter = theWires.front();
	theWires.pop_front();

	const auto outerBox = theOuter->BoundingBox(0);

	std::vector<std::list<std::shared_ptr<Pln_Wire>>::iterator> removes;
	auto iter = theWires.begin();
	while (iter NOT_EQUAL theWires.end())
	{
		const auto& x = (*iter);
		if (Entity2d_Box::IsInside(x->BoundingBox(0), outerBox))
		{
			theInners.push_back(x);
			removes.push_back(iter);
		}

		iter++;
	}

	for (const auto& x : removes)
	{
		theWires.erase(x);
	}
}

void tnbLib::Pln_Tools::SetPrecision
(
	const std::shared_ptr<Pln_Wire>& theWire, 
	const Standard_Real theOffsetTol
)
{
	const auto vertices = RetrieveVertices(*theWire);
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		x->SetPrecision(CalcPrecision(*x) + theOffsetTol);
	}
}

void tnbLib::Pln_Tools::PlaceVertices
(
	const std::shared_ptr<Pln_Wire>& theWire
)
{
	if (NOT theWire)
	{
		FatalErrorIn(FunctionSIG)
			<< " the wire is null" << endl
			<< abort(FatalError);
	}
	auto vertices = theWire->RetrieveVertices();
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		PlaceVertex(x);
	}
}

void tnbLib::Pln_Tools::PlaceVertex
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	Debug_Null_Pointer(theVtx);
	if (NOT theVtx->IsManifold())
	{
		FatalErrorIn(FunctionSIG)
			<< "the vertex is not manifold" << endl
			<< abort(FatalError);
	}

	auto bwd = BackwardEdge(theVtx);
	auto fwd = ForwardEdge(theVtx);

	auto p0 = bwd->LastCoord(bwd->Sense());
	auto p1 = fwd->FirstCoord(fwd->Sense());

	auto mp = MEAN(p0, p1);
	theVtx->Coord() = std::move(mp);
}

void tnbLib::Pln_Tools::CheckManifold
(
	const std::shared_ptr<Pln_Wire>& theWire
)
{
	const auto vertices = RetrieveVertices(*theWire);
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsManifold())
		{
			FatalErrorIn(FunctionSIG)
				<< "the wire is non-manifold" << endl
				<< " - nb. of edges: " << x->NbEdges() << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::Pln_Tools::CheckWire(const std::shared_ptr<Pln_Edge>& theEdge)
{
	if (NOT theEdge->IsRing())
	{
		FatalErrorIn(FunctionSIG)
			<< "The edge is not a ring." << endl
			<< abort(FatalError);
	}
}

void tnbLib::Pln_Tools::CheckWire
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	if (theEdges.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge list is empty." << endl
			<< abort(FatalError);
	}

	if (theEdges.size() IS_EQUAL 1)
	{
		CheckWire(theEdges.at(0));
		return;
	}
	else
	{
		// Check if all edges are a segment. [2/2/2022 Amir]
		for (const auto& x : theEdges)
		{
			Debug_Null_Pointer(x);
			if (x->IsRing())
			{
				FatalErrorIn(FunctionSIG)
					<< "The edge is supposed to be a segment, not a ring." << endl
					<< abort(FatalError);
			}
		}

		// Check if each two-consecutive edges have an intersection, [2/2/2022 Amir]
		for (size_t k = 1; k < theEdges.size(); k++)
		{
			const auto e0 = std::dynamic_pointer_cast<Pln_Segment>(theEdges[k - 1]);
			const auto e1 = std::dynamic_pointer_cast<Pln_Segment>(theEdges[k]);

			Debug_Null_Pointer(e0);
			Debug_Null_Pointer(e1);

			auto vtx = CommonVertex(e0, e1);
			if (NOT vtx)
			{
				FatalErrorIn(FunctionSIG)
					<< "The two following edges have no intersection." << endl
					<< abort(FatalError);
			}

			if (NOT vtx->IsManifold())
			{
				FatalErrorIn(FunctionSIG)
					<< "The vertex is not manifold." << endl
					<< abort(FatalError);
			}
		}
	}
}

void tnbLib::Pln_Tools::Connect
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	if (auto ring = std::dynamic_pointer_cast<Pln_Ring>(theEdge))
	{
		const auto& v0 = ring->Vtx();
		Debug_Null_Pointer(v0);

		v0->InsertToEdges(theEdge->Index(), theEdge);
	}
	else if (auto seg = std::dynamic_pointer_cast<Pln_Segment>(theEdge))
	{
		const auto& v0 = seg->Vtx0();
		Debug_Null_Pointer(v0);

		const auto& v1 = seg->Vtx1();
		Debug_Null_Pointer(v1);

		v0->InsertToEdges(theEdge->Index(), theEdge);
		v1->InsertToEdges(theEdge->Index(), theEdge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of edge has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Pln_Tools::Connect
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	if (auto ring = std::dynamic_pointer_cast<Pln_Ring>(theEdge))
	{
		const auto& v0 = ring->Vtx();
		Debug_Null_Pointer(v0);

		v0->InsertToEdges(theIndex, theEdge);
	}
	else if (auto seg = std::dynamic_pointer_cast<Pln_Segment>(theEdge))
	{
		const auto& v0 = seg->Vtx0();
		Debug_Null_Pointer(v0);

		const auto& v1 = seg->Vtx1();
		Debug_Null_Pointer(v1);

		v0->InsertToEdges(theIndex, theEdge);
		v1->InsertToEdges(theIndex, theEdge);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "unspecified type of edge has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Pln_Tools::Connect
(
	const std::shared_ptr<Pln_Wire>& theWire
)
{
	Debug_Null_Pointer(theWire);
	for (const auto& x : theWire->Edges())
	{
		Debug_Null_Pointer(x);
		x->SetWire(theWire);

		Connect(x);
	}
}

void tnbLib::Pln_Tools::Connect
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
{
	Debug_Null_Pointer(thePlane);
	const auto& outer = thePlane->OuterWire();
	Debug_Null_Pointer(outer);

	Connect(outer);

	if (thePlane->InnerWires())
	{
		for (const auto& x : *thePlane->InnerWires())
		{
			Debug_Null_Pointer(x);
			Connect(x);
		}
	}
}

void tnbLib::Pln_Tools::WatertightWire
(
	const std::vector<std::shared_ptr<Entity2d_Polygon>>& theWire
)
{
	for (size_t i = 1; i < theWire.size(); i++)
	{
		const auto& poly0 = theWire.at(i - 1);
		const auto& poly1 = theWire.at(i);

		Debug_If_Condition(NOT poly0->NbPoints());
		Debug_If_Condition(NOT poly1->NbPoints());

		auto& pts0 = poly0->Points();
		auto& pts1 = poly1->Points();

		pts0.at(pts0.size() - 1) = pts1.at(0) = MEAN(pts0.at(pts0.size() - 1), pts1.at(0));
	}

	const auto& poly0 = theWire.at(theWire.size() - 1);
	const auto& poly1 = theWire.at(0);

	Debug_If_Condition(NOT poly0->NbPoints());
	Debug_If_Condition(NOT poly1->NbPoints());

	auto& pts0 = poly0->Points();
	auto& pts1 = poly1->Points();

	pts0.at(pts0.size() - 1) = pts1.at(0) = MEAN(pts0.at(pts0.size() - 1), pts1.at(0));
}

//std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
//tnbLib::Pln_Tools::RetrieveVertices
//(
//	const std::shared_ptr<Pln_Entity>& theEnt
//)
//{
//	return std::vector<std::shared_ptr<Pln_Vertex>>();
//}

//void tnbLib::Pln_Tools::ImportToCorner
//(
//	const std::shared_ptr<Pln_Vertex>& theVtx, 
//	Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>& theEngine
//)
//{
//#ifdef _DEBUG
//	const auto& domain = theEngine.GeometryBoundingBox();
//	if (NOT domain.IsInside(theVtx->Coord()))
//	{
//		FatalErrorIn("void ImportToCorner(const std::shared_ptr<Pln_Vertex>&, Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>&)")
//			<< "the vertex is out of domain!" << endl
//			<< abort(FatalError);
//	}
//#endif // _DEBUG
//
//	const auto radius = theVtx->Precision();
//	Debug_If_Condition_Message(radius <= RealFirst(), "the precision is not set!");
//
//	auto b = Entity2d_Box::Box(theVtx->Coord(), radius);
//	if (theEngine.IsEmpty())
//	{
//		auto crn = std::make_shared<cad2dLib::Modeler_Corner>(1);
//		Debug_Null_Pointer(crn);
//
//		crn->InsertToCorners(theVtx->Index(), theVtx);
//		crn->SetCoord(theVtx->Coord());
//		theEngine.InsertToGeometry(crn);
//		return;
//	}
//
//	std::vector<std::shared_ptr<cad2dLib::Modeler_Corner>> corners;
//	theEngine.GeometrySearch(b, corners);
//
//	if (NOT corners.size())
//	{
//		auto crn = std::make_shared<cad2dLib::Modeler_Corner>(theEngine.Size() + 1);
//		Debug_Null_Pointer(crn);
//
//		crn->InsertToCorners(theVtx->Index(), theVtx);
//		crn->SetCoord(theVtx->Coord());
//		theEngine.InsertToGeometry(crn);
//		return;
//	}
//
//	auto minDis = RealLast();
//	Standard_Integer k = -1;
//	Standard_Integer i = 0;
//	for (const auto& x : corners)
//	{
//		auto dis = x->Coord().SquareDistance(theVtx->Coord());
//		if (dis <= minDis)
//		{
//			minDis = dis;
//			k = i;
//		}
//		i++;
//	}
//	
//	Debug_If_Condition(k < 0);
//	const auto& crn = corners[k];
//
//	try
//	{
//		crn->InsertToCorners(theVtx->Index(), theVtx);
//	}
//	catch (const std::exception&)
//	{
//		FatalErrorIn("void ImportToCorner(const std::shared_ptr<Pln_Vertex>&, Geo_AdTree<std::shared_ptr<cad2dLib::Modeler_Corner>>&)")
//			<< "unable to insert the vertex into the tree!" << endl
//			<< abort(FatalError);
//	}
//}