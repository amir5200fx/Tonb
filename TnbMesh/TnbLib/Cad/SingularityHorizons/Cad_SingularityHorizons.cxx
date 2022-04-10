#include <Cad_SingularityHorizons.hxx>

#include <Cad_ApprxMetric.hxx>
#include <Cad_MetricCalculator.hxx>
#include <Geo_Tools.hxx>
#include <Geo2d_KnitChain.hxx>
#include <Geo2d_PolygonGraph.hxx>
#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_PolygonSegmentGraphEdge.hxx>
#include <Merge_StaticData.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Entity2d_Metric1.hxx>
#include <Entity2d_Chain.hxx>
#include <Entity_Segment.hxx>
#include <Entity_Triangle.hxx>
#include <Entity2d_Box.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Cad_SingularityHorizons::HasHorizon() const
{
	CheckDone((*this));
	return (Standard_Boolean)NbHorizons();
}

Standard_Integer 
tnbLib::Cad_SingularityHorizons::NbHorizons() const
{
	CheckDone((*this));
	Debug_Null_Pointer(theHorizons_);
	return Horizons()->NbEdges();
}

namespace tnbLib
{

	static std::pair<Pnt2d, Standard_Boolean> 
		Interpolate
		(
			const Handle(Geom_Surface)& theGeometry,
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Entity_Segment<const Pnt2d&>& theSeg,
			const Standard_Real theCriterion
		)
	{
		const auto& p0 = theSeg.P0();
		const auto& p1 = theSeg.P1();

		const auto m0 = theCalculator->CalcMetric(p0, theGeometry);
		const auto m1 = theCalculator->CalcMetric(p1, theGeometry);

		const auto det0 = m0.Determinant();
		const auto det1 = m1.Determinant();

		if (det0 > theCriterion AND det1 > theCriterion)
		{
			auto paired = std::make_pair(Pnt2d::null, Standard_False);
			return std::move(paired);
		}

		if (det0 <= theCriterion AND det1 <= theCriterion)
		{
			auto paired = std::make_pair(Pnt2d::null, Standard_False);
			return std::move(paired);
		}

		auto t = (theCriterion - det0) / (det1 - det0);
		if (t < 0)
		{
			auto paired = std::make_pair(Pnt2d::null, Standard_False);
			return std::move(paired);
		}
		if (t > 1)
		{
			auto paired = std::make_pair(Pnt2d::null, Standard_False);
			return std::move(paired);
		}

		auto coord = p0 + t * (p1 - p0);
		auto paired = std::make_pair(std::move(coord), Standard_True);
		return std::move(paired);
	}

	static std::pair<Pnt2d, Pnt2d> 
		MergePoints
		(
			const Pnt2d& p0,
			const Pnt2d& p1, 
			const Pnt2d& p2, 
			const Standard_Real theTol
		)
	{
		const auto tol2 = theTol * theTol;
		if (p0.SquareDistance(p1) > tol2)
		{
			auto paired = std::make_pair(p0, p1);
			return std::move(paired);
		}

		if (p0.SquareDistance(p2) > tol2)
		{
			auto paired = std::make_pair(p0, p2);
			return std::move(paired);
		}

		if (p1.SquareDistance(p2) > tol2)
		{
			auto paired = std::make_pair(p1, p2);
			return std::move(paired);
		}

		FatalErrorIn(FunctionSIG)
			<< "unexpected error has been detected!" << endl
			<< abort(FatalError);
		auto paired = std::make_pair(Pnt2d::null, Pnt2d::null);
		return std::move(paired);
	}

	static Standard_Integer 
		StandPoint
		(
			const Standard_Real det0, 
			const Standard_Real det1,
			const Standard_Real det2, 
			const Standard_Real theDegeneracy
		)
	{
		if (det0 <= theDegeneracy AND det1 <= theDegeneracy AND det2 <= theDegeneracy)
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid Data : " << endl
				<< " - All of the determinants of the triangle are less than the degeneracy criterion!" << endl
				<< " - d0 = " << det0 << ", d1 = " << det1 << ", d2 = " << det2 << endl
				<< " - Degeneracy criterion = " << theDegeneracy << endl
				<< abort(FatalError);
		}

		Standard_Integer gt_deg, st_deg;
		gt_deg = 0;
		st_deg = 0;
		det0 <= theDegeneracy ? st_deg++ : gt_deg++;
		det1 <= theDegeneracy ? st_deg++ : gt_deg++;
		det2 <= theDegeneracy ? st_deg++ : gt_deg++;

		if (st_deg IS_EQUAL 1)
		{
			if (det0 <= theDegeneracy) return 0;
			if (det1 <= theDegeneracy) return 1;
			if (det2 <= theDegeneracy) return 2;
		}

		if (gt_deg IS_EQUAL 1)
		{
			if (det0 > theDegeneracy) return 0;
			if (det1 > theDegeneracy) return 1;
			if (det2 > theDegeneracy) return 2;
		}

		FatalErrorIn(FunctionSIG)
			<< "Invalid Data : " << endl
			<< " - something went wrong!" << endl
			<< abort(FatalError);

		return 0;
	}

	static void
		CheckOrientation
		(
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator, 
			const Entity_Triangle<const Pnt2d&>& theTriangle,
			const Standard_Real theCriterion,
			Entity2d_Chain& theSeg
		)
	{
		const auto& p0 = theTriangle.P0();
		const auto& p1 = theTriangle.P1();
		const auto& p2 = theTriangle.P2();

		const auto m0 = theCalculator->CalcMetric(p0, theGeometry);
		const auto m1 = theCalculator->CalcMetric(p1, theGeometry);
		const auto m2 = theCalculator->CalcMetric(p2, theGeometry);

		const auto det0 = m0.Determinant();
		const auto det1 = m1.Determinant();
		const auto det2 = m2.Determinant();

		const auto& pt = theTriangle.Vertex(StandPoint(det0, det1, det2, theCriterion));

		auto& pts = theSeg.Points();
		const auto& v0 = pts[0];
		const auto& v1 = pts[1];

		if (CrossProduct(v0 - pt, v1 - pt) < 0)
		{
			std::reverse(pts.begin(), pts.end());
		}
	}

	static std::shared_ptr<Entity2d_Chain> 
		GetPathFromTriangle
		(
			const Handle(Geom_Surface)& theGeometry, 
			const std::shared_ptr<Cad_MetricCalculator>& theCalculator,
			const Entity_Triangle<const Pnt2d&>& theTriangle,
			const Standard_Real theCriterion, 
			const Standard_Real theMergeTol
		)
	{
		auto seg = std::make_shared<Entity2d_Chain>();

		std::vector<Pnt2d> pts;
		pts.reserve(3);

		{
			const auto[coord, cond] = 
				Interpolate
				(
					theGeometry, 
					theCalculator,
					theTriangle.Segment(0),
					theCriterion
				);
			if (cond)
			{
				pts.push_back(std::move(coord));
			}
		}

		{
			const auto[coord, cond] =
				Interpolate
				(
					theGeometry,
					theCalculator,
					theTriangle.Segment(1),
					theCriterion
				);
			if (cond)
			{
				pts.push_back(std::move(coord));
			}
		}

		{
			const auto[coord, cond] =
				Interpolate
				(
					theGeometry,
					theCalculator,
					theTriangle.Segment(2),
					theCriterion
				);
			if (cond)
			{
				pts.push_back(std::move(coord));
			}
		}
		
		if (pts.empty())
		{
			return nullptr;
		}

		Pnt2d Q0, Q1;
		if (pts.size() > 2)
		{
			const auto[q0, q1] = MergePoints(pts[0], pts[1], pts[2], theMergeTol);
			Q0 = std::move(q0);
			Q1 = std::move(q1);
		}
		else
		{
			Q0 = pts[0];
			Q1 = pts[1];
		}

		auto& points = seg->Points();
		points.reserve(2);

		points.push_back(std::move(Q0));
		points.push_back(std::move(Q1));

		auto& indices = seg->Connectivity();
		indices.resize(1);
		indices[0].Value(0) = 1;
		indices[0].Value(1) = 2;

		CheckOrientation(theGeometry, theCalculator, theTriangle, theCriterion, *seg);

		return std::move(seg);
	}
}

void tnbLib::Cad_SingularityHorizons::Perform()
{
	if (NOT Approximation())
	{
		FatalErrorIn(FunctionSIG)
			<< "no metric approximation has been loaded!" << endl
			<< abort(FatalError);
	}

	if (NOT Geometry())
	{
		FatalErrorIn(FunctionSIG)
			<< "no geometry has been loaded!" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Entity2d_Chain>> list;
	for (Standard_Integer tri = 0; tri < Approximation()->NbConnectivity(); tri++)
	{
		auto triangle = Geo_Tools::GetTriangle(tri, *Approximation());

		auto path = 
			GetPathFromTriangle
			(
				Geometry(), 
				MetricCalculator(),
				triangle,
				Criterion(),
				MergingTolerance()
			);

		if (path)
		{
			list.push_back(std::move(path));
		}
	}

	if (list.empty())
	{
		Change_IsDone() = Standard_True;
		return;
	}

	std::shared_ptr<Entity2d_Chain> merged;
	{ //- merging the chains
		Merge_StaticData<Entity2d_Chain> merge;
		merge.Import(list);
		merge.SetRemoveDegeneracy();

		merge.Perform();
		Debug_If_Condition_Message(NOT merge.IsDone(), "the application is not performed!");

		merged = merge.Merged();
		Debug_Null_Pointer(merged);		
	}

	list.clear();

	std::shared_ptr<Geo2d_PolygonGraph> graph;
	{
		auto knit = std::make_shared<Geo2d_KnitChain>();
		Debug_Null_Pointer(knit);

		knit->Import(*merged);
		merged.reset();

		knit->Perform();
		Debug_If_Condition_Message(NOT knit->IsDone(), "the application is not performed!");

		graph = knit->Graph();
	}

	theHorizons_ = std::move(graph);
	Change_IsDone() = Standard_True;
}

tnbLib::Entity2d_Box 
tnbLib::Cad_SingularityHorizons::RetrieveDomain
(
	const Cad_SingularityHorizons & theHorizons
)
{
	CheckDone(theHorizons);
	Debug_Null_Pointer(theHorizons.Approximation());
	Debug_Null_Pointer(theHorizons.Approximation()->BoundingBox());
	return *theHorizons.Approximation()->BoundingBox();
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>> 
tnbLib::Cad_SingularityHorizons::RetrieveHorizons
(
	const Cad_SingularityHorizons & theHorizons
)
{
	Debug_Null_Pointer(theHorizons.Horizons());
	const auto& graph = theHorizons.Horizons();

	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	polygons.reserve(theHorizons.NbHorizons());
	for (const auto& x : graph->Edges())
	{
		const auto& e = x.second;
		Debug_Null_Pointer(e);
		polygons.push_back(e->Polygon());
	}
	return std::move(polygons);
}