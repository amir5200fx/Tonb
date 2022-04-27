#include <Aft2d_gSegmentEdge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_gCornerNode.hxx>
#include <Aft2d_gSegmentNode.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_gSegmentEdge>>
tnbLib::Aft2d_gSegmentEdge::GetTopology
(
	const Entity2d_Polygon& theChain,
	const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve
)
{
	const auto& pts = theChain.Points();
	if (pts.size() < 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid chain: a valid chain must have more than 2 points" << endl
			<< abort(FatalError);
	}

	std::vector<std::shared_ptr<Aft2d_NodeSurface>> nodes;
	nodes.reserve(pts.size());

	Standard_Integer K = 0;
	K++;
	auto n0 = std::make_shared<Aft2d_gCornerNode>(K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		K++;
		auto n = std::make_shared<Aft2d_gSegmentNode>(K, pts[K - 1]);
		Debug_Null_Pointer(n);

		n->SetCurve(theCurve);

		nodes.push_back(std::move(n));
	}

	K++;
	auto n1 = std::make_shared<Aft2d_gCornerNode>(K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_gSegmentEdge>> edges;
	edges.reserve(pts.size() - 1);

	K = 0;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes[i - 1];
		const auto& n1 = nodes[i];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_gSegmentEdge>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}

#include <Aft2d_gCornerPoleNode.hxx>
#include <Aft2d_gCornerLineNode.hxx>

template<>
void tnbLib::Aft2d_gSegmentEdge::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>& theWire,
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

		if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Invalid Wire" << endl
				<< " - distance: " << Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) << endl
				<< " - tol: " << theTol << endl
				<< abort(FatalError);
		}

		auto bn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
		auto bn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());
		Debug_Null_Pointer(bn0);
		Debug_Null_Pointer(bn1);

		if (NOT bn0->IsSingular() AND NOT bn1->IsSingular())
		{
			auto node =
				Aft2d_gCornerNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else
		{
			if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_gCornerNode>>(bn0))
			{
				if (sn->IsPole())
				{
					auto node =
						Aft2d_gCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

					e0.SetNode1(node);
					e1.SetNode0(node);
				}
				else if (sn->IsLine())
				{
					auto node =
						Aft2d_gCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
			else if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_gCornerNode>>(bn1))
			{
				if (sn->IsPole())
				{
					auto node =
						Aft2d_gCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

					e0.SetNode1(node);
					e1.SetNode0(node);
				}
				else if (sn->IsLine())
				{
					auto node =
						Aft2d_gCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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

	if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	auto bn0 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e0.Node1());
	auto bn1 = std::dynamic_pointer_cast<Aft2d_gCornerNode>(e1.Node0());
	Debug_Null_Pointer(bn0);
	Debug_Null_Pointer(bn1);

	if (NOT bn0->IsSingular() AND NOT bn1->IsSingular())
	{
		auto node =
			Aft2d_gCornerNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);
	}
	else
	{
		if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_gCornerNode>>(bn0))
		{
			if (sn->IsPole())
			{
				auto node =
					Aft2d_gCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (sn->IsLine())
			{
				auto node =
					Aft2d_gCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
		else if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_gCornerNode>>(bn1))
		{
			if (sn->IsPole())
			{
				auto node =
					Aft2d_gCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (sn->IsLine())
			{
				auto node =
					Aft2d_gCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
	}
}