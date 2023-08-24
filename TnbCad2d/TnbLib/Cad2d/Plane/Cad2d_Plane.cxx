#include <Cad2d_Plane.hxx>

#include <Entity2d_Box.hxx>
#include <Entity2d_Polygon.hxx>
#include <Entity2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <Cad_BlockEntity.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_Plane_Info.hxx>

#include <Geom2d_Curve.hxx>
#include <gp.hxx>
#include <gp_Ax2.hxx>
#include <gp_Trsf2d.hxx>

void tnbLib::Cad2d_Plane::SetOuter
(
	const outer && theOuter
)
{
	theOuter_ = std::move(theOuter);
}

void tnbLib::Cad2d_Plane::SetInner
(
	const inner && theInner
)
{
	theInner_ = std::move(theInner);
}

std::shared_ptr<tnbLib::Entity2d_Box> 
tnbLib::Cad2d_Plane::CalcBoundingBox
(
	const Standard_Real theTol
) const
{
	Debug_Null_Pointer(OuterWire());
	auto b = std::make_shared<Entity2d_Box>(OuterWire()->BoundingBox());
	return std::move(b);
}

namespace tnbLib
{

	std::vector<std::shared_ptr<Pln_Edge>>
		RetrieveEdges
		(
			const std::shared_ptr<Pln_Wire> & theOuter,
			const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>> & theInners
		)
	{
		auto edges = theOuter->Edges();
		if (theInners)
		{
			for (const auto& wire : *theInners)
			{
				Debug_Null_Pointer(wire);

				for (const auto& x : wire->Edges())
				{
					Debug_Null_Pointer(x);
					edges.push_back(x);
				}
			}
		}
		return std::move(edges);
	}
}

void tnbLib::Cad2d_Plane::Make
(
	const outer & theOuter, 
	const inner & theInners
)
{
	CheckOuter(theOuter, "void tnbLib::Cad2d_Plane::Make(Args...)");
	
	if (theInners)
	{
		CheckInners(theInners, "void tnbLib::Cad2d_Plane::Make(Args...)");
	}

	theOuter_ = theOuter;

	if (theInners)
	{
		theInner_ = theInners;
	}

	auto edges = RetrieveEdges(theOuter, theInners);

	auto vertices = Pln_Tools::RetrieveVertices(edges);
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		x->SetPrecision(Pln_Tools::CalcPrecision(*x));
	}
	
	auto edgeBlock = 
		std::make_shared<Cad_BlockEntity<Pln_Edge>>("Default Block Edge", edges);
	Debug_Null_Pointer(edgeBlock);

	ChangeSegments() = 
		std::make_shared<Cad_EntityManager<Pln_Edge>>(edgeBlock->Name(), edgeBlock);
	Debug_Null_Pointer(Segments());

	auto vertexBlock =
		std::make_shared<Cad_BlockEntity<Pln_Vertex>>("Default Block Vertex", vertices);
	Debug_Null_Pointer(vertexBlock);

	ChangeCorners() = 
		std::make_shared<Cad_EntityManager<Pln_Vertex>>(vertexBlock->Name(), vertexBlock);
	Debug_Null_Pointer(Corners());

	const auto plane = std::dynamic_pointer_cast<Cad2d_Plane>(This());
	theOuter->SetPlane(plane);
	if (theInners)
	{
		for (const auto& x : *theInners)
		{
			x->SetPlane(plane);
		}
	}

	auto b = CalcBoundingBox(0);
	Debug_Null_Pointer(b);

	SetBoundingBox(std::move(b));
}

void tnbLib::Cad2d_Plane::Make
(
	const outer && theOuter,
	const inner && theInners
)
{
	SetOuter(std::move(theOuter));

	if (theInners)
	{
		SetInner(std::move(theInners));
	}

	CheckOuter(OuterWire(), "void tnbLib::Cad2d_Plane::Make(Args...)");

	if (InnerWires())
	{
		CheckInners(InnerWires(), "void tnbLib::Cad2d_Plane::Make(Args...)");
	}

	auto edges = RetrieveEdges(OuterWire(), InnerWires());

	auto vertices = Pln_Tools::RetrieveVertices(edges);

	auto edgeBlock =
		std::make_shared<Cad_BlockEntity<Pln_Edge>>("Default Block Edge", edges);
	Debug_Null_Pointer(edgeBlock);

	ChangeSegments() =
		std::make_shared<Cad_EntityManager<Pln_Edge>>(edgeBlock->Name(), edgeBlock);
	Debug_Null_Pointer(Segments());

	auto vertexBlock =
		std::make_shared<Cad_BlockEntity<Pln_Vertex>>("Default Block Vertex", vertices);
	Debug_Null_Pointer(vertexBlock);

	ChangeCorners() =
		std::make_shared<Cad_EntityManager<Pln_Vertex>>(vertexBlock->Name(), vertexBlock);
	Debug_Null_Pointer(Corners());

	const auto plane = std::dynamic_pointer_cast<Cad2d_Plane>(This());
	OuterWire()->SetPlane(plane);
	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			x->SetPlane(plane);
		}
	}

	auto b = CalcBoundingBox(0);
	Debug_Null_Pointer(b);

	SetBoundingBox(std::move(b));
}

void tnbLib::Cad2d_Plane::CheckOuter
(
	const outer & theOuter,
	const char* theName
)
{
	if (NOT theOuter)
	{
		FatalErrorIn(theName) << endl
			<< "no outer wire has been loaded!" << endl
			<< abort(FatalError);
	}

	if (theOuter->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CCW)
	{
		FatalErrorIn(theName) << endl
			<< "Wrong orientation of the outer wire!" << " orientation code = " 
			<< (int)theOuter->Orientation() << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_Plane::CheckInner
(
	const std::shared_ptr<Pln_Wire> & theInner,
	const char * theName
)
{
	if (NOT theInner)
	{
		FatalErrorIn(theName) << endl
			<< "null inner wire!" << endl
			<< abort(FatalError);
	}

	if (theInner->Orientation() NOT_EQUAL Pln_Orientation::Pln_Orientation_CW)
	{
		FatalErrorIn(theName) << endl
			<< "Wrong orientation of the outer wire!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_Plane::CheckInners
(
	const inner & theInner,
	const char * theName
)
{
	for (const auto& x : *theInner)
	{
		CheckInner(x, theName);
	}
}

const std::string tnbLib::Cad2d_Plane::extension = ".plane";

//- Constructors

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const gp_Ax2 & theSystem
)
	: cad2dLib::Plane_Auxillary(theSystem)
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const gp_Ax2 && theSystem
)
	: cad2dLib::Plane_Auxillary(std::move(theSystem))
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex, 
	const gp_Ax2 & theSystem
)
	: Pln_Entity(theIndex)
	, cad2dLib::Plane_Auxillary(theSystem)
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex,
	const gp_Ax2 && theSystem
)
	: Pln_Entity(theIndex)
	, cad2dLib::Plane_Auxillary(std::move(theSystem))
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const gp_Ax2 & theSystem
)
	: Pln_Entity(theIndex, theName)
	, cad2dLib::Plane_Auxillary(theSystem)
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex,
	const word & theName,
	const gp_Ax2 && theSystem
)
	: Pln_Entity(theIndex, theName)
	, cad2dLib::Plane_Auxillary(std::move(theSystem))
{
}

//*******************************************

Standard_Integer 
tnbLib::Cad2d_Plane::NbWires() const
{
	Debug_Null_Pointer(OuterWire());
	return NbHoles() + 1;
}

Standard_Integer 
tnbLib::Cad2d_Plane::NbHoles() const
{
	if (NOT theInner_) return 0;
	return (Standard_Integer)theInner_->size();
}

Standard_Integer 
tnbLib::Cad2d_Plane::NbEntities
(
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
		return NbCorners();
	if (t IS_EQUAL Pln_EntityType::EDGE)
		return NbSegments();
	if (t IS_EQUAL Pln_EntityType::WIRE)
		return NbWires();
	if (t IS_EQUAL Pln_EntityType::PLANE)
		return 1;
	return 0;
}

Standard_Boolean 
tnbLib::Cad2d_Plane::IsOrphan() const
{
	return Standard_True;
}

std::tuple<Standard_Real, Standard_Real> 
tnbLib::Cad2d_Plane::BoundTolerance() const
{
	Debug_Null_Pointer(OuterWire());
	auto[minTol, maxTol] = OuterWire()->BoundTolerance();

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			auto[t0, t1] = x->BoundTolerance();

			if (minTol > t0)
				minTol = t0;
			if (maxTol < t1)
				maxTol = t1;
		}
	}
	auto t = std::make_tuple(minTol, maxTol);
	return std::move(t);
}

std::shared_ptr<tnbLib::Pln_Entity> 
tnbLib::Cad2d_Plane::Copy() const
{
	auto ow = std::dynamic_pointer_cast<Pln_Wire>(OuterWire()->Copy());
	Debug_Null_Pointer(ow);

	if (InnerWires())
	{
		auto iw = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);

			auto w = std::dynamic_pointer_cast<Pln_Wire>(x->Copy());
			Debug_Null_Pointer(w);

			iw->push_back(std::move(w));
		}

		auto plane = Cad2d_Plane::MakePlane(ow, iw, System());
		Debug_Null_Pointer(plane);

		plane->SetIndex(Index());
		plane->SetName(Name());

		return std::move(plane);
	}

	auto plane = Cad2d_Plane::MakePlane(ow, nullptr, System());
	Debug_Null_Pointer(plane);

	plane->SetIndex(Index());
	plane->SetName(Name());

	return std::move(plane);
}

tnbLib::Pln_EntityType 
tnbLib::Cad2d_Plane::Type() const
{
	return Pln_EntityType::PLANE;
}

void tnbLib::Cad2d_Plane::Approx
(
	const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
) const
{
	auto edges = Segments()->RetrieveEntities();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Approx(theInfo);
	}
}

void tnbLib::Cad2d_Plane::Transform
(
	const gp_Trsf2d & t
)
{
	if (OuterWire())
		OuterWire()->ForcedTransform(t);

	if (InnerWires())
	{
		for (const auto& x : *InnerWires())
		{
			Debug_Null_Pointer(x);
			x->ForcedTransform(t);
		}
	}

	auto b = CalcBoundingBox(0);
	Debug_Null_Pointer(b);

	SetBoundingBox(std::move(b));
}

void tnbLib::Cad2d_Plane::RetrieveWiresTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theWires
) const
{
	Debug_Null_Pointer(OuterWire());
	theWires.reserve(NbWires());

	theWires.push_back(OuterWire());
	if (InnerWires())
	{
		const auto& inners = *InnerWires();
		for (const auto& x : inners)
		{
			theWires.push_back(x);
		}
	}
}

void tnbLib::Cad2d_Plane::RetrieveEntitiesTo
(
	std::vector<std::shared_ptr<Pln_Entity>>& theEntities,
	const Pln_EntityType t
) const
{
	if (t IS_EQUAL Pln_EntityType::VERTEX)
	{
		RetrieveCornersTo(theEntities);
	}

	if (t IS_EQUAL Pln_EntityType::EDGE)
	{
		RetrieveSegmentsTo(theEntities);
	}

	if (t IS_EQUAL Pln_EntityType::WIRE)
	{
		RetrieveWiresTo(theEntities);
	}

	if (t IS_EQUAL Pln_EntityType::PLANE)
	{
		theEntities.push_back(std::dynamic_pointer_cast<Pln_Entity>(This()));
	}
}

//std::shared_ptr<tnbLib::Entity2d_Chain> 
//tnbLib::Cad2d_Plane::Polygon() const
//{
//	std::vector<std::shared_ptr<Entity2d_Polygon>> poly;
//
//	auto edges = Segments()->RetrieveEntities();
//	for (const auto& x : edges)
//	{
//		Debug_Null_Pointer(x);
//		
//		if (x->Mesh())
//		{
//			poly.push_back(x->Mesh());
//		}
//	}
//
//	if (edges.empty())
//	{
//		return nullptr;
//	}
//
//	auto chain = Geo_Tools::RetrieveChain(poly);
//	return std::move(chain);
//}

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Cad2d_Plane::MergedPolygon() const
{
	auto chain = std::make_shared<Entity2d_Chain>();
	Debug_Null_Pointer(chain);

	Debug_Null_Pointer(OuterWire());
	const auto& outer = *OuterWire();
	const auto& poly = outer.Polygon();

	auto& pts = chain->Points();
	auto& indices = chain->Connectivity();

	Standard_Integer nbPts = 0;
	for (const auto& x : poly->Points())
	{
		auto v0 = nbPts;
		auto v1 = (v0 + 1) % poly->NbPoints();

		connectivity::dual id;
		id.Value(0) = v0 + 1;
		id.Value(1) = v1 + 1;

		indices.push_back(std::move(id));

		pts.push_back(x);

		nbPts++;
	}

	if (InnerWires())
	{
		for (const auto& w : *InnerWires())
		{
			Debug_Null_Pointer(w);

			const auto& poly = w->Polygon();

			Standard_Integer K = 0;
			for (const auto& x : poly->Points())
			{
				auto v0 = K;
				auto v1 = (v0 + 1) % poly->NbPoints();

				connectivity::dual id;
				id.Value(0) = v0 + nbPts + 1;
				id.Value(1) = v1 + nbPts + 1;

				indices.push_back(std::move(id));

				pts.push_back(x);

				K++;
			}

			nbPts += poly->NbPoints();
		}
	}
	return std::move(chain);
}

tnbLib::Entity2d_Box 
tnbLib::Cad2d_Plane::BoundingBox
(
	const Standard_Real Tol
) const
{
	Debug_Null_Pointer(BoundingBox());
	auto b = *BoundingBox();
	if (Tol > 0)
	{
		b.Expand(Tol);
	}
	return std::move(b);
}

const typename tnbLib::Cad2d_Plane::outer&
tnbLib::Cad2d_Plane::OuterWire() const
{
	return theOuter_;
}

const typename tnbLib::Cad2d_Plane::inner& 
tnbLib::Cad2d_Plane::InnerWires() const
{
	return theInner_;
}

//- Static functions

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakePlane
(
	const std::shared_ptr<Pln_Wire>& theOuter, 
	const std::shared_ptr<std::vector<std::shared_ptr<Pln_Wire>>>& theInners, 
	const gp_Ax2 & theSystem
)
{
	auto plane = std::make_shared<Cad2d_Plane>(theSystem);
	Debug_Null_Pointer(plane);

	plane->Make(theOuter, theInners);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeBox
(
	const Pnt2d & theCorner,
	const Standard_Real theDx, 
	const Standard_Real theDy,
	const gp_Ax2 & theSystem
)
{
	auto plane = 
		MakeBox
		(
			theCorner, theCorner + Pnt2d(theDx, theDy), 
			theSystem
		);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeBox
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1, 
	const gp_Ax2& theSystem
)
{
	const auto& P0 = theP0;
	const auto P1 = Pnt2d(theP1.X(), theP0.Y());
	const auto& P2 = theP1;
	const auto P3 = Pnt2d(theP0.X(), theP1.Y());

	const auto g1 = Pln_CurveTools::MakeSegment(P0, P1);
	Debug_Null_Pointer(g1);

	const auto g2 = Pln_CurveTools::MakeSegment(P1, P2);
	Debug_Null_Pointer(g2);

	const auto g3 = Pln_CurveTools::MakeSegment(P2, P3);
	Debug_Null_Pointer(g3);

	const auto g4 = Pln_CurveTools::MakeSegment(P3, P0);
	Debug_Null_Pointer(g4);

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(4);

	auto c1 = std::make_shared<Pln_Curve>(g1);
	Debug_Null_Pointer(c1);
	c1->SetIndex(1);
	c1->SetName("bottom");

	auto c2 = std::make_shared<Pln_Curve>(g2);
	Debug_Null_Pointer(c2);
	c2->SetIndex(2);
	c2->SetName("right");

	auto c3 = std::make_shared<Pln_Curve>(g3);
	Debug_Null_Pointer(c3);
	c3->SetIndex(3);
	c3->SetName("top");

	auto c4 = std::make_shared<Pln_Curve>(g4);
	Debug_Null_Pointer(c4);
	c4->SetIndex(4);
	c4->SetName("left");

	curves.push_back(std::move(c1));
	curves.push_back(std::move(c2));
	curves.push_back(std::move(c3));
	curves.push_back(std::move(c4));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);
	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeBox
(
	const gp_Ax2d & theAx, 
	const Standard_Real theDx, 
	const Standard_Real theDy, 
	const gp_Ax2 & theSystem
)
{
	const auto& loc = theAx.Location();
	auto pln = MakeBox(gp::Origin2d(), theDx, theDy, theSystem);

	gp_Trsf2d t;
	t.SetTransformation(gp::OX2d(), theAx);
	pln->Transform(t.Inverted());
	return std::move(pln);
}

#include <Pln_CurveTools.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeCircle
(
	const gp_Circ2d & C,
	const gp_Ax2& theSystem
)
{
	const auto g = Pln_CurveTools::MakeCircle(C);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeCircle
(
	const gp_Circ2d & C,
	const Pnt2d & theP,
	const gp_Ax2 & theSystem
)
{
	const auto g = Pln_CurveTools::MakeCircle(C, theP);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeCircle
(
	const Pnt2d & theP0, 
	const Pnt2d & theP1,
	const Pnt2d & theP2,
	const gp_Ax2 & theSystem
)
{
	const auto g = Pln_CurveTools::MakeCircle(theP0, theP1, theP2);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeCircle
(
	const Pnt2d & theC,
	const Standard_Real theRadius, 
	const gp_Ax2 & theSystem
)
{
	const auto g = Pln_CurveTools::MakeCircle(theC, theRadius);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane>
tnbLib::Cad2d_Plane::MakeCircle
(
	const Pnt2d & theC, 
	const Pnt2d & theP, 
	const gp_Ax2 & theSystem
)
{
	const auto g = Pln_CurveTools::MakeCircle(theC, theP);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeEllipse
(
	const gp_Elips2d & E,
	const gp_Ax2& theSystem
)
{
	const auto g = Pln_CurveTools::MakeEllipse(E);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Plane::MakeEllipse
(
	const Pnt2d & theS0, 
	const Pnt2d & theS1,
	const Pnt2d & theCenter,
	const gp_Ax2 & theSystem
)
{
	const auto g = Pln_CurveTools::MakeEllipse(theS0, theS1, theCenter);
	Debug_Null_Pointer(g);

	auto trimmed = Pln_CurveTools::Trim(g, g->FirstParameter(), g->LastParameter());

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	curves.reserve(1);

	auto c1 = std::make_shared<Pln_Curve>(std::move(trimmed));
	curves.push_back(std::move(c1));

	auto wire = Pln_Tools::MakeWire(curves, 1.0E-6);
	Debug_Null_Pointer(wire);

	auto plane = Cad2d_Plane::MakePlane(wire, nullptr, theSystem);
	Debug_Null_Pointer(plane);

	return std::move(plane);
}