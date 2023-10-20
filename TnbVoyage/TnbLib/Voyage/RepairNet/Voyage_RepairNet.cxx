#include <Voyage_RepairNet.hxx>

#include <VoyageWP_Net.hxx>
#include <Global_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	namespace voyageLib
	{
		namespace repair
		{

			// Forward Declarations
			class Edge;

			class Node
				: public Global_Indexed
				, public std::enable_shared_from_this<Node>
			{

				/*Private Data*/

				std::shared_ptr<VoyageWP_Net::Node> theWp_;

				std::map<Standard_Integer, std::weak_ptr<Edge>> theEdges_;

			public:

				// construtcors

				Node(const Standard_Integer theIndex, const std::shared_ptr<VoyageWP_Net::Node>& theWp)
					: Global_Indexed(theIndex)
					, theWp_(theWp)
				{}

				// Public functions and operators

				Standard_Integer NbEdges() const;
				Standard_Integer NbForwardEdges() const;
				Standard_Integer NbBackwardEdges() const;

				// There's no way to reach any forward node
				Standard_Boolean IsDeadend() const;
				Standard_Boolean IsReference() const;

				Standard_Boolean ShouldRemove() const;

				const auto& Wp() const { return theWp_; }

				const auto& Edges() const { return theEdges_; }
				void ImportEdge(const Standard_Integer, const std::shared_ptr<Edge>&);
				void RemoveEdge(const Standard_Integer theIndex);
				
			};

			class Edge
				: public Global_Indexed
			{

				/*Private Data*/

				std::shared_ptr<Node> theNode0_;
				std::shared_ptr<Node> theNode1_;

			public:

				// constructors

				Edge
				(
					const Standard_Integer theIndex,
					const std::shared_ptr<Node>& theNode0,
					const std::shared_ptr<Node>& theNode1
				)
					: Global_Indexed(theIndex)
					, theNode0_(theNode0)
					, theNode1_(theNode1)
				{}

				// Public functions and operators

				Standard_Boolean IsReference() const;

				[[nodiscard]] const auto& Node0() const { return theNode0_; }
				[[nodiscard]] const auto& Node1() const { return theNode1_; }
				
				
			};

			Standard_Integer Node::NbEdges() const { return static_cast<Standard_Integer>(theEdges_.size()); }
			Standard_Integer Node::NbForwardEdges() const
			{
				const auto This = this->shared_from_this();
				Standard_Integer size = 0;
				for (const auto& [id, x] : theEdges_)
				{
					const auto edge = x.lock();
					Debug_Null_Pointer(edge);
					if (edge->Node0() IS_EQUAL This)
					{
						size++;
					}
				}
				return size;
			}

			Standard_Integer Node::NbBackwardEdges() const
			{
				const auto This = this->shared_from_this();
				Standard_Integer size = 0;
				for (const auto& [id, x] : theEdges_)
				{
					const auto edge = x.lock();
					Debug_Null_Pointer(edge);
					if (edge->Node1() IS_EQUAL This)
					{
						size++;
					}
				}
				return size;
			}

			Standard_Boolean Node::IsDeadend() const
			{
				return NOT NbForwardEdges();
			}

			Standard_Boolean Node::IsReference() const
			{
				Debug_Null_Pointer(theWp_);
				return theWp_->IsReference();
			}

			Standard_Boolean Node::ShouldRemove() const
			{
				if (theWp_->IsReference()) 
					return Standard_False; // Cannot remove a reference node
				if (IsDeadend() OR NOT NbBackwardEdges())
				{
					return Standard_True;
				}
				return Standard_False;
			}

			void Node::ImportEdge(const Standard_Integer theIndex, const std::shared_ptr<Edge>& theEdge)
			{
				if (NOT theEdges_.insert({ theIndex, theEdge }).second)
				{
					FatalErrorIn(FunctionSIG) << endl
						<< " Duplicate data has been detected." << endl
						<< " - index: " << theIndex << endl
						<< abort(FatalError);
				}
			}

			void Node::RemoveEdge(const Standard_Integer theIndex)
			{
				const auto iter = theEdges_.find(theIndex);
				if (iter IS_EQUAL theEdges_.end())
				{
					FatalErrorIn(FunctionSIG) << endl
						<< " the item is not in the tree." << endl
						<< " - index: " << theIndex << endl
						<< abort(FatalError);
				}
				theEdges_.erase(iter);
			}

			Standard_Boolean Edge::IsReference() const
			{
				return Node0()->IsReference() AND Node1()->IsReference();
			}
		}
	}
}

tnbLib::Voyage_RepairNet::Voyage_RepairNet() = default;

void tnbLib::Voyage_RepairNet::Perform()
{
	if (NOT Net())
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "No net has been found." << endl
			<< abort(FatalError);
	}
	const auto origins = Net()->RetrieveNodes();
	/*
	 * ========================
	 * Building up the Topology
	 */
	// creating the repair's node map
	std::map<Standard_Integer, std::shared_ptr<voyageLib::repair::Node>> nodesMap;
	for (const auto& x: origins)
	{
		nodesMap.insert
		({ x->Index(), std::make_shared<voyageLib::repair::Node>(x->Index(), x) });
	}
	std::map<Standard_Integer, std::shared_ptr<voyageLib::repair::Edge>> edgesMap;
	Standard_Integer nb_edges = 0;
	for (const auto& x: Net()->Nodes())
	{ // for each ref. node
		auto nodes = x->RetrieveNodes(); // retrieve all the nodes in the current state.
		for (const auto& current: nodes)
		{
			Debug_Null_Pointer(current);
			// retrieve all the forward nodes
			const auto& nexts = current->Nexts();
			for (const auto& [next_id, next] : nexts)
			{
				Debug_Null_Pointer(next);
				auto edge = 
					std::make_shared<voyageLib::repair::Edge>
				(
					++nb_edges, 
					nodesMap.at(current->Index()),
					nodesMap.at(next->Index())
					); // create an edge
				// import the edge for the two end point of the edge
				nodesMap.at(edge->Node0()->Index())->ImportEdge(edge->Index(), edge);
				nodesMap.at(edge->Node1()->Index())->ImportEdge(edge->Index(), edge);
				edgesMap.insert({ edge->Index(), std::move(edge) }); // insert the edge to the edgeMap
			}
		}
	}
	/*
	 * End of the Building up the Topology
	 * ===================================
	 */
	/*
	 * =========================================================
	 * Start removing the nodes and edges which are unnecessary.
	 */
	Standard_Integer nb_cycles = 0;
	while (true)
	{
		std::vector<std::shared_ptr<voyageLib::repair::Node>> removed_nodes;
		// traverse through all of the nodes in the mesh
		for (const auto& [current_id, current] : nodesMap)
		{
			Debug_Null_Pointer(current);
			if (current->ShouldRemove()) // checking to remove the node
			{
				// retrieve all the edges around the node
				std::vector<Standard_Integer> removed_edges;
				for (const auto& [edge_id, w_edge]: current->Edges())
				{
					const auto edge = w_edge.lock();
					Debug_Null_Pointer(edge);
					removed_edges.emplace_back(edge->Index());
				}
				// removing the edges
				for (auto edge_id: removed_edges)
				{
					auto iter = edgesMap.find(edge_id);
					if (iter IS_EQUAL edgesMap.end())
					{
						FatalErrorIn(FunctionSIG) << endl
							<< " the item is not found." << endl
							<< " - index: " << edge_id << endl
							<< abort(FatalError);
					}
					auto edge = iter->second;
					// remove the edge from the its two end nodes
					edge->Node0()->RemoveEdge(edge_id);
					edge->Node1()->RemoveEdge(edge_id);
					// remove the edge from the map
					edgesMap.erase(iter);
				}
				// register the already removed node into the removed_nodes list
				removed_nodes.emplace_back(current); 
			}
		}
		// remove all the nodes in the removed_nodes list
		for (const auto& node:removed_nodes)
		{
			Debug_Null_Pointer(node);
			auto iter = nodesMap.find(node->Index());
			if (iter IS_EQUAL nodesMap.end())
			{
				FatalErrorIn(FunctionSIG) << endl
					<< " the item is not found." << endl
					<< " - index: " << node->Index() << endl
					<< abort(FatalError);
			}
			nodesMap.erase(iter);
		}
		if (!removed_nodes.empty())
		{
			++nb_cycles; // counting removing cycles
		}
		if (removed_nodes.empty())
		{
			break; // get out from the cycle!
		}
	}
	/*
	 * End of the removing the nodes and edges which are unnecessary.
	 * ==============================================================
	 */
	if (nb_cycles)
	{ // if there is any node that has been removed from the mesh
		Net()->FlushConnects(); // remove the connects
		/*
		 * =============================
		 * Remove the non-feasible nodes
		 */
		for (const auto& ref: Net()->Nodes())
		{
			if (const auto interior = std::dynamic_pointer_cast<VoyageWP_Net::InterNode>(ref))
			{ // Check if the node is an interior; forbidden to remove a reference node
				{// checking the starboard side
					const auto wps = interior->RetrieveStarSides();
					for (const auto& wp: wps)
					{
						Debug_Null_Pointer(wp);
						if (auto iter = nodesMap.find(wp->Index()); iter IS_EQUAL nodesMap.end())
						{
							interior->RemoveFromStarboard(wp->Index());
						}
					}
				}
				{// checking the port side
					const auto wps = interior->RetrievePortSides();
					for (const auto& wp : wps)
					{
						Debug_Null_Pointer(wp);
						if (auto iter = nodesMap.find(wp->Index()); iter IS_EQUAL nodesMap.end())
						{
							interior->RemoveFromPort(wp->Index());
						}
					}
				}
			}
		}
		/*
		 * The nodes have been removed
		 * ============================
		 */
		/* =====================
		 * Renumbering the nodes
		 */
		std::map<Standard_Integer, Standard_Integer> oldId_to_newId;
		{ // saving the old numbering
			auto allNodes = Net()->RetrieveNodes();
			Standard_Integer nb_nodes = 0;
			for (const auto& x : allNodes)
			{
				oldId_to_newId.insert({ x->Index(), ++nb_nodes });
			}
		}
		{// renumbering
			/*const auto nodes = Net()->RetrieveNodes();
			Standard_Integer nb_nodes = 0;
			for (const auto& x : nodes)
			{
				x->SetIndex(++nb_nodes);
			}*/
		}
		/*
		 * End of renumbering
		 * ==================
		 */
		/*
		 * =========================
		 * Reconnect the nodes again
		 */
		for (const auto& [id, x] : edgesMap)
		{
			Debug_Null_Pointer(x);
			const auto& node0 = x->Node0();
			const auto& node1 = x->Node1();
			Debug_Null_Pointer(node0);
			Debug_Null_Pointer(node1);
			const auto& wp0 = node0->Wp();
			const auto& wp1 = node1->Wp();
			Debug_Null_Pointer(wp0);
			Debug_Null_Pointer(wp1);
			wp0->InsertNode(wp1->Index(), wp1);
		}
		/*
		 * End of the reconnection
		 * =======================
		 */
	}
	Change_IsDone() = Standard_True;
}
