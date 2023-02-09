#include <Aft2d_CornerGapNodeUniMetric.hxx>

#include <Aft2d_SegmentEdgeUniMetric.hxx>
#include <Aft2d_SegmentNodeUniMetric.hxx>
#include <Aft2d_BndEdgeAnIso.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

template<>
std::shared_ptr<tnbLib::Aft2d_BndEdgeAnIso>
tnbLib::Aft2d_CornerGapNodeUniMetric::BlowThisUp()
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

	std::shared_ptr<Aft2d_BndEdgeAnIso> gapEdge;
	std::shared_ptr<Aft2d_BndEdgeAnIso> nonGapEdge;
	{
		auto iter = bEdges.begin();
		auto edge = iter->second.lock();
		if (edge->IsGap())
		{
			gapEdge = edge;
		}
		else
		{
			nonGapEdge = edge;
		}
		iter++;
		edge = iter->second.lock();
		if (edge->IsGap())
		{
			gapEdge = edge;
		}
		else
		{
			nonGapEdge = edge;
		}
	}
	if (NOT gapEdge OR NOT nonGapEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data has been detected!" << endl
			<< abort(FatalError);
	}

	const auto thisId = this->Index();
	std::shared_ptr<Aft2d_BndNodeAnIso> n0;
	std::shared_ptr<Aft2d_BndNodeAnIso> n1;
	{// retrieve the node n0 and an1 [5/13/2022 Amir]
		if (gapEdge->Node0()->Index() IS_EQUAL thisId)
		{
			n1 = std::dynamic_pointer_cast<Aft2d_BndNodeAnIso>(gapEdge->Node1());
			Debug_Null_Pointer(n1);

			n1->RemoveFromBoundaryEdges(gapEdge->Index());
		}
		else if (gapEdge->Node1()->Index() IS_EQUAL thisId)
		{
			n0 = std::dynamic_pointer_cast<Aft2d_BndNodeAnIso>(gapEdge->Node0());
			Debug_Null_Pointer(n0);

			n0->RemoveFromBoundaryEdges(gapEdge->Index());
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
		this->RemoveFromBoundaryEdges(gapEdge->Index());
		this->RemoveFromBoundaryEdges(nonGapEdge->Index());
	}
	catch (const error& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.message() << endl
			<< abort(FatalError);
	}

	{// retrieve the node n0 and an1 [5/13/2022 Amir]
		if (nonGapEdge->Node0()->Index() IS_EQUAL thisId)
		{
			n1 = std::dynamic_pointer_cast<Aft2d_BndNodeAnIso>(nonGapEdge->Node1());
			Debug_Null_Pointer(n1);

			n1->RemoveFromBoundaryEdges(nonGapEdge->Index());
		}
		else if (nonGapEdge->Node1()->Index() IS_EQUAL thisId)
		{
			n0 = std::dynamic_pointer_cast<Aft2d_BndNodeAnIso>(nonGapEdge->Node0());
			Debug_Null_Pointer(n0);

			n0->RemoveFromBoundaryEdges(nonGapEdge->Index());
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

	auto edge = nonGapEdge;
	Debug_Null_Pointer(edge);

	edge->SetNode0(n0);
	edge->SetNode1(n1);

	n0->InsertToBoundaryEdges(edge->Index(), edge);
	n1->InsertToBoundaryEdges(edge->Index(), edge);

	Debug_If_Condition(n0->NbBoundaryEdges() NOT_EQUAL 2);
	Debug_If_Condition(n1->NbBoundaryEdges() NOT_EQUAL 2);

	return std::move(edge);
}