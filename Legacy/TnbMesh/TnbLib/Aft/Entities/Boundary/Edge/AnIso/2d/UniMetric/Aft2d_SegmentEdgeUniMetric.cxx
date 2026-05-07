#include <Aft2d_SegmentEdgeUniMetric.hxx>

#include <Aft2d_PlnCurveUniMetric.hxx>
#include <Aft2d_NodeAnIso.hxx>
#include <Aft2d_CornerNodeUniMetric.hxx>
#include <Aft2d_SegmentNodeUniMetric.hxx>
#include <Aft2d_ElementAnIso.hxx>
#include <Aft2d_CornerGapNodeUniMetric.hxx>
#include <Entity2d_Polygon.hxx>
#include <Global_Transient.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdgeUniMetric>>
tnbLib::Aft2d_SegmentEdgeUniMetric::GetTopology
(
	const Entity2d_Polygon& theChain,
	const std::shared_ptr<Aft2d_PlnCurveUniMetric>& theCurve
)
{
	const auto& pts = theChain.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid chain: a valid chain must have more than 2 points" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Aft2d_NodeAnIso>> nodes;
	nodes.reserve(pts.size());

	Standard_Integer K = 0;
	K++;
	auto n0 = std::make_shared<Aft2d_CornerNodeUniMetric>(K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		K++;
		auto n = std::make_shared<Aft2d_SegmentNodeUniMetric>(K, pts[K - 1]);
		Debug_Null_Pointer(n);

		n->SetCurve(theCurve);

		nodes.push_back(std::move(n));
	}

	K++;
	auto n1 = std::make_shared<Aft2d_CornerNodeUniMetric>(K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>> edges;
	edges.reserve(pts.size() - 1);

	K = 0;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes[i - 1];
		const auto& n1 = nodes[i];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_SegmentEdgeUniMetric>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}

template<>
void tnbLib::Aft2d_SegmentEdgeUniMetric::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_SegmentEdgeUniMetric>>& theWire,
	const Standard_Real theTol
)
{
	forThose(Index, 1, theWire.size() - 1)
	{
		Debug_Null_Pointer(theWire[Index - 1]);
		Debug_Null_Pointer(theWire[Index]);

		auto& e0 = *theWire[Index - 1];
		auto& e1 = *theWire[Index];

		if (e0.Node1() IS_EQUAL e1.Node0())
			continue;

		/*if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid Wire" << endl
				<< abort(FatalError);
		}*/

		/*const auto sn0 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e0.Node1());
		const auto sn1 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e1.Node0());

		if (sn0 AND sn1)
		{
			auto node =
				Aft2d_SegmentNode::MergeNodes(sn0, sn1, Aft2d_SegmentNode::Merge_Alg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);

			continue;
		}*/

		const auto cn0 = std::dynamic_pointer_cast<Aft2d_CornerNodeUniMetric>(e0.Node1());
		const auto cn1 = std::dynamic_pointer_cast<Aft2d_CornerNodeUniMetric>(e1.Node0());
		Debug_Null_Pointer(cn0);
		Debug_Null_Pointer(cn1);

		if (cn0->IsRegular() AND cn1->IsRegular())
		{
			auto node =
				Aft2d_CornerNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else if (cn0->IsGap() AND cn1->IsGap())
		{
			auto node =
				Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else
		{
			if (auto gn = std::dynamic_pointer_cast<Aft2d_CornerGapNodeUniMetric>(cn0))
			{
				auto node =
					Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (auto gn = std::dynamic_pointer_cast<Aft2d_CornerGapNodeUniMetric>(cn1))
			{
				auto node =
					Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data has been detected!" << endl
					<< abort(FatalError);
			}
		}
	}

	auto& e0 = *theWire[theWire.size() - 1];
	auto& e1 = *theWire[0];

	if (e0.Node1() IS_EQUAL e1.Node0())
		return;

	/*if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}*/

	/*const auto sn0 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e0.Node1());
	const auto sn1 = std::dynamic_pointer_cast<Aft2d_SegmentNode>(e1.Node0());

	if (sn0 AND sn1)
	{
		auto node =
			Aft2d_SegmentNode::MergeNodes(sn0, sn1, Aft2d_SegmentNode::Merge_Alg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);

		return;
	}*/

	const auto cn0 = std::dynamic_pointer_cast<Aft2d_CornerNodeUniMetric>(e0.Node1());
	const auto cn1 = std::dynamic_pointer_cast<Aft2d_CornerNodeUniMetric>(e1.Node0());
	Debug_Null_Pointer(cn0);
	Debug_Null_Pointer(cn1);

	if (cn0->IsRegular() AND cn1->IsRegular())
	{
		auto node =
			Aft2d_CornerNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);
	}
	else if (cn0->IsGap() AND cn1->IsGap())
	{
		auto node =
			Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);
	}
	else
	{
		if (auto gn = std::dynamic_pointer_cast<Aft2d_CornerGapNodeUniMetric>(cn0))
		{
			auto node =
				Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else if (auto gn = std::dynamic_pointer_cast<Aft2d_CornerGapNodeUniMetric>(cn1))
		{
			auto node =
				Aft2d_CornerGapNodeUniMetric::MergeNodes(cn0, cn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
	}
}