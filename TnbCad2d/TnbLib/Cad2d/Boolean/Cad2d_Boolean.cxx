#include <Cad2d_Boolean.hxx>

#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Curve.hxx>

namespace tnbLib
{

	Standard_Real Cad2d_Boolean::Tolerance(1.0E-6);

	namespace boolean
	{

		static Standard_Real CalcBeta
		(
			const Pnt2d& thePt, 
			const Pnt2d& O, 
			const Pnt2d& P1, 
			const Pnt2d& P2, 
			const Standard_Real theTol
		)
		{
			if (Geo_Tools::Oriented_cgal(O, P1, P2) >= 0.0)
			{
				if (NOT Geo_Tools::IsPointInsideTriangle_cgal(thePt, O, P1, P2))
				{
					return 0;
				}
				else
				{
					if (Geo_Tools::Distance_cgal(thePt, O, P1) <= theTol)
						return 0.5;
					if (Geo_Tools::Distance_cgal(thePt, O, P2) <= theTol)
						return 0.5;
					if (Geo_Tools::Distance_cgal(thePt, P1, P2) <= theTol)
						return 0.5;
					return 1.0;
				}
			}
			else
			{
				if (NOT Geo_Tools::IsPointInsideTriangleCW_cgal(thePt, O, P1, P2))
				{
					return 0;
				}
				else
				{
					if (Geo_Tools::Distance_cgal(thePt, O, P1) <= theTol)
						return -0.5;
					if (Geo_Tools::Distance_cgal(thePt, O, P2) <= theTol)
						return -0.5;
					if (Geo_Tools::Distance_cgal(thePt, P1, P2) <= theTol)
						return -0.5;
					return -1.0;
				}
			}
		}

		static Standard_Real CalcCharFunOfChain
		(
			const Pnt2d& thePt, 
			const Pnt2d& O,
			const Entity2d_Chain& Chain
		)
		{
			const auto& pts = Chain.Points();
			const auto& edges = Chain.Connectivity();

			Standard_Real f = 0;

			const auto tol = Precision::Confusion();
			for (const auto& x : edges)
			{
				const auto v0 = x.Value(0) - 1;
				const auto v1 = x.Value(1) - 1;

				f += CalcBeta(thePt, O, pts[v0], pts[v1], tol);
			}
			return f;
		}

		static Standard_Boolean IsCurveInsidePolygon
		(
			const Pln_Curve& theCurve,
			const Entity2d_Chain& Chain,
			const Entity2d_Box& domain
		)
		{
			const auto pt = theCurve.Value_normParam(0.5);
			if (NOT domain.IsInside(pt))
				return Standard_False;

			const auto f = CalcCharFunOfChain(pt, domain.P0() - 0.01*domain.Diameter(), Chain);

			const auto index = Geo_Tools::Round(f);

			if (index IS_EQUAL 0) return Standard_False;
			return Standard_True;
		}


		
	}
}

#include <Pln_Edge.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PlanePlaneIntersection.hxx>
#include <Cad2d_Subdivide.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Boolean::Union
(
	const std::shared_ptr<Cad2d_Plane>& thePlane0,
	const std::shared_ptr<Cad2d_Plane>& thePlane1
)
{
	if (NOT thePlane0)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)")
			<< "the plane 0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT thePlane1)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)")
			<< "the plane 1 is not loaded!" << endl
			<< abort(FatalError);
	}

	auto intersection = std::make_shared<Cad2d_PlanePlaneIntersection>();
	Debug_Null_Pointer(intersection);

	intersection->LoadPlane0(thePlane0);
	intersection->LoadPlane1(thePlane1);

	intersection->SetTolerance(Tolerance);

	intersection->Perform();
	Debug_If_Condition_Message(NOT intersection->IsDone(), "the algorithm is not performed!");

	auto subdivide = std::make_shared<Cad2d_Subdivide>();
	Debug_Null_Pointer(subdivide);

	subdivide->LoadIntersectionAlgorithm(intersection);

	subdivide->Perform();

	Debug_If_Condition_Message(NOT subdivide->IsDone(), "the algorithm is not performed!");

	const auto& sub0 = subdivide->ModifiedPlane0();
	const auto& sub1 = subdivide->ModifiedPlane1();

	Debug_Null_Pointer(sub0);
	Debug_Null_Pointer(sub1);

	const auto& domain0 = sub0->BoundingBox();
	const auto& domain1 = sub1->BoundingBox();

	const auto chain0 = sub0->MergedPolygon();
	const auto chain1 = sub1->MergedPolygon();

	Debug_Null_Pointer(sub0->Segments());
	Debug_Null_Pointer(sub1->Segments());

	auto edges0 = sub0->Segments()->RetrieveEntities();
	auto edges1 = sub1->Segments()->RetrieveEntities();

	std::vector<Handle(Geom2d_Curve)> curves;
	for (const auto& x : edges0)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			continue;
		}

		if (NOT boolean::IsCurveInsidePolygon(*x->Curve(), *chain1, domain1))
		{
			curves.push_back(x->Curve()->Geometry());
		}
	}

	for (const auto& x : edges1)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			continue;
		}

		if (NOT boolean::IsCurveInsidePolygon(*x->Curve(), *chain0, domain0))
		{
			curves.push_back(x->Curve()->Geometry());
		}
	}

	auto[minTol0, maxTol0] = thePlane0->BoundTolerance();
	auto[minTol1, maxTol1] = thePlane0->BoundTolerance();

	auto wires = Pln_Tools::RetrieveWires(curves, MAX(MAX(minTol0, minTol1), Tolerance), 10.0*MAX(MAX(maxTol0, maxTol1), Tolerance));

	auto outer = Pln_Tools::RetrieveOuterWire(wires);
	auto inners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
	Debug_Null_Pointer(inners);

	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		if (x NOT_EQUAL outer)
		{
			inners->push_back(x);
		}
	}
	
	auto plane = Cad2d_Plane::MakePlane(outer, inners, thePlane0->System());
	Debug_Null_Pointer(plane);

	return std::move(plane);
}