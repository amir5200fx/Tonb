#include <Aft2d_tCornerPoleNode.hxx>

#include <Aft2d_tSegmentEdge.hxx>
#include <Aft2d_tSegmentNode.hxx>
#include <Geo2d_MetricPrcsrAnIso.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
void tnbLib::Aft2d_tCornerPoleNode::RemoveThis
(
	const Geo2d_MetricPrcsrAnIso& thePrcsr
)
{
	auto edge = BlowThisUp();

	const auto& n0 = edge->Node0();
	const auto& n1 = edge->Node1();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	edge->SetCharLength(thePrcsr.CalcDistance(n0->Coord(), n1->Coord()));
	edge->SetCentre(thePrcsr.CalcCentre(n0->Coord(), n1->Coord()));
}

template<>
std::shared_ptr<tnbLib::Aft2d_BndEdgeSurface>
tnbLib::Aft2d_tCornerPoleNode::BlowThisUp()
{
	if (this->NbBoundaryEdges() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG)
			<< "the node is not manifold!" << endl
			<< abort(FatalError);
	}

	if (this->IsFixed())
	{
		FatalErrorIn(FunctionSIG)
			<< "the node is forbidden to remove:" << endl
			<< " - the fixed flag is on." << endl
			<< abort(FatalError);
	}
	const auto& bEdges = this->RetrieveBoundaryEdges();

	std::shared_ptr<Aft2d_BndEdgeSurface> singEdge;
	std::shared_ptr<Aft2d_BndEdgeSurface> nonSingEdge;
	{
		auto iter = bEdges.begin();
		auto edge = iter->second.lock();
		if (edge->IsPoleSingular())
		{
			singEdge = edge;
		}
		else
		{
			nonSingEdge = edge;
		}
		iter++;
		edge = iter->second.lock();
		if (edge->IsPoleSingular())
		{
			singEdge = edge;
		}
		else
		{
			nonSingEdge = edge;
		}
	}
	if (NOT singEdge OR NOT nonSingEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected!" << endl
			<< abort(FatalError);
	}

	const auto thisId = this->Index();
	std::shared_ptr<Aft2d_BndNodeSurface> n0;
	std::shared_ptr<Aft2d_BndNodeSurface> n1;
	{// retrieve the node n0 and an1 [4/25/2022 Amir]
		if (singEdge->Node0()->Index() IS_EQUAL thisId)
		{
			n1 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(singEdge->Node1());
			Debug_Null_Pointer(n1);

			n1->RemoveFromBoundaryEdges(singEdge->Index());
		}
		else if (singEdge->Node1()->Index() IS_EQUAL thisId)
		{
			n0 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(singEdge->Node0());
			Debug_Null_Pointer(n0);

			n0->RemoveFromBoundaryEdges(singEdge->Index());
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
	}

	try
	{
		this->RemoveFromBoundaryEdges(singEdge->Index());
		this->RemoveFromBoundaryEdges(nonSingEdge->Index());
	}
	catch (const error& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.message() << endl
			<< abort(FatalError);
	}

	{// retrieve the node n0 and an1 [4/25/2022 Amir]
		if (nonSingEdge->Node0()->Index() IS_EQUAL thisId)
		{
			n1 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(nonSingEdge->Node1());
			Debug_Null_Pointer(n1);

			n1->RemoveFromBoundaryEdges(nonSingEdge->Index());
		}
		else if (nonSingEdge->Node1()->Index() IS_EQUAL thisId)
		{
			n0 = std::dynamic_pointer_cast<Aft2d_BndNodeSurface>(nonSingEdge->Node0());
			Debug_Null_Pointer(n0);

			n0->RemoveFromBoundaryEdges(nonSingEdge->Index());
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected!" << endl
				<< abort(FatalError);
		}
	}
	if (NOT n0 OR NOT n1)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected!" << endl
			<< abort(FatalError);
	}

	auto edge = nonSingEdge;
	Debug_Null_Pointer(edge);

	edge->SetNode0(n0);
	edge->SetNode1(n1);

	n0->InsertToBoundaryEdges(edge->Index(), edge);
	n1->InsertToBoundaryEdges(edge->Index(), edge);

	Debug_If_Condition(n0->NbBoundaryEdges() NOT_EQUAL 2);
	Debug_If_Condition(n1->NbBoundaryEdges() NOT_EQUAL 2);

	return std::move(edge);
}