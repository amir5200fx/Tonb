#include <Pln_Tools.hxx>

#include <Geo_PrTree.hxx>
#include <Geo_CurveIntegrand_Function.hxx>
#include <Geo_ApprxCurve_Info.hxx>
#include <Adt_AvlTree.hxx>
#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Entity2d_Triangulation.hxx>
#include <NumAlg_AdaptiveInteg.hxx>

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dConvert.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

Standard_Boolean 
tnbLib::Pln_Tools::IsBounded
(
	const Handle(Geom2d_Curve)& theCurve
)
{
	return (Standard_Boolean)Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
}

Standard_Real 
tnbLib::Pln_Tools::Length
(
	const Handle(Geom2d_Curve)& theCurve,
	const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
)
{
	Geo_CurveIntegrand_Function<Geom2d_Curve, void, false>
		function(*theCurve);

	NumAlg_AdaptiveInteg<Geo_CurveIntegrand_Function<Geom2d_Curve, void, false>>
		alg(function, theCurve->FirstParameter(), theCurve->LastParameter(), *theInfo);

	alg.Perform();

	if (NOT alg.IsDone())
	{
		FatalErrorIn("Standard_Real Length(Args...)")
			<< "the integration is not performed!" << endl
			<< abort(FatalError);
	}

	return theInfo->Result();
}

std::shared_ptr<tnbLib::Pln_CmpEdge> 
tnbLib::Pln_Tools::MakeCompoundEdge
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
)
{
	auto pln = std::make_shared<Pln_CmpEdge>();

	if (theEdges.size() IS_EQUAL 1)
	{
		pln->Insert(theEdges[0]);

		return std::move(pln);
	}

	pln->Insert(theEdges[0]);

	forThose(Index, 1, theEdges.size() - 1)
	{
		if (theEdges[Index]->Vtx0() NOT_EQUAL theEdges[Index - 1]->Vtx1())
		{
			FatalErrorIn("std::shared_ptr<Pln_CmpEdge> MakeCompoundEdge(const std::vector<std::shared_ptr<Pln_Edge>>& theEdges)")
				<< "Unable to make compound edge" << endl
				<< abort(FatalError);
		}

		pln->Insert(theEdges[Index]);
	}

	return std::move(pln);
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

		auto edge = std::make_shared<Pln_Edge>(v0, v1, x);
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

	info->SetAngle(2.0);
	info->SetApprox(1.0E-4*box.Diameter());

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
				auto pt = curve.LastCoord();
				return std::move(pt);
			}
			else
			{
				auto pt = curve.FirstCoord();
				return std::move(pt);
			}
		}
		else
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
	if (theCurves.empty())
	{
		FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
			<< "the list of the curves is empty!" << endl
			<< abort(FatalError);
	}

	auto info = std::make_shared<Geo_ApprxCurve_Info>();
	Debug_Null_Pointer(info);

	info->SetAngle(2.0);
	info->SetApprox(1.0E-4);

	if (theCurves.size() IS_EQUAL 1)
	{
		const auto& c = theCurves[0];

		auto p0 = c->FirstCoord();
		auto p1 = c->LastCoord();

		auto m = MEAN(p0, p1);

		if (p0.Distance(p1) > theMaxTol)
		{
			FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
				<< "the curve is not formed a wire; max tolerance = " << theMaxTol << endl
				<< abort(FatalError);
		}

		auto v = std::make_shared<Pln_Vertex>(1, m);
		Debug_Null_Pointer(v);

		v->SetPrecision(MAX(m.Distance(p0), m.Distance(p1)));

		auto ring = std::make_shared<Pln_Ring>(v, c, theSense[0]);
		Debug_Null_Pointer(ring);

		ring->SetIndex(1);
		ring->Approx(info);

		auto wire = MakeWire(ring);

		return std::move(wire);
	}

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	vertices.reserve(theCurves.size());

	auto p0 = GetCoord(*theCurves[theCurves.size() - 1], theSense[theSense.size() - 1], 1);
	
	forThose(Index, 0, theCurves.size() - 1)
	{
		auto p1 = GetCoord(*theCurves[Index], theSense[Index], 0);

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

		auto edge = std::make_shared<Pln_Edge>(v0, v1, x, theSense[K]);
		Debug_Null_Pointer(edge);

		edge->SetIndex(++K);
		edge->Approx(info);

		edges.push_back(std::move(edge));
	}

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	return std::move(wire);
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
	auto box = (*iter)->Curve()->CalcBoundingBox();

	iter++;

	while (iter NOT_EQUAL theEdges.end())
	{
		Debug_Null_Pointer((*iter)->Curve());
		box = Entity2d_Box::Union(box, (*iter)->Curve()->CalcBoundingBox());

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
		compact.InsertIgnoreDup(x->Vtx0());
		compact.InsertIgnoreDup(x->Vtx1());
	}

	std::vector<std::shared_ptr<Pln_Vertex>> list;
	compact.RetrieveTo(list);

	return std::move(list);
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

Handle(Geom2d_Curve)
tnbLib::Pln_Tools::ConvertToTrimmedCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theU0,
	const Standard_Real theU1
)
{
	Handle(Geom2d_Curve) trimmed =
		new Geom2d_TrimmedCurve(theCurve, theU0, theU1);
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
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
			<< "Invalid Data" << endl
			<< abort(FatalError);
	}

	if (theNy < 2)
	{
		FatalErrorIn("std::shared_ptr<AutLib::Entity2d_Triangulation> ParametricTriangulation()")
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

void tnbLib::Pln_Tools::SplitCurve
(
	const Handle(Geom2d_Curve)& theCurve,
	const Standard_Real theX,
	Handle(Geom2d_Curve)& theC0,
	Handle(Geom2d_Curve)& theC1
)
{
	auto trimmed = Handle(Geom2d_BoundedCurve)::DownCast(theCurve);
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
	}

	auto first = theCurve->FirstParameter();
	auto last = theCurve->LastParameter();

	theC0 = Pln_Tools::ConvertToTrimmedCurve(theCurve, first, theX);
	theC1 = Pln_Tools::ConvertToTrimmedCurve(theCurve, theX, last);
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

			std::weak_ptr<Vertex> Pair;

			Vertex(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Index(theIndex), Coord(theCoord)
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

			Handle(Geom2d_Curve) Curve;

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
				const std::vector<Handle(Geom2d_Curve)>& theCurves
			)
		{
			std::vector<std::shared_ptr<Edge>> edges;
			Standard_Integer nbVertices = 0;
			Standard_Integer nbEdges = 0;
			for (const auto& x : theCurves)
			{
				Debug_Null_Pointer(x);
				
				if (NOT Pln_Tools::IsBounded(x))
				{
					FatalErrorIn(FunctionSIG)
						<< "the curve is not bounded" << endl
						<< abort(FatalError);
				}

				auto P0 = x->Value(x->FirstParameter());
				auto P1 = x->Value(x->LastParameter());

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
			const Standard_Real theMinTol,
			const Standard_Real theMaxTol
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
				(Entity2d_Box(x->Coord - Pnt2d(theMaxTol, theMaxTol), x->Coord + Pnt2d(theMaxTol, theMaxTol)),
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

					if (minDis <= theMinTol)
					{
						search.RemoveFromGeometry(found);

						x->Pair = found;
						found->Pair = x;
					}
					else
					{
						search.InsertToGeometry(x);
					}
				}
			}

			if (search.Size())
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire! tree size = "<< search.Size() << endl
					<< abort(FatalError);
			}
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
				Debug_Null_Pointer(pair);

				pairdVertices.erase(pair->Index);

				auto M = MEAN(x->Coord, pair->Coord);
				auto vtx = std::make_shared<Pln_Vertex>(++nbVertices, M);
				Debug_Null_Pointer(vtx);

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

				iter++;
			}

			return std::move(vertices);
		}

		static std::vector<std::shared_ptr<Pln_Edge>>
			RetrieveEdges
			(
				const std::vector<std::shared_ptr<Edge>>& theEdges, 
				const std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>& theVertices
			)
		{
			std::vector<std::shared_ptr<Pln_Edge>> edges;
			edges.reserve(theEdges.size());

			auto apxInfo = std::make_shared<Geo_ApprxCurve_Info>();
			Debug_Null_Pointer(apxInfo);

			apxInfo->SetAngle(2.0);
			apxInfo->SetMinSize(1.0E-3);
			apxInfo->SetNbSamples(3);

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

				if (vtx0 IS_EQUAL vtx1)
				{
					auto edge = std::make_shared<Pln_Ring>(++nbEdges, vtx0);
					Debug_Null_Pointer(edge);

					edge->SetCurve(std::make_shared<Pln_Curve>(nbEdges, x->Curve));
					edge->Approx(apxInfo);
					vtx0->InsertToEdges(edge->Index(), edge);

					edges.push_back(std::move(edge));
				}
				else
				{
					auto edge = std::make_shared<Pln_Edge>(++nbEdges, vtx0, vtx1);
					Debug_Null_Pointer(edge);

					vtx0->InsertToEdges(edge->Index(), edge);
					vtx1->InsertToEdges(edge->Index(), edge);

					edge->SetCurve(std::make_shared<Pln_Curve>(nbEdges, x->Curve));
					edge->Approx(apxInfo);
					edges.push_back(std::move(edge));
				}	
			}
			return std::move(edges);
		}

		static std::pair<std::shared_ptr<Pln_Vertex>, std::shared_ptr<Pln_Edge>>
			Next
			(
				const std::shared_ptr<Pln_Vertex>& theVtx,
				const std::shared_ptr<Pln_Edge>& thePrior
			)
		{
			if (theVtx->IsRingPoint())
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire: the wire is not manifold" << endl
					<< abort(FatalError);
			}

			if (theVtx->NbEdges() NOT_EQUAL 2)
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Wire: the wire is not manifold" << endl
					<< abort(FatalError);
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

			if (edge->Vtx0() NOT_EQUAL theVtx)
			{
				auto pair = std::make_pair(edge->Vtx0(), edge);
				return std::move(pair);
			}
			else if (edge->Vtx1() NOT_EQUAL theVtx)
			{
				auto pair = std::make_pair(edge->Vtx1(), edge);
				return std::move(pair);
			}

			FatalErrorIn(FunctionSIG)
				<< "Invalid Data" << endl
				<< abort(FatalError);
			auto pair = std::make_pair(edge->Vtx0(), edge);
			return pair;
		}

		static std::vector<std::shared_ptr<Pln_Edge>>
			TrackWire
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			)
		{
			std::vector<std::shared_ptr<Pln_Edge>> edges;

			auto next = Next(theVtx, nullptr);
			edges.push_back(next.second);

			while (next.first NOT_EQUAL theVtx)
			{
				next = Next(next.first, edges[edges.size() - 1]);
				edges.push_back(next.second);
			}
			return std::move(edges);
		}
	}
}

std::vector<std::shared_ptr<tnbLib::Pln_Wire>> 
tnbLib::Pln_Tools::RetrieveWires
(
	const std::vector<Handle(Geom2d_Curve)>& theCurves,
	const Standard_Real theMinTol,
	const Standard_Real theMaxTol
)
{
	auto segments = retrieveWires::RetrieveUnMergedEdges(theCurves);
	auto unMergedVertices = retrieveWires::RetrieveUnMergedVerticesFromEdges(segments);

	retrieveWires::MergeVertices(segments, theMinTol, theMaxTol);

	auto mergedVerticesMap = retrieveWires::RetrieveMergedVertices(segments);

	auto edges = retrieveWires::RetrieveEdges(segments, mergedVerticesMap);

	Adt_AvlTree<std::shared_ptr<Pln_Vertex>>
		vertexMap;
	vertexMap.SetComparableFunction(&Pln_Vertex::IsLess);
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		vertexMap.InsertIgnoreDup(x->Vtx0());
		vertexMap.InsertIgnoreDup(x->Vtx1());
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

std::shared_ptr<tnbLib::Pln_Wire> 
tnbLib::Pln_Tools::RetrieveWire
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

		auto wire = std::make_shared<Pln_Wire>(cmpEdge);
		Debug_Null_Pointer(wire);

		return std::move(wire);
	}

	auto cmpEdge = std::make_shared<Pln_CmpEdge>();
	Debug_Null_Pointer(cmpEdge);

	cmpEdge->ChangeEdges() = retrieveWires::TrackWire(theVtx);

	SameSense(cmpEdge);

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	for (const auto& x : cmpEdge->Edges())
	{
		Debug_Null_Pointer(x);
		x->SetWire(wire);
	}

	return std::move(wire);
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

		auto indx0 = edge0->GetIndex(vtx);
		auto indx1 = edge1->GetIndex(vtx);

		if (indx0 NOT_EQUAL 1)
		{
			edge0->Reverse(Standard_True);
		}

		if (indx1 NOT_EQUAL 0)
		{
			edge1->Reverse(Standard_True);
		}

		if (edge0->Vtx1() NOT_EQUAL edge1->Vtx0())
		{
			FatalErrorIn("void tnbLib::Pln_Tools::SameSense(const std::shared_ptr<Pln_CmpEdge>& theEdge)")
				<< "Invalid CmpEdge: the two edges are not consecutive" << endl
				<< abort(FatalError);
		}

		iter++;

		edge0 = edge1;
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

	Debug_Null_Pointer(outer->BoundingBox());
	auto maxBox = *outer->BoundingBox();

	while (iter NOT_EQUAL theWires.end())
	{
		auto wire = (*iter);
		Debug_Null_Pointer(wire);

		Debug_Null_Pointer(wire->BoundingBox());
		auto box = *wire->BoundingBox();

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
		if (NOT Entity2d_Box::IsInside(*x->BoundingBox(), maxBox))
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

		if (edge->Vtx0() IS_EQUAL theVtx)
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

		if (edge->Vtx1() IS_EQUAL theVtx)
			return std::move(edge);
	}
	return nullptr;
}