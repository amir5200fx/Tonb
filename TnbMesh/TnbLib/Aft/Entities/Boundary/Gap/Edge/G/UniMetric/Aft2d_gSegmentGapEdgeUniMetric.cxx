#include <Aft2d_gSegmentGapEdgeUniMetric.hxx>

#include <Aft2d_gCornerGapNodeUniMetric.hxx>
#include <Aft2d_gSegmentGapNodeUniMetric.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetric.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_gSegmentGapEdgeUniMetric::Contraction
(
	const Geo2d_MetricPrcsrUniMetric& thePrcsr
)
{
	if (auto n = std::dynamic_pointer_cast<Aft2d_gCornerGapNodeUniMetric>(this->Node0()))
	{
		n->BlowThisUp(thePrcsr);
	}
	else if (auto n = std::dynamic_pointer_cast<Aft2d_gCornerGapNodeUniMetric>(this->Node1()))
	{
		n->BlowThisUp(thePrcsr);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "no corner node has been found!" << endl
			<< abort(FatalError);
	}
}

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdgeUniMetric>>
tnbLib::Aft2d_gSegmentGapEdgeUniMetric::GetTopology
(
	const Entity2d_Polygon& thePoly,
	const std::shared_ptr<Aft2d_gPlnCurveSurfaceUniMetric>& theCurve
)
{
	static const Standard_Integer nbPts = 3;
	static const Standard_Integer nbEdges = nbPts - 1;
	static const Standard_Integer midPtId = 1;

	const auto& pts = thePoly.Points();
	if (pts.size() NOT_EQUAL nbPts)
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid chain has been detected" << endl
			<< abort(FatalError);
	}

	auto n0 = std::make_shared<Aft2d_gCornerGapNodeUniMetric>(1, pts.at(0));
	Debug_Null_Pointer(n0);

	n0->InsertToCurves(theCurve->Index(), theCurve);

	auto n1 = std::make_shared<Aft2d_gSegmentGapNodeUniMetric>(2, pts.at(1));
	Debug_Null_Pointer(n1);

	n1->SetCurve(theCurve);
	// fix the middle node [4/26/2022 Amir]
	n1->IsFixedRef() = Standard_True;

	auto n2 = std::make_shared<Aft2d_gCornerGapNodeUniMetric>(3, pts.at(2));
	Debug_Null_Pointer(n2);

	n2->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_gSegmentEdgeUniMetric>> edges;
	edges.reserve(nbEdges);

	{// create the first edge [4/26/2022 Amir]
		auto edge = std::make_shared<Aft2d_gSegmentGapEdgeUniMetric>(1, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}

	{// create the second edge [4/26/2022 Amir]
		auto edge = std::make_shared<Aft2d_gSegmentGapEdgeUniMetric>(2, n1, n2);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}