#include <Aft2d_tSegmentPoleEdge.hxx>

#include <Aft2d_tCornerPoleNode.hxx>
#include <Aft2d_tSegmentPoleNode.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Aft2d_ElementSurface.hxx>
#include <Entity2d_Polygon.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
Standard_Boolean
tnbLib::Aft2d_tSegmentPoleEdge::SingularityContraction
(
	const Geo2d_MetricPrcsrAnIso& thePrcsr
)
{
	auto n0 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(this->Node0());
	auto n1 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(this->Node1());
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	if (n0->IsCorner() AND NOT n0->IsRegular())
	{
		auto edge = n0->BlowThisUp();
		Debug_Null_Pointer(edge);

		const auto& v0 = edge->Node0();
		const auto& v1 = edge->Node1();

		Debug_Null_Pointer(v0);
		Debug_Null_Pointer(v1);

		edge->SetCharLength(thePrcsr.CalcDistance(v0->Coord(), v1->Coord()));
		edge->SetCentre(thePrcsr.CalcCentre(v0->Coord(), v1->Coord()));
	}

	if (n1->IsCorner() AND NOT n1->IsRegular())
	{
		auto edge = n1->BlowThisUp();
		Debug_Null_Pointer(edge);

		const auto& v0 = edge->Node0();
		const auto& v1 = edge->Node1();

		Debug_Null_Pointer(v0);
		Debug_Null_Pointer(v1);

		edge->SetCharLength(thePrcsr.CalcDistance(v0->Coord(), v1->Coord()));
		edge->SetCentre(thePrcsr.CalcCentre(v0->Coord(), v1->Coord()));
	}

	/*if (auto n = std::dynamic_pointer_cast<Aft2d_gCornerPoleNode>(this->Node0()))
	{
		n->RemoveThis(thePrcsr);
	}
	else if (auto n = std::dynamic_pointer_cast<Aft2d_gCornerPoleNode>(this->Node1()))
	{
		n->RemoveThis(thePrcsr);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "no corner node has been found!" << endl
			<< abort(FatalError);
	}*/
	return Standard_True;
}

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Aft2d_tSegmentPoleEdge::GetTopology
(
	const Entity2d_Polygon& thePoly,
	const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve
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

	auto n0 = std::make_shared<Aft2d_tCornerPoleNode>(1, pts.at(0));
	Debug_Null_Pointer(n0);

	n0->InsertToCurves(theCurve->Index(), theCurve);

	auto n1 = std::make_shared<Aft2d_tSegmentPoleNode>(2, pts.at(1));
	Debug_Null_Pointer(n1);

	n1->SetCurve(theCurve);
	// fix the middle node [4/26/2022 Amir]
	n1->IsFixedRef() = Standard_True;

	auto n2 = std::make_shared<Aft2d_tCornerPoleNode>(3, pts.at(2));
	Debug_Null_Pointer(n2);

	n2->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_tSegmentEdge>> edges;
	edges.reserve(nbEdges);

	{// create the first edge [4/26/2022 Amir]
		auto edge = std::make_shared<Aft2d_tSegmentPoleEdge>(1, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}

	{// create the second edge [4/26/2022 Amir]
		auto edge = std::make_shared<Aft2d_tSegmentPoleEdge>(2, n1, n2);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}