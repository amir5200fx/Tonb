#include <Aft2d_tSegmentEdge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>
#include <Aft2d_NodeSurface.hxx>
#include <Aft2d_tCornerNode.hxx>
#include <Aft2d_tSegmentNode.hxx>
#include <Aft2d_tCornerGapNode.hxx>
#include <Aft2d_tSegmentGapNode.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::vector<std::shared_ptr<tnbLib::Aft2d_tSegmentEdge>>
tnbLib::Aft2d_tSegmentEdge::GetTopology
(
	const Entity2d_Polygon& theChain,
	const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve
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
	auto n0 = std::make_shared<Aft2d_tCornerNode>(K, pts[K - 1]);
	nodes.push_back(n0);
	n0->InsertToCurves(theCurve->Index(), theCurve);

	forThose(Index, 1, pts.size() - 2)
	{
		K++;
		auto n = std::make_shared<Aft2d_tSegmentNode>(K, pts[K - 1]);
		Debug_Null_Pointer(n);

		n->SetCurve(theCurve);

		nodes.push_back(std::move(n));
	}

	K++;
	auto n1 = std::make_shared<Aft2d_tCornerNode>(K, pts[K - 1]);
	nodes.push_back(n1);
	n1->InsertToCurves(theCurve->Index(), theCurve);

	std::vector<std::shared_ptr<Aft2d_tSegmentEdge>> edges;
	edges.reserve(pts.size() - 1);

	K = 0;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& n0 = nodes[i - 1];
		const auto& n1 = nodes[i];

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);

		auto edge = std::make_shared<Aft2d_tSegmentEdge>(++K, n0, n1);
		Debug_Null_Pointer(edge);

		edge->SetCurve(theCurve);

		edges.push_back(std::move(edge));
	}
	return std::move(edges);
}

#include <Aft2d_tCornerPoleNode.hxx>
#include <Aft2d_tCornerLineNode.hxx>

template<>
void tnbLib::Aft2d_tSegmentEdge::MergeDangles
(
	const std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>& theWire,
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

		//		if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
		//		{
		//#ifdef _DEBUG
		//			meshLib::ExportInvalidWireAtMergeDangles(theWire);
		//#endif // _DEBUG
		//
		//			FatalErrorIn(FunctionSIG) << endl
		//				<< "Invalid Wire" << endl
		//				<< " - distance: " << Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) << endl
		//				<< " - tol: " << theTol << endl
		//				<< abort(FatalError);
		//		}

		auto bn0 = std::dynamic_pointer_cast<Aft2d_tCornerNode>(e0.Node1());
		auto bn1 = std::dynamic_pointer_cast<Aft2d_tCornerNode>(e1.Node0());
		Debug_Null_Pointer(bn0);
		Debug_Null_Pointer(bn1);

		if (bn0->IsRegular() AND bn1->IsRegular())
		{
			auto node =
				Aft2d_tCornerNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else if (bn0->IsGap() AND bn1->IsGap())
		{
			auto node =
				Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else if (bn0->IsSingular() AND bn1->IsSingular())
		{
			auto snBn0 = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn0);
			auto snBn1 = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn1);
			Debug_Null_Pointer(snBn0);
			Debug_Null_Pointer(snBn1);

			if (snBn0->IsPole() OR snBn1->IsPole())
			{
				auto node =
					Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);
				Debug_Null_Pointer(node);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else
			{
				auto node =
					Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);
				Debug_Null_Pointer(node);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
		}
		else
		{
			if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn0))
			{
				if (sn->IsPole())
				{
					auto node =
						Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

					e0.SetNode1(node);
					e1.SetNode0(node);
				}
				else if (sn->IsLine())
				{
					auto node =
						Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
			else if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn1))
			{
				if (sn->IsPole())
				{
					auto node =
						Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

					e0.SetNode1(node);
					e1.SetNode0(node);
				}
				else if (sn->IsLine())
				{
					auto node =
						Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
			else if (auto gn = std::dynamic_pointer_cast<Aft2d_tCornerGapNode>(bn0))
			{
				auto node =
					Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (auto gn = std::dynamic_pointer_cast<Aft2d_tCornerGapNode>(bn1))
			{
				auto node =
					Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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

	if (Distance(e0.Node1()->Coord(), e1.Node0()->Coord()) > theTol)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Invalid Wire" << endl
			<< abort(FatalError);
	}

	auto bn0 = std::dynamic_pointer_cast<Aft2d_tCornerNode>(e0.Node1());
	auto bn1 = std::dynamic_pointer_cast<Aft2d_tCornerNode>(e1.Node0());
	Debug_Null_Pointer(bn0);
	Debug_Null_Pointer(bn1);

	if (bn0->IsRegular() AND bn1->IsRegular())
	{
		auto node =
			Aft2d_tCornerNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);
	}
	else if (bn0->IsGap() AND bn1->IsGap())
	{
		auto node =
			Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

		e0.SetNode1(node);
		e1.SetNode0(node);
	}
	else if (bn0->IsSingular() AND bn1->IsSingular())
	{
		auto snBn0 = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn0);
		auto snBn1 = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn1);
		Debug_Null_Pointer(snBn0);
		Debug_Null_Pointer(snBn1);

		if (snBn0->IsPole() OR snBn1->IsPole())
		{
			auto node =
				Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);
			Debug_Null_Pointer(node);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else
		{
			auto node =
				Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);
			Debug_Null_Pointer(node);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
	}
	else
	{
		if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn0))
		{
			if (sn->IsPole())
			{
				auto node =
					Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (sn->IsLine())
			{
				auto node =
					Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
		else if (auto sn = std::dynamic_pointer_cast<Aft2d_SingularNodeTemplate<Aft2d_tCornerNode>>(bn1))
		{
			if (sn->IsPole())
			{
				auto node =
					Aft2d_tCornerPoleNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

				e0.SetNode1(node);
				e1.SetNode0(node);
			}
			else if (sn->IsLine())
			{
				auto node =
					Aft2d_tCornerLineNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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
		else if (auto gn = std::dynamic_pointer_cast<Aft2d_tCornerGapNode>(bn0))
		{
			auto node =
				Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

			e0.SetNode1(node);
			e1.SetNode0(node);
		}
		else if (auto gn = std::dynamic_pointer_cast<Aft2d_tCornerGapNode>(bn1))
		{
			auto node =
				Aft2d_tCornerGapNode::MergeNodes(bn0, bn1, Mesh_BndMergeAlg::New);

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