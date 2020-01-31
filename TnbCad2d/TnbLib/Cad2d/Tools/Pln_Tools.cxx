#include <Pln_Tools.hxx>

#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Entity2d_Triangulation.hxx>

#include <Bnd_Box2d.hxx>
#include <BndLib_Add2dCurve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_BoundedCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>

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

	auto p0 = theCurves[theCurves.size() - 2]->LastCoord();
	auto p1 = theCurves[0]->FirstCoord();

	if (p0.Distance(p1) > theMaxTol)
	{
		FatalErrorIn("std::vector<std::shared_ptr<tnbLib::Pln_Wire>> Pln_Tools::MakeWire(Args...)")
			<< "the curves are not formed a wire; max tolerance = " << theMaxTol << endl
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

	auto wire = std::make_shared<Pln_Wire>(cmpEdge);
	Debug_Null_Pointer(wire);

	return std::move(wire);
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