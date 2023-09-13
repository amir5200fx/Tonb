#include <VoyageWP_Ref.hxx>

#include <Voyage_Tools.hxx>
#include <VoyageMesh_Element.hxx>
#include <VoyageMesh_RefEdge.hxx>
#include <VoyageMesh_DepartureNode.hxx>
#include <VoyageMesh_ArrivalNode.hxx>
#include <VoyageMesh_Node.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

tnbLib::Dir2d 
tnbLib::VoyageWP_Ref::DepNode::CalcTangent() const
{
	auto edge = Forward().lock();
	if (NOT edge)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no forward edge has been assigned." << endl
			<< abort(FatalError);
	}
	auto d = edge->CalcTangent();
	return std::move(d);
}

tnbLib::Dir2d 
tnbLib::VoyageWP_Ref::ArvNode::CalcTangent() const
{
	const auto edge = Backward().lock();
	if (NOT edge)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no backward edge has been assigned." << endl
			<< abort(FatalError);
	}
	auto d = edge->CalcTangent();
	return std::move(d);
}

tnbLib::Dir2d 
tnbLib::VoyageWP_Ref::SupEdge::CalcTangent() const
{
	const auto p0 = VoyageWP_Ref::FirstCoord(*this);
	const auto p1 = VoyageWP_Ref::SecondCoord(*this);
	Dir2d d(p0, p1);
	return std::move(d);
}

tnbLib::Dir2d
tnbLib::VoyageWP_Ref::InterNode::CalcTangent() const
{
	const auto sup_forward_edge = Forward().lock();
	Debug_Null_Pointer(sup_forward_edge);
	const auto sup_backward_edge = Backward().lock();
	Debug_Null_Pointer(sup_backward_edge);
	const auto& n0 = sup_backward_edge->Node0();
	const auto& n1 = sup_backward_edge->Node1();
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	const auto& n2 = sup_forward_edge->Node0();
	const auto& n3 = sup_forward_edge->Node1();
	Debug_Null_Pointer(n2);
	Debug_Null_Pointer(n3);
	if (n2 NOT_EQUAL n1)
	{
		FatalErrorIn(FunctionSIG)
			<< "Something went wrong: the topology is not correct." << endl
			<< abort(FatalError);
	}
	auto dir = Voyage_Tools::CalcTangent(n0->Coord(), n1->Coord(), n3->Coord());
	return std::move(dir);
}

tnbLib::Pnt2d
tnbLib::VoyageWP_Ref::InterNode::CalcStarOffset() const
{
	const auto sup_forward_edge = Forward().lock();
	Debug_Null_Pointer(sup_forward_edge);
	const auto sup_backward_edge = Backward().lock();
	Debug_Null_Pointer(sup_backward_edge);
	const auto node0 = sup_backward_edge->RetrieveStarTip();
	Debug_Null_Pointer(node0);
	const auto node1 = sup_forward_edge->RetrieveStarTip();
	Debug_Null_Pointer(node1);
	const auto pm = MEAN(node0->Coord(), node1->Coord());
	return std::move(pm);
}

tnbLib::Pnt2d
tnbLib::VoyageWP_Ref::InterNode::CalcPortOffset() const
{
	const auto sup_forward_edge = Forward().lock();
	Debug_Null_Pointer(sup_forward_edge);
	const auto sup_backward_edge = Backward().lock();
	Debug_Null_Pointer(sup_backward_edge);
	const auto node0 = sup_backward_edge->RetrievePortTip();
	Debug_Null_Pointer(node0);
	const auto node1 = sup_forward_edge->RetrievePortTip();
	Debug_Null_Pointer(node1);
	const auto pm = MEAN(node0->Coord(), node1->Coord());
	return std::move(pm);
}

std::shared_ptr<tnbLib::VoyageMesh_Node>
tnbLib::VoyageWP_Ref::SupEdge::RetrieveStarTip() const
{
	const auto edge = 
		std::dynamic_pointer_cast<VoyageMesh_RefEdge>(Starboard());
	Debug_Null_Pointer(edge);
	auto node = edge->RetrieveTip();
	return std::move(node);
}

std::shared_ptr<tnbLib::VoyageMesh_Node>
tnbLib::VoyageWP_Ref::SupEdge::RetrievePortTip() const
{
	const auto edge =
		std::dynamic_pointer_cast<VoyageMesh_RefEdge>(Port());
	Debug_Null_Pointer(edge);
	auto node = edge->RetrieveTip();
	return std::move(node);
}

std::shared_ptr<tnbLib::VoyageMesh_Element>
tnbLib::VoyageWP_Ref::SupEdge::RetrieveStarElement() const
{
	const auto element = theStarboard_->LeftElement().lock();
	if(NOT element)
	{
		FatalErrorIn(FunctionSIG)
			<< "no element has been found." << endl
			<< abort(FatalError);
	}
	return std::move(element);
}

std::shared_ptr<tnbLib::VoyageMesh_Element>
tnbLib::VoyageWP_Ref::SupEdge::RetrievePortElement() const
{
	const auto element = thePort_->LeftElement().lock();
	if (NOT element)
	{
		FatalErrorIn(FunctionSIG)
			<< "no element has been found." << endl
			<< abort(FatalError);
	}
	return std::move(element);
}

Standard_Real tnbLib::VoyageWP_Ref::DEFAULT_TOL = 1.0E-6;

namespace tnbLib
{
	Standard_Boolean 
		AreMatched
		(
			const VoyageMesh_Edge& theEdge0, 
			const VoyageMesh_Edge& theEdge1, 
			const Standard_Real tol
		)
	{
		Debug_Null_Pointer(theEdge0.Node0());
		Debug_Null_Pointer(theEdge0.Node1());
		const auto& p0 = theEdge0.Node0()->Coord();
		const auto& p1 = theEdge0.Node1()->Coord();
		Debug_Null_Pointer(theEdge1.Node0());
		Debug_Null_Pointer(theEdge1.Node1());
		{
			const auto& pt = theEdge1.Node1()->Coord();
			if (pt.Distance(p0) > tol)
			{
				return Standard_False;
			}
		}
		{
			const auto& pt = theEdge1.Node0()->Coord();
			if (pt.Distance(p1) > tol)
			{
				return Standard_False;
			}
		}
		return Standard_True;
	}

	// The first one is starboard and the seond is port [9/13/2023 Payvand]
	std::vector
		<
		std::pair
		<
		std::shared_ptr<VoyageMesh_Edge>,
		std::shared_ptr<VoyageMesh_Edge>
		>
		>
		MakePairs
		(
			const std::vector<std::shared_ptr<VoyageMesh_Edge>>& theStarboard,
			const std::vector<std::shared_ptr<VoyageMesh_Edge>>& thePort,
			const Standard_Real tol
		)
	{
		auto port = thePort;
		std::reverse(port.begin(), port.end());
		std::vector
			<
			std::pair
			<
			std::shared_ptr<VoyageMesh_Edge>,
			std::shared_ptr<VoyageMesh_Edge>
			>
			> edges;
		for (size_t i = 0; i < theStarboard.size(); i++)
		{
			const auto& edge0 = theStarboard.at(i);
			const auto& edge1 = port.at(i);
			if (AreMatched(*edge0, *edge1, tol))
			{
				auto paired = std::make_pair(edge0, edge1);
				edges.push_back(std::move(paired));
			}
		}
		return std::move(edges);
	}

	auto RetrieveFirstCoord
	(
		const std::pair<std::shared_ptr<VoyageMesh_Edge>, std::shared_ptr<VoyageMesh_Edge>>& thePair
	)
	{
		auto [e0, e1] = thePair;
		auto ref0 = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e0);
		Debug_Null_Pointer(ref0);
		auto ref1 = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e1);
		Debug_Null_Pointer(ref1);
		//std::cout << "sense 0 : " << ref0->Sense() << std::endl;
		//std::cout << "sense 1 : " << ref1->Sense() << std::endl;
		auto n0 = ref0->Node0();
		if (NOT ref0->Sense())
		{
			n0 = ref0->Node1();
		}
		auto n1 = ref1->Node0();
		if (NOT ref1->Sense())
		{
			n1 = ref1->Node1();
		}
		auto pm = MEAN(n0->Coord(), n1->Coord());
		return std::move(pm);
	}

	auto RetrieveSecondCoord
	(
		const std::pair<std::shared_ptr<VoyageMesh_Edge>, std::shared_ptr<VoyageMesh_Edge>>& thePair
	)
	{
		auto [e0, e1] = thePair;
		auto ref0 = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e0);
		Debug_Null_Pointer(ref0);
		auto ref1 = std::dynamic_pointer_cast<VoyageMesh_RefEdge>(e1);
		Debug_Null_Pointer(ref1);
		auto n0 = ref0->Node1();
		if (NOT ref0->Sense())
		{
			n0 = ref0->Node0();
		}
		auto n1 = ref1->Node1();
		if (NOT ref1->Sense())
		{
			n1 = ref1->Node0();
		}
		auto pm = MEAN(n0->Coord(), n1->Coord());
		return std::move(pm);
	}

	std::vector<std::shared_ptr<VoyageWP_Ref::SupNode>> 
		CalcNodes
		(
			const std::vector
			<
			std::pair
			<
			std::shared_ptr<VoyageMesh_Edge>,
			std::shared_ptr<VoyageMesh_Edge>
			>
			>& theEdges
		)
	{
		if (theEdges.empty())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid path has been detected." << endl
				<< abort(FatalError);
		}
		Standard_Integer nbNodes = 0;
		std::vector<std::shared_ptr<VoyageWP_Ref::SupNode>> nodes;
		nodes.reserve(theEdges.size() + 1);
		{// departure node [9/6/2023 aamir]
			auto pt = RetrieveFirstCoord(FirstItem(theEdges));
			auto node = std::make_shared<VoyageWP_Ref::DepNode>(++nbNodes, std::move(pt));
			nodes.push_back(std::move(node));
		}
		for (size_t i = 1; i < theEdges.size(); i++)
		{
			auto pt = RetrieveFirstCoord(theEdges.at(i));
			auto node = std::make_shared<VoyageWP_Ref::InterNode>(++nbNodes, std::move(pt));
			nodes.push_back(std::move(node));
		}
		{// arrival node [9/6/2023 aamir]
			auto pt = RetrieveSecondCoord(LastItem(theEdges));
			auto node = std::make_shared<VoyageWP_Ref::ArvNode>(++nbNodes, std::move(pt));
			nodes.push_back(std::move(node));
		}
		return std::move(nodes);
	}
}

std::shared_ptr<tnbLib::VoyageWP_Ref::SupNode>
tnbLib::VoyageWP_Ref::GetDeparture() const
{
	return FirstItem(theEntities_)->Node0();
}

std::shared_ptr<tnbLib::VoyageWP_Ref::SupNode>
tnbLib::VoyageWP_Ref::GetArrival() const
{
	return LastItem(theEntities_)->Node1();
}

std::shared_ptr<tnbLib::VoyageWP_Ref::SupNode> 
tnbLib::VoyageWP_Ref::Departure() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the applications is not performed." << endl
			<< abort(FatalError);
	}
	return GetDeparture();
}

std::shared_ptr<tnbLib::VoyageWP_Ref::SupNode> 
tnbLib::VoyageWP_Ref::Arrival() const
{
	if (NOT IsDone())
	{
		FatalErrorIn(FunctionSIG)
			<< "the application is not performed." << endl
			<< abort(FatalError);
	}
	return GetArrival();
}

void tnbLib::VoyageWP_Ref::CalcReference
(
	const EdgeList& theStarboard, 
	const EdgeList& thePort
)
{
	if (theStarboard.size() NOT_EQUAL thePort.size())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "the size of starboard list and the size of the port list aren't matched." << endl
			<< abort(FatalError);
	}
	auto edges = MakePairs(theStarboard, thePort, DEFAULT_TOL);
	auto nodes = CalcNodes(edges);
	Standard_Integer nbEdges = 0;
	std::vector<std::shared_ptr<SupEdge>> super_edges;
	super_edges.reserve(edges.size());
	for (size_t i = 0; i < edges.size(); i++)
	{
		const auto& n0 = nodes.at(i);
		const auto& n1 = nodes.at(i + 1);
		//std::cout << "n0 = " << n0->Coord() << std::endl;
		//std::cout << "n1 = " << n1->Coord() << std::endl;
		//std::cout << std::endl;
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto sup_edge = std::make_shared<SupEdge>(++nbEdges, n0, n1);
		Debug_Null_Pointer(sup_edge);
		sup_edge->SetStarboard(edges.at(i).first);
		sup_edge->SetPort(edges.at(i).second);
		super_edges.push_back(std::move(sup_edge));
	}
	//std::exit(1);
	theEntities_ = super_edges;
	{// getting the departure node [9/13/2023 Payvand]
		auto node = std::dynamic_pointer_cast<DepNode>(GetDeparture());
		Debug_Null_Pointer(node);
		auto edge = FirstItem(super_edges);
		Debug_Null_Pointer(edge);
		node->SetForward(edge);
		auto inter_node = std::dynamic_pointer_cast<InterNode>(edge->Node1());
		Debug_Null_Pointer(inter_node);
		inter_node->SetBackward(edge);
	}
	{
		// getting the arrival node [9/13/2023 Payvand]
		auto node = std::dynamic_pointer_cast<ArvNode>(GetArrival());
		Debug_Null_Pointer(node);
		auto edge = LastItem(super_edges);
		Debug_Null_Pointer(edge);
		node->SetBackward(edge);
		auto inter_node = std::dynamic_pointer_cast<InterNode>(edge->Node0());
		Debug_Null_Pointer(inter_node);
		inter_node->SetForward(edge);
	}
	// Setting up the forward and the backward edges for interior nodes [9/13/2023 Payvand]
	for (size_t i = 1; i < super_edges.size() - 1; i++)
	{
		Debug_Null_Pointer(super_edges.at(i));
		const auto node0 = std::dynamic_pointer_cast<InterNode>(super_edges.at(i)->Node0());
		const auto node1 = std::dynamic_pointer_cast<InterNode>(super_edges.at(i)->Node1());
		Debug_Null_Pointer(node0);
		Debug_Null_Pointer(node1);
		node0->SetForward(super_edges.at(i));
		node1->SetBackward(super_edges.at(i));
	}
	Change_IsDone() = Standard_True;
}

std::shared_ptr<tnbLib::VoyageMesh_Element> 
tnbLib::VoyageWP_Ref::RetrieveStarElement
(
	const SupEdge& theEdge
)
{
	const auto& edge = theEdge.Starboard();
	Debug_Null_Pointer(edge);
	auto element = edge->LeftElement().lock();
	return std::move(element);
}

std::shared_ptr<tnbLib::VoyageMesh_Element> 
tnbLib::VoyageWP_Ref::RetrievePortElement
(
	const SupEdge& theEdge
)
{
	const auto& edge = theEdge.Port();
	Debug_Null_Pointer(edge);
	auto element = edge->LeftElement().lock();
	return std::move(element);
}

tnbLib::Pnt2d 
tnbLib::VoyageWP_Ref::FirstCoord
(
	const SupEdge& theEdge
)
{
	const auto& node = theEdge.Node0();
	Debug_Null_Pointer(node);
	auto coord = node->Coord();
	return std::move(coord);
}

tnbLib::Pnt2d 
tnbLib::VoyageWP_Ref::SecondCoord
(
	const SupEdge& theEdge
)
{
	const auto& node = theEdge.Node1();
	Debug_Null_Pointer(node);
	auto coord = node->Coord();
	return std::move(coord);
}