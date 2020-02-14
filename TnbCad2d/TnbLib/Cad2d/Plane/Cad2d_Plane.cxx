#include <Cad2d_Plane.hxx>

#include <Geo_Tools.hxx>
#include <Cad_BlockEntity.hxx>
#include <Cad_EntityManager.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <Cad2d_Plane_Info.hxx>

#include <gp_Ax2.hxx>

Standard_Integer 
tnbLib::Cad2d_Plane_Manager::NbCorners() const
{
	Debug_Null_Pointer(theVertices_);
	return (Standard_Integer)theVertices_->Size();
}

Standard_Integer 
tnbLib::Cad2d_Plane_Manager::NbSegments() const
{
	Debug_Null_Pointer(theEdges_);
	return (Standard_Integer)theEdges_->Size();
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
			<< "Wrong orientation of the outer wire!" << endl
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

//- Constructors

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const gp_Ax2 & theSystem
)
	: theSystem_(theSystem)
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex, 
	const gp_Ax2 & theSystem
)
	: Pln_Entity(theIndex)
	, theSystem_(theSystem)
{
}

tnbLib::Cad2d_Plane::Cad2d_Plane
(
	const Standard_Integer theIndex, 
	const word & theName, 
	const gp_Ax2 & theSystem
)
	: Pln_Entity(theIndex, theName)
	, theSystem_(theSystem)
{
}

//*******************************************

Standard_Integer 
tnbLib::Cad2d_Plane::NbHoles() const
{
	if (NOT theInner_) return 0;
	return (Standard_Integer)theInner_->size();
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

std::shared_ptr<tnbLib::Entity2d_Chain> 
tnbLib::Cad2d_Plane::Polygon() const
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> poly;

	auto edges = Segments()->RetrieveEntities();
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		
		if (x->Mesh())
		{
			poly.push_back(x->Mesh());
		}
	}

	if (edges.empty())
	{
		return nullptr;
	}

	auto chain = Geo_Tools::RetrieveChain(poly);
	return std::move(chain);
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

	auto c2 = std::make_shared<Pln_Curve>(g2);
	Debug_Null_Pointer(c2);

	auto c3 = std::make_shared<Pln_Curve>(g3);
	Debug_Null_Pointer(c3);

	auto c4 = std::make_shared<Pln_Curve>(g4);
	Debug_Null_Pointer(c4);

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