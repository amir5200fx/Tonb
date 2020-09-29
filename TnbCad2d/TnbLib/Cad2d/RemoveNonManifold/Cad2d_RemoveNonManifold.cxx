#include <Cad2d_RemoveNonManifold.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::Cad2d_RemoveNonManifold::Node::IsOrphan() const
{
	Debug_Null_Pointer(Vtx());
	return Vtx()->IsOrphan();
}

//std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>
//tnbLib::Cad2d_RemoveNonManifold::Node::Select
//(
//	const Standard_Integer theIndex
//) const
//{
//	const auto& segments = Segments();
//	auto iter = segments.find(theIndex);
//	if (iter IS_EQUAL segments.end())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the item is not in the tree!" << endl
//			<< " - index = " << theIndex << endl
//			<< abort(FatalError);
//	}
//	
//}

std::weak_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment> 
tnbLib::Cad2d_RemoveNonManifold::Node::Remove
(
	const Standard_Integer theIndex
)
{
	auto iter = theSegments_.find(theIndex);
	if (iter IS_EQUAL theSegments_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theSegments_.erase(iter);
	return std::move(item);
}

void tnbLib::Cad2d_RemoveNonManifold::Node::Insert
(
	const Standard_Integer theIndex, 
	const std::shared_ptr<Segment>& theSegment
)
{
	auto paired = std::make_pair(theIndex, theSegment);
	auto insert = theSegments_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " index = " << theIndex << endl
			<< abort(FatalError);
	}
}

tnbLib::Cad2d_RemoveNonManifold::Segment::Segment
(
	std::shared_ptr<Node>&& theNode0,
	std::shared_ptr<Node>&& theNode1,
	std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
)
	: theNode0_(std::move(theNode0))
	, theNode1_(std::move(theNode1))
	, theEdges_(std::move(theEdges))
{
	// empty body
}

tnbLib::Cad2d_RemoveNonManifold::Segment::Segment
(
	const Standard_Integer theIndex,
	std::shared_ptr<Node>&& theNode0,
	std::shared_ptr<Node>&& theNode1,
	std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
)
	: Global_Indexed(theIndex)
	, theNode0_(std::move(theNode0))
	, theNode1_(std::move(theNode1))
	, theEdges_(std::move(theEdges))
{
	// empty body
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Cad2d_RemoveNonManifold::Segment::RetrieveEdges() const
{
	auto nodes = Pln_Tools::RetrieveVertices(Edges());

	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>> vtxMap;
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x);

		auto c = std::dynamic_pointer_cast<Pln_Vertex>(x->Copy());
		Debug_Null_Pointer(c);

		auto paired = std::make_pair(c->Index(), std::move(c));
		auto insert = vtxMap.insert(std::move(paired));
		if (NOT insert.second)
		{
			FatalErrorIn(FunctionSIG)
				<< "duplicate data!" << endl
				<< "index = " << c->Index() << endl
				<< abort(FatalError);
		}
	}

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		const auto& pv0 = x->Vtx0();
		const auto& pv1 = x->Vtx1();

		Debug_Null_Pointer(pv0);
		Debug_Null_Pointer(pv1);

		auto v0 = vtxMap[pv0->Index()];
		auto v1 = vtxMap[pv1->Index()];

		if (x->IsRing())
		{
			if (x->Curve())
			{
				auto curve = x->Curve()->Copy();
				auto c =
					std::make_shared<Pln_Ring>
					(
						x->Index(), x->Name(),
						v0,
						std::move(curve), x->Sense()
						);

				if (x->Mesh()) c->Mesh() = x->Mesh();

				edges.push_back(std::move(c));
			}
			else
			{
				auto c =
					std::make_shared<Pln_Ring>
					(
						x->Index(), x->Name(),
						v0,
						x->Sense()
						);

				if (x->Mesh()) c->Mesh() = x->Mesh();

				edges.push_back(std::move(c));
			}
		}
		else
		{
			if (x->Curve())
			{
				auto curve = x->Curve()->Copy();
				auto c =
					std::make_shared<Pln_Edge>
					(
						x->Index(), x->Name(),
						std::move(v0), std::move(v1),
						std::move(curve), x->Sense()
						);

				if (x->Mesh()) c->Mesh() = x->Mesh();

				edges.push_back(std::move(c));
			}
			else
			{
				auto c =
					std::make_shared<Pln_Edge>
					(
						x->Index(), x->Name(),
						std::move(v0), std::move(v1),
						x->Sense()
						);

				if (x->Mesh()) c->Mesh() = x->Mesh();

				edges.push_back(std::move(c));
			}		
		}	
	}

	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		if (x->IsRing())
		{
			const auto& v = x->Vtx0();
			v->InsertToEdges(x->Index(), x);
		}
		else
		{
			const auto& v0 = x->Vtx0();
			const auto& v1 = x->Vtx1();

			v0->InsertToEdges(x->Index(), x);
			v1->InsertToEdges(x->Index(), x);
		}
	}
	return std::move(edges);
}

void tnbLib::Cad2d_RemoveNonManifold::Ring::CheckRing()
{
	if (Node0() NOT_EQUAL Node1())
	{
		FatalErrorIn(FunctionSIG)
			<< "the ring is not valid" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_RemoveNonManifold::Import
(
	std::shared_ptr<Node>&& theNode
)
{
	auto& nodes = NodesRef();
	
	auto paired = std::make_pair(theNode->Index(), std::move(theNode));
	auto insert = nodes.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " - index = " << theNode->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_RemoveNonManifold::Import
(
	std::shared_ptr<Segment>&& theSegment
)
{
	auto& segments = SegmentsRef();

	auto paired = std::make_pair(theSegment->Index(), std::move(theSegment));
	auto insert = segments.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data" << endl
			<< " - index = " << theSegment->Index() << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_RemoveNonManifold::Remove
(
	const std::shared_ptr<Node>& theNode
)
{
	auto& nodes = NodesRef();

	auto iter = nodes.find(theNode->Index());
	if (iter IS_EQUAL nodes.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theNode->Index() << endl
			<< abort(FatalError);
	}
	Debug_If_Condition(iter->second NOT_EQUAL theNode);
	nodes.erase(iter);
}

void tnbLib::Cad2d_RemoveNonManifold::InsertVertices
(
	const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
)
{
	auto& nodes = NodesRef();

	for (const auto& x : theVertices)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsManifold())
		{
			auto node = std::make_shared<Node>(x->Index(), x);
			Debug_Null_Pointer(node);

			Import(std::move(node));
		}
	}
}

namespace tnbLib
{

	std::shared_ptr<Pln_Vertex> 
		NextNode
		(
			const std::shared_ptr<Pln_Vertex>& theNode,
			const std::shared_ptr<Pln_Edge>& theEdge
		)
	{
		Debug_Null_Pointer(theNode);
		Debug_Null_Pointer(theEdge);

		const auto& v0 = theEdge->Vtx0();
		const auto& v1 = theEdge->Vtx1();

		if (v0 IS_EQUAL theNode)
		{
			return v1;
		}
		if (v1 IS_EQUAL theNode)
		{
			return v0;
		}
		return nullptr;
	}

	std::shared_ptr<Pln_Edge> 
		NextEdge
		(
			const std::shared_ptr<Pln_Vertex>& theVtx,
			const std::shared_ptr<Pln_Edge>& theEdge
		)
	{
		const auto& edges = theVtx->RetrieveEdges();
		if (edges.size() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "the vertex is not manifold" << endl
				<< abort(FatalError);
		}

		if (edges[0].lock() IS_EQUAL theEdge)
		{
			return edges[1].lock();
		}
		if (edges[1].lock() IS_EQUAL theEdge)
		{
			return edges[0].lock();
		}
		FatalErrorIn(FunctionSIG)
			<< "Unable to find the next edge" << endl
			<< abort(FatalError);
		return nullptr;
	}

	std::tuple
		<
		std::vector<std::shared_ptr<Pln_Edge>>,
		std::shared_ptr<Pln_Vertex>,
		std::shared_ptr<Pln_Vertex>
		>
		MarchOnEdges
		(
			const std::shared_ptr<Pln_Vertex>& theVtx, 
			const std::shared_ptr<Pln_Edge>& theEdge
		)
	{
		theVtx->RemoveFromEdges(theEdge->Index());

		auto v0 = theVtx;
		auto nextEdge = theEdge;

		std::vector<std::shared_ptr<Pln_Edge>> edges;
		edges.push_back(nextEdge);

		auto nextVtx = NextNode(theVtx, nextEdge);
		while (NOT nextVtx->IsManifold())
		{
			nextEdge = NextEdge(nextVtx, nextEdge);
			edges.push_back(nextEdge);

			nextVtx = NextNode(nextVtx, nextEdge);
		}

		if (theVtx NOT_EQUAL nextVtx) nextVtx->RemoveFromEdges(nextEdge->Index());
		auto v1 = nextVtx;
		auto t = std::make_tuple(std::move(edges), std::move(v0), std::move(v1));
		return std::move(t);
	}

}

std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Node> 
tnbLib::Cad2d_RemoveNonManifold::SelectNode
(
	const Standard_Integer theIndex
) const
{
	const auto& nodes = Nodes();
	auto iter = nodes.find(theIndex);
	if (iter IS_EQUAL nodes.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index = " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment> 
tnbLib::Cad2d_RemoveNonManifold::RetrieveString
(
	const std::shared_ptr<Cad2d_RemoveNonManifold::Node>& theNode
) const
{
	Debug_Null_Pointer(theNode);

	const auto& vrtx = theNode->Vtx();
	Debug_Null_Pointer(vrtx);

	auto edges = vrtx->RetrieveEdges();
	Debug_If_Condition(edges.empty());

	const auto edge = edges[0].lock();

	auto[edgeString, v0, v1] = MarchOnEdges(vrtx, edge);

	auto node0 = SelectNode(v0->Index());
	auto node1 = SelectNode(v1->Index());
	if (node0 IS_EQUAL node1)
	{
		auto segment =
			std::make_shared<Ring>
			(
				SegmentCounter().RetrieveIndex(),
				std::move(node0),
				std::move(node1),
				std::move(edgeString)
				);
		return std::move(segment);
	}
	else
	{
		auto segment =
			std::make_shared<Segment>
			(
				SegmentCounter().RetrieveIndex(),
				std::move(node0),
				std::move(node1),
				std::move(edgeString)
				);
		return std::move(segment);
	}
}

std::vector<std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>> 
tnbLib::Cad2d_RemoveNonManifold::RetrieveSegments
(
	const std::shared_ptr<Cad2d_RemoveNonManifold::Node>& theNode
)
{
	Debug_If_Condition(theNode->IsOrphan());

	const auto& vtx = theNode->Vtx();
	Debug_Null_Pointer(vtx);

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> segments;
	while (NOT vtx->IsOrphan())
	{
		auto segment = RetrieveString(theNode);
		Debug_Null_Pointer(segment);

		segments.push_back(std::move(segment));
	}
	return std::move(segments);
}

std::vector<std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>> 
tnbLib::Cad2d_RemoveNonManifold::InsertEdges()
{
	auto& nodes = NodesRef();
	if (nodes.empty())
	{
		return std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>();
	}

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> nonRings;
	std::vector<std::shared_ptr<Node>> removed;

	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x.second);
		const auto& node = x.second;

		if (NOT node->IsOrphan())
		{
			auto segments = RetrieveSegments(node);
			for (auto& segment : segments)
			{
				Debug_Null_Pointer(segment);
				if (segment->IsRing())
				{
					Import(std::move(segment));
				}
				else
				{
					nonRings.push_back(std::move(segment));
				}
			}
		}
		else
		{
			removed.push_back(node);
		}
	}

	for (const auto& x : removed)
	{
		Remove(x);
	}

	return std::move(nonRings);
}

void tnbLib::Cad2d_RemoveNonManifold::AttachEdgesToNodes
(
	const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& x
) const
{
	Debug_Null_Pointer(x);
	const auto& edges = x->Edges();
	const auto& edge0 = edges[0];
	const auto& edge1 = edges[edges.size() - 1];

	Debug_Null_Pointer(edge0);
	Debug_Null_Pointer(edge1);

	if (edge0 IS_EQUAL edge1)
	{
		if (edge0->IsRing())
		{
			const auto& vtx = edge0->Vtx0();
			Debug_Null_Pointer(vtx);

			vtx->InsertToEdges(edge0->Index(), edge0);

			return;
		}
	}

	const auto& node0 = x->Node0();
	const auto& node1 = x->Node1();

	Debug_Null_Pointer(node0);
	Debug_Null_Pointer(node1);

	const auto& v0 = node0->Vtx();
	const auto& v1 = node1->Vtx();

	if (edge0->Vtx0() IS_EQUAL v0)
	{
		edge0->Vtx0()->InsertToEdges(edge0->Index(), edge0);
	}
	else if (edge0->Vtx1() IS_EQUAL v0)
	{
		edge0->Vtx1()->InsertToEdges(edge0->Index(), edge0);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	if (edge1->Vtx0() IS_EQUAL v1)
	{
		edge1->Vtx0()->InsertToEdges(edge1->Index(), edge1);
	}
	else if (edge1->Vtx1() IS_EQUAL v1)
	{
		edge1->Vtx1()->InsertToEdges(edge1->Index(), edge1);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}
}

Standard_Integer 
tnbLib::Cad2d_RemoveNonManifold::NbRings() const
{
	Standard_Integer k = 0;
	for (const auto& x : theSegments_)
	{
		Debug_Null_Pointer(x.second);
		if (x.second->IsRing())
		{
			++k;
		}
	}
	return k;
}

std::vector<std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>> 
tnbLib::Cad2d_RemoveNonManifold::RetrieveRings() const
{
	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> segments;
	for (const auto& x : theSegments_)
	{
		Debug_Null_Pointer(x.second);
		if (x.second->IsRing())
		{
			segments.push_back(x.second);
		}
	}
	return std::move(segments);
}

void tnbLib::Cad2d_RemoveNonManifold::Perform()
{
	auto nodes = Pln_Tools::RetrieveVertices(Edges());
	InsertVertices(nodes);

	auto nbRings = (Standard_Integer)0;
	Standard_Boolean Do = Standard_True;
	do 
	{
		auto segments = InsertEdges();

		if (Segments().size() > nbRings)
		{
			nbRings = Segments().size();

			for (const auto& x : segments)
			{
				AttachEdgesToNodes(x);
			}
		}
		else
		{
			Do = Standard_False;

			for (auto& x : segments)
			{
				Import(std::move(x));
			}
		}
	} while (Do);

	for (const auto& x : Segments())
	{
		Debug_Null_Pointer(x.second);
		AttachEdgesToNodes(x.second);
	}

	Change_IsDone() = Standard_True;
}