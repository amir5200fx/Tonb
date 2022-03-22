#include <Cad2d_Boolean.hxx>

#include <Pnt2d.hxx>
#include <Entity2d_Box.hxx>
#include <Entity2d_Chain.hxx>
#include <Geo_Tools.hxx>
#include <Pln_Curve.hxx>
#include <Pln_Wire.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Tools.hxx>
#include <Pln_CurveTools.hxx>
#include <NumAlg_AdaptiveInteg_Info.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Precision.hxx>
#include <Geom2d_Curve.hxx>

#include <Entity2d_Polygon.hxx>

namespace tnbLib
{

	//Standard_Real Cad2d_Boolean::Tolerance(1.0E-6);

	//OFstream myFile(fileName("curves.plt"));

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
			/*if (NOT domain.IsInside(pt))
				return Standard_False;*/

			const auto f = CalcCharFunOfChain(pt, domain.P0() - 0.01*domain.Diameter(), Chain);

			const auto index = Geo_Tools::Round(f);

			if (index IS_EQUAL 0) return Standard_False;
			return Standard_True;
		}

		static auto RetriveMinMaxTolerance(const Standard_Real maxTol0, const Standard_Real maxTol1, const Standard_Real tol)
		{
			auto t = std::make_pair(MAX(4.1*MAX(maxTol0, maxTol1), tol), 10.0*MAX(MAX(maxTol0, maxTol1), tol));
			return std::move(t);
		}

		static auto myInfo = std::make_shared<NumAlg_AdaptiveInteg_Info>();
		class MyInfoRunTimeConfig
		{

		public:

			MyInfoRunTimeConfig()
			{
				Init();
			}

			static void Init();
		};
		
		static auto RemoveDegeneratedCurves
		(
			std::vector<std::shared_ptr<Pln_Curve>>&& Crvs,
			const Standard_Real tol
		)
		{
			std::vector<std::shared_ptr<Pln_Curve>> curves;
			for (auto& x : Crvs)
			{
				Debug_Null_Pointer(x);
				Debug_Null_Pointer(x->Geometry());
				auto b = x->BoundingBox(0);
				auto d = b.Diameter();

				myInfo->SetTolerance(d*Precision::Confusion());
				
				auto len = Pln_Tools::Length(*x->Geometry(), myInfo);

				if (len > tol)
				{
					curves.push_back(std::move(x));
				}
			}
			return std::move(curves);
		}
	}
}

void tnbLib::boolean::MyInfoRunTimeConfig::Init()
{
	myInfo->SetMaxNbIterations(100);
	myInfo->SetNbInitIterations(4);
	myInfo->SetTolerance(1.0E-6);
}

static tnbLib::boolean::MyInfoRunTimeConfig myInfoRunTimeConfigObj;

#include <Pln_Edge.hxx>
#include <Cad_EntityManager.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PlanePlaneIntersection.hxx>
#include <Cad2d_Subdivide.hxx>

std::shared_ptr<tnbLib::Cad2d_Plane> 
tnbLib::Cad2d_Boolean::Union
(
	const std::shared_ptr<Cad2d_Plane>& thePlane0,
	const std::shared_ptr<Cad2d_Plane>& thePlane1,
	const Standard_Real theTol
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

	auto bb0 = thePlane0->BoundingBox(0);
	auto bb1 = thePlane1->BoundingBox(0);

	const auto tol = std::min(bb0.Diameter(), bb1.Diameter())*theTol;

	if (NOT bb0.IsIntersect(bb1))
	{
		return nullptr;
	}

	auto intersection = std::make_shared<Cad2d_PlanePlaneIntersection>();
	Debug_Null_Pointer(intersection);

	intersection->LoadPlane0(thePlane0);
	intersection->LoadPlane1(thePlane1);

	intersection->SetTolerance(tol);

	intersection->Perform();
	Debug_If_Condition_Message(NOT intersection->IsDone(), "the algorithm is not performed!");

	if (NOT intersection->NbEntities())
	{
		return nullptr;
	}

	auto subdivide = std::make_shared<Cad2d_Subdivide>();
	Debug_Null_Pointer(subdivide);

	subdivide->LoadIntersectionAlgorithm(intersection);

	subdivide->Perform();

	Debug_If_Condition_Message(NOT subdivide->IsDone(), "the algorithm is not performed!");

	const auto& sub0 = subdivide->ModifiedPlane0();
	const auto& sub1 = subdivide->ModifiedPlane1();

	Debug_Null_Pointer(sub0);
	Debug_Null_Pointer(sub1);

	const auto domain0 = sub0->BoundingBox(0);
	const auto domain1 = sub1->BoundingBox(0);

	const auto chain0 = sub0->MergedPolygon();
	const auto chain1 = sub1->MergedPolygon();

	Debug_Null_Pointer(sub0->Segments());
	Debug_Null_Pointer(sub1->Segments());

	auto edges0 = sub0->Segments()->RetrieveEntities();
	auto edges1 = sub1->Segments()->RetrieveEntities();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	Standard_Integer k0 = 0;
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
			curves.push_back(x->Curve());
			++k0;
		}
	}

	if (NOT k0)
	{
		return thePlane1;
	}

	Standard_Integer k1 = 0;
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
			curves.push_back(x->Curve());
			k1++;
		}
	}

	if (NOT k1)
	{
		return thePlane0;
	}

	if (curves.empty())
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)")
			<< "Contradictory data: there is no curve be created from boolean operator" << endl
			<< abort(FatalError);
	}

	auto[minTol0, maxTol0] = thePlane0->BoundTolerance();
	auto[minTol1, maxTol1] = thePlane1->BoundTolerance();

	const auto[minTol, maxTol] = boolean::RetriveMinMaxTolerance(maxTol0, maxTol1, tol);

	curves = boolean::RemoveDegeneratedCurves(std::move(curves), minTol + Precision::Confusion());

	auto wires =
		Pln_Tools::RetrieveWires
		(curves,
			minTol + Precision::Confusion(),  // the min. tolerance is set to the max. tolerance of the planes [8/4/2021 Amir]
			maxTol);

	auto outer = Pln_Tools::RetrieveOuterWire(wires);
	if (NOT outer)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)")
			<< "Failed to create outer wire!" << endl
			<< abort(FatalError);
	}

	Pln_Tools::PlaceVertices(outer);
	Pln_Tools::SetPrecision(outer);

	auto inners = std::make_shared<std::vector<std::shared_ptr<Pln_Wire>>>();
	Debug_Null_Pointer(inners);

	for (const auto& x : wires)
	{
		Debug_Null_Pointer(x);
		if (x NOT_EQUAL outer)
		{
			inners->push_back(x);

			Pln_Tools::PlaceVertices(x);
			Pln_Tools::SetPrecision(x);
		}
	}
	
	auto plane = Cad2d_Plane::MakePlane(outer, inners, thePlane0->System());
	Debug_Null_Pointer(plane);

	return std::move(plane);
}

std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>>
tnbLib::Cad2d_Boolean::Subtract
(
	const std::shared_ptr<Cad2d_Plane>& thePlane0, 
	const std::shared_ptr<Cad2d_Plane>& thePlane1,
	const Standard_Real theTol
)
{
	if (NOT thePlane0)
	{
		FatalErrorIn
		(
			"std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)"
		)
			<< "the plane 0 is not loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT thePlane1)
	{
		FatalErrorIn
		(
			"std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Union(Args...)"
		)
			<< "the plane 1 is not loaded!" << endl
			<< abort(FatalError);
	}

	auto bb0 = thePlane0->BoundingBox(0);
	auto bb1 = thePlane1->BoundingBox(0);

	const auto tol = std::min(bb0.Diameter(), bb1.Diameter())*theTol;

	if (NOT bb0.IsIntersect(bb1))
	{
		return std::vector<std::shared_ptr<Cad2d_Plane>>();
	}

	auto intersection = std::make_shared<Cad2d_PlanePlaneIntersection>();
	Debug_Null_Pointer(intersection);

	auto plane1 = 
		Cad2d_Plane::MakePlane(thePlane1->OuterWire(), nullptr, thePlane1->System());
	Debug_Null_Pointer(plane1);

	intersection->LoadPlane0(thePlane0);
	intersection->LoadPlane1(plane1);

	intersection->SetTolerance(tol);

	intersection->Perform();
	Debug_If_Condition_Message(NOT intersection->IsDone(), "the algorithm is not performed!");

	auto subdivide = std::make_shared<Cad2d_Subdivide>();
	Debug_Null_Pointer(subdivide);

	subdivide->LoadIntersectionAlgorithm(intersection);

	subdivide->Perform();

	Debug_If_Condition_Message(NOT subdivide->IsDone(), "the algorithm is not performed!");

	if (NOT intersection->NbEntities())
	{
		return std::vector<std::shared_ptr<Cad2d_Plane>>();
	}

	const auto& sub0 = subdivide->ModifiedPlane0();
	const auto& sub1 = subdivide->ModifiedPlane1();

	Debug_Null_Pointer(sub0);
	Debug_Null_Pointer(sub1);

	const auto domain0 = sub0->BoundingBox(0);
	const auto domain1 = sub1->BoundingBox(0);

	const auto chain0 = sub0->MergedPolygon();
	const auto chain1 = sub1->MergedPolygon();

	Debug_Null_Pointer(sub0->Segments());
	Debug_Null_Pointer(sub1->Segments());

	auto edges0 = sub0->Segments()->RetrieveEntities();
	auto edges1 = sub1->Segments()->RetrieveEntities();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	Standard_Integer k0 = 0;
	for (const auto& x : edges0)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			curves.push_back(x->Curve());
			continue;
		}

		if (NOT boolean::IsCurveInsidePolygon(*x->Curve(), *chain1, domain1))
		{
			curves.push_back(x->Curve());
			++k0;
		}
	}

	if (NOT k0)
	{
		return std::vector<std::shared_ptr<Cad2d_Plane>>();
	}

	Standard_Integer k1 = 0;
	for (const auto& x : edges1)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			continue;
		}

		if (boolean::IsCurveInsidePolygon(*x->Curve(), *chain0, domain0))
		{
			auto copy = x->Curve()->Geometry()->Copy();
			auto c = Handle(Geom2d_Curve)::DownCast(copy);
			Debug_Null_Pointer(c);

			c->Reverse();

			auto newPlnCurve = (*x->Curve())(std::move(c));
			curves.push_back(std::move(newPlnCurve));

			++k1;
		}
	}

	if (NOT k1)
	{
		std::vector<std::shared_ptr<Cad2d_Plane>> planes;
		planes.push_back(thePlane0);

		return std::move(planes);
	}

	auto[minTol0, maxTol0] = thePlane0->BoundTolerance();
	auto[minTol1, maxTol1] = thePlane1->BoundTolerance();

	const auto[minTol, maxTol] = boolean::RetriveMinMaxTolerance(maxTol0, maxTol1, tol);

	curves = boolean::RemoveDegeneratedCurves(std::move(curves), minTol + Precision::Confusion());

	if (curves.empty())
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Subtract(Args...)")
			<< "Contradictory data: there is no curve be created from boolean operator" << endl
			<< abort(FatalError);
	}

	auto wires = 
		Pln_Tools::RetrieveWires
		(
			curves, 
			minTol + Precision::Confusion(),  // the min. tolerance is set to the max. tolerance of the planes [8/4/2021 Amir]
			maxTol);

	for (const auto& x : wires)
	{
		Pln_Tools::PlaceVertices(x);
		Pln_Tools::SetPrecision(x);
	}

	auto planes = Pln_Tools::RetrievePlanes(wires, thePlane0->System());
	return std::move(planes);

	/*auto outer = Pln_Tools::RetrieveOuterWire(wires);
	if (NOT outer)
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Subtract(Args...)")
			<< "Failed to create outer wire!" << endl
			<< abort(FatalError);
	}

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

	return std::move(plane);*/
}

std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>>
tnbLib::Cad2d_Boolean::Intersection
(
	const std::shared_ptr<Cad2d_Plane>& thePlane0, 
	const std::shared_ptr<Cad2d_Plane>& thePlane1,
	const Standard_Real theTol
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

	auto bb0 = thePlane0->BoundingBox(0);
	auto bb1 = thePlane1->BoundingBox(0);

	const auto tol = std::min(bb0.Diameter(), bb1.Diameter())*theTol;

	if (NOT bb0.IsIntersect(bb1))
	{
		return std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>>();
	}

	auto intersection = std::make_shared<Cad2d_PlanePlaneIntersection>();
	Debug_Null_Pointer(intersection);

	intersection->LoadPlane0(thePlane0);
	intersection->LoadPlane1(thePlane1);

	intersection->SetTolerance(tol);

	intersection->Perform();
	Debug_If_Condition_Message(NOT intersection->IsDone(), "the algorithm is not performed!");

	if (NOT intersection->NbEntities())
	{
		auto c0 = thePlane0->OuterWire()->RetrieveCurves();
		auto c1 = thePlane1->OuterWire()->RetrieveCurves();

		if (Entity2d_Box::IsInside(bb0, bb1))
		{
			std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> l;
			l.push_back(thePlane0);
			return std::move(l);
		}

		if (Entity2d_Box::IsInside(bb1, bb0))
		{
			std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> l;
			l.push_back(thePlane1);
			return std::move(l);
		}

		return std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>>();
	}

	auto subdivide = std::make_shared<Cad2d_Subdivide>();
	Debug_Null_Pointer(subdivide);

	subdivide->LoadIntersectionAlgorithm(intersection);
	subdivide->Perform();

	Debug_If_Condition_Message(NOT subdivide->IsDone(), "the algorithm is not performed!");

	const auto& sub0 = subdivide->ModifiedPlane0();
	const auto& sub1 = subdivide->ModifiedPlane1();
	
	Debug_Null_Pointer(sub0);
	Debug_Null_Pointer(sub1);

	const auto domain0 = sub0->BoundingBox(0);
	const auto domain1 = sub1->BoundingBox(0);

	const auto chain0 = sub0->MergedPolygon();
	const auto chain1 = sub1->MergedPolygon();

	Debug_Null_Pointer(sub0->Segments());
	Debug_Null_Pointer(sub1->Segments());

	auto edges0 = sub0->Segments()->RetrieveEntities();
	auto edges1 = sub1->Segments()->RetrieveEntities();

	std::vector<std::shared_ptr<Pln_Curve>> curves;
	Standard_Integer k0 = 0;
	
	for (const auto& x : edges0)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			continue;
		}

		if (boolean::IsCurveInsidePolygon(*x->Curve(), *chain1, domain1))
		{
			curves.push_back(x->Curve());
			++k0;
		}
	}

	Standard_Integer k1 = 0;
	for (const auto& x : edges1)
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		if (x->Curve()->IsTangential())
		{
			continue;
		}

		if (boolean::IsCurveInsidePolygon(*x->Curve(), *chain0, domain0))
		{
			curves.push_back(x->Curve());
			++k1;
		}
	}

	if (NOT k0 AND NOT k1)
	{
		return std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>>();
	}

	if (k0 AND NOT k1)
	{
		std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> l;
		l.push_back(thePlane0);
		return std::move(l);
	}

	if (k1 AND NOT k0)
	{
		std::vector<std::shared_ptr<tnbLib::Cad2d_Plane>> l;
		l.push_back(thePlane1);
		return std::move(l);
	}

	auto[minTol0, maxTol0] = thePlane0->BoundTolerance();
	auto[minTol1, maxTol1] = thePlane1->BoundTolerance();

	const auto[minTol, maxTol] = boolean::RetriveMinMaxTolerance(maxTol0, maxTol1, tol);

	curves = boolean::RemoveDegeneratedCurves(std::move(curves), minTol + Precision::Confusion());

	/*{

		for (const auto& x : curves)
		{
			auto poly = Pln_Curve::Discretize(*x, 40);
			poly->ExportToPlt(myFile);
		}
	}*/

	/*{
		std::cout << "tolerance: " << tol << std::endl;
		std::cout << "min. tol0: " << minTol0 << ", max. tol0: " << maxTol0 << std::endl;
		std::cout << "min. tol1: " << minTol1 << ", max. tol1: " << maxTol1 << std::endl;
		std::cout << std::endl;
		std::cout << "min. tol: " << MAX(MAX(minTol0, minTol1), tol) << ", max. tol: " << 10.0*MAX(MAX(maxTol0, maxTol1), tol) << std::endl;
		std::cout << std::endl;
	}*/
	if (curves.empty())
	{
		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Intersection(Args...)")
			<< "Contradictory data: there is no curve be created from boolean operator" << endl
			<< abort(FatalError);
	}
	
	auto wires =
		Pln_Tools::RetrieveWires
		(
			curves, 
			minTol + Precision::Confusion(),  // the min. tolerance is set to the max. tolerance of the planes [8/4/2021 Amir]
			maxTol);

	for (const auto& x : wires)
	{
		Pln_Tools::PlaceVertices(x);
		Pln_Tools::SetPrecision(x);
	}

	auto planes = Pln_Tools::RetrievePlanes(wires, thePlane0->System());
	return std::move(planes);

	/*auto outer = Pln_Tools::RetrieveOuterWire(wires);
	if (NOT outer)
	{
		fileName myName("out1.plt");
		OFstream myFile(myName);

		thePlane0->ExportToPlt(myFile);
		thePlane1->ExportToPlt(myFile);

		for (const auto& x : curves)
		{
			Pln_CurveTools::ExportToPlt(x->Geometry(), myFile);
		}

		FatalErrorIn("std::shared_ptr<tnbLib::Cad2d_Plane> Cad2d_Boolean::Intersection(Args...)")
			<< "Failed to create outer wire!" << endl
			<< abort(FatalError);
	}

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

	return std::move(plane);*/
}