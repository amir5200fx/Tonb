#include <VoyageWP_Offset.hxx>

#include <VoyageWP_Ref.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::VoyageWP_Offset::CalcOffsets
(
	const VoyageWP_Ref& theRef
)
{
	const auto& edges = theRef.Entities();
	if (edges.empty())
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge list is empty." << endl
			<< abort(FatalError);
	}
	Standard_Integer nb_nodes = 0;
	std::vector<std::shared_ptr<Node>> nodes;
	nodes.reserve(edges.size() + 1);
	{//- the departure node
		auto ref_node = theRef.Departure();
		Debug_Null_Pointer(ref_node);
		auto node = std::make_shared<DepNode>(++nb_nodes, ref_node->Coord());
		Debug_Null_Pointer(node);
		node->SetTangent(ref_node->CalcTangent());
		nodes.push_back(std::move(node));
	}
	for (size_t i = 1; i < edges.size(); i++)
	{
		Debug_Null_Pointer(edges.at(i));
		const auto& ref_node = edges.at(i)->Node0();
		Debug_Null_Pointer(ref_node);
		auto node = std::make_shared<InterNode>(++nb_nodes, ref_node->Coord());
		Debug_Null_Pointer(node);
		node->SetTangent(ref_node->CalcTangent());
		{//- Create the Offset points
			auto interior_node = std::dynamic_pointer_cast<VoyageWP_Ref::InterNode>(ref_node);
			Debug_Null_Pointer(interior_node);
			
			auto star_offset_node = std::make_shared<OffsetNode>(++nb_nodes, interior_node->CalcStarOffset());
			Debug_Null_Pointer(star_offset_node);
			star_offset_node->SetRef(node);
			node->SetStarboard(std::move(star_offset_node));

			auto port_offset_node = std::make_shared<OffsetNode>(++nb_nodes, interior_node->CalcPortOffset());
			Debug_Null_Pointer(port_offset_node);
			port_offset_node->SetRef(node);
			node->SetPort(std::move(port_offset_node));
		}
		nodes.push_back(std::move(node));
	}
	{//- the arrival node
		auto ref_node = theRef.Arrival();
		Debug_Null_Pointer(ref_node);
		auto node = std::make_shared<ArvNode>(++nb_nodes, ref_node->Coord());
		Debug_Null_Pointer(node);
		node->SetTangent(ref_node->CalcTangent());
		nodes.push_back(std::move(node));
	}
	theRef_ = std::move(nodes);
	Change_IsDone() = Standard_True;
}