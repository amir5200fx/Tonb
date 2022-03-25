#include <Cad2d_RemoveNonManifold.hxx>

#include <Pln_Curve.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_CmpEdge.hxx>
#include <Pln_Wire.hxx>
#include <Pln_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

short unsigned tnbLib::Cad2d_RemoveNonManifold::verbose(0);

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
		const auto pv0 = x->FirstVtx();
		const auto pv1 = x->LastVtx();

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
					std::make_shared<Pln_Segment>
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
					std::make_shared<Pln_Segment>
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
			const auto v = x->FirstVtx();
			v->InsertToEdges(x->Index(), x);
		}
		else
		{
			const auto v0 = x->FirstVtx();
			const auto v1 = x->LastVtx();

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

void tnbLib::Cad2d_RemoveNonManifold::RemoveManifols
(
	const std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>& theSegments
) const
{
	for (const auto& seg : theSegments)
	{
		Debug_Null_Pointer(seg);
		for (const auto& x : seg->Edges())
		{
			Debug_Null_Pointer(x);

			const auto v0 = x->FirstVtx();
			Debug_Null_Pointer(v0);

			auto iter = theManifolds_.find(v0->Index());
			if (iter NOT_EQUAL theManifolds_.end())
			{
				theManifolds_.erase(iter);
			}
			/*else*/
			//{
				//- do nothing!
				//- 
				//- the vertex has been removed
				//  [5/25/2021 Amir]
			//}

			const auto v1 = x->LastVtx();
			Debug_Null_Pointer(v1);

			iter = theManifolds_.find(v1->Index());
			if (iter NOT_EQUAL theManifolds_.end())
			{
				theManifolds_.erase(iter);
			}
			/*else*/
			//{
				//- do nothing!
				//- 
				//- the vertex has been removed
				//  [5/25/2021 Amir]
			//}
		}
	}
}

void tnbLib::Cad2d_RemoveNonManifold::InsertVertices
(
	const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
)
{
	for (const auto& x : theVertices)
	{
		Debug_Null_Pointer(x);

		if (NOT x->IsManifold())
		{
			auto node = std::make_shared<Node>(x->Index(), x);
			Debug_Null_Pointer(node);

			Import(std::move(node), NodesRef());
		}
		else
		{
			auto vtx = x;
			Import(std::move(vtx), Manifolds());
		}
	}
}

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::Pln_Edge>>, 
	std::shared_ptr<tnbLib::Pln_Vertex>, 
	std::shared_ptr<tnbLib::Pln_Vertex>
> 
tnbLib::Cad2d_RemoveNonManifold::MarchOnEdges
(
	const std::shared_ptr<Pln_Vertex>& theVtx, 
	const std::shared_ptr<Pln_Edge>& theEdge
) const
{
	if (Cad2d_RemoveNonManifold::verbose > 1)
	{
		Info << " - marching on the edges..." << endl;
	}

	auto[edges, v0, v1] = Pln_Tools::MarchOnEdges(theVtx, theEdge);

	v0->RemoveFromEdges(FirstItem(edges)->Index());
	if (v0 NOT_EQUAL v1)
	{
		v1->RemoveFromEdges(LastItem(edges)->Index());
	}

	/*theVtx->RemoveFromEdges(theEdge->Index());

	auto v0 = theVtx;
	auto nextEdge = theEdge;

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.push_back(nextEdge);

	auto nextVtx = Pln_Tools::NextNode(theVtx, nextEdge);
	while (nextVtx->IsManifold())
	{
		nextEdge = Pln_Tools::NextEdge(nextEdge, nextVtx);
		edges.push_back(nextEdge);

		nextVtx = Pln_Tools::NextNode(nextVtx, nextEdge);
	}

	if (theVtx NOT_EQUAL nextVtx) nextVtx->RemoveFromEdges(nextEdge->Index());
	auto v1 = nextVtx;*/
	auto t = std::make_tuple(std::move(edges), std::move(v0), std::move(v1));

	if (Cad2d_RemoveNonManifold::verbose > 1)
	{
		Info << " - " << edges.size() << " edges are detected" << endl;
		Info << " ***** Leaving the MarchOnEdges function ******" << endl;
	}
	return std::move(t);
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
		if (verbose > 1)
		{
			Info << " a ring is detected" << endl;
		}

		auto segment =
			std::make_shared<Cad2d_RemoveNonManifold::Ring>
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
		if (verbose > 1)
		{
			Info << " a segment is detected" << endl;
		}

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

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>>,
	std::vector<std::shared_ptr<tnbLib::Cad2d_RemoveNonManifold::Segment>>
>
tnbLib::Cad2d_RemoveNonManifold::InsertEdges()
{
	const auto& nodes = Nodes();

	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> nonRings;
	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> rings;
	if (nodes.empty())
	{
		auto t = std::make_tuple(std::move(rings), std::move(nonRings));
		return std::move(t);
	}
	
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
					rings.push_back(segment);
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

	for (auto& x : removed)
	{
		Remove(x, NodesRef());
	}

	auto t = std::make_tuple(std::move(rings), std::move(nonRings));
	return std::move(t);
}

namespace tnbLib
{
	auto RetrieveRing(const Standard_Integer segId, const std::shared_ptr<Pln_Vertex>& theVtx)
	{
		auto wire = Pln_Tools::RetrieveWire(theVtx);
		Debug_Null_Pointer(wire);
		Debug_Null_Pointer(wire->CmpEdge());

		auto node0 = std::make_shared<Cad2d_RemoveNonManifold::Node>(theVtx->Index(), theVtx);
		auto node1 = node0;
		auto v = node0;
		Debug_Null_Pointer(node0);
	
		auto edges = wire->CmpEdge()->Edges();
		auto segment = 
			std::make_shared<Cad2d_RemoveNonManifold::Ring>
			(
				segId, std::move(node0),
				std::move(node1), std::move(edges)
				);
		Debug_Null_Pointer(segment);

		v->Insert(segId, segment);
		return std::move(segment);
	}
}

void tnbLib::Cad2d_RemoveNonManifold::RetrieveManifoldRings()
{
	auto& nodesMap = theManifolds_;
	auto& Ids = theSegmentCounter_;

	while (nodesMap.size())
	{
		auto iter = nodesMap.begin();
		Debug_Null_Pointer(iter->second);

		auto ring = RetrieveRing(Ids.RetrieveIndex(), iter->second);
		auto nodes = Pln_Tools::RetrieveVertices(ring->Edges());

		for (const auto& x : nodes)
		{
			Debug_Null_Pointer(x);
			Remove(x, nodesMap);
		}

		Import(std::move(ring));
	}
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
			const auto& vtx = edge0->FirstVtx();
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

	if (edge0->FirstVtx() IS_EQUAL v0)
	{
		edge0->FirstVtx()->InsertToEdges(edge0->Index(), edge0);
	}
	else if (edge0->LastVtx() IS_EQUAL v0)
	{
		edge0->LastVtx()->InsertToEdges(edge0->Index(), edge0);
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}

	if (edge1->FirstVtx() IS_EQUAL v1)
	{
		edge1->FirstVtx()->InsertToEdges(edge1->Index(), edge1);
	}
	else if (edge1->LastVtx() IS_EQUAL v1)
	{
		edge1->LastVtx()->InsertToEdges(edge1->Index(), edge1);
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
tnbLib::Cad2d_RemoveNonManifold::RetrieveCompundEdges() const
{
	std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> segments;
	segments.reserve(theSegments_.size());
	for (const auto& x : theSegments_)
	{
		Debug_Null_Pointer(x.second);
		segments.push_back(x.second);
	}
	return std::move(segments);
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
	if (verbose)
	{
		Info << endl;
		Info << "******* Detecting non-manifold features in a plane structure ********" << endl;
		Info << endl;
	}

	if (verbose)
	{
		Info << " - retrieving the nodes from the edges..." << endl;
		Info << " - nb. of edges = " << (int)Edges().size() << endl;
	}

	//- retrieving the nodes from the edges
	auto nodes = Pln_Tools::RetrieveVertices(Edges());

	if (verbose)
	{
		Info << " - the nodes are retrieved, successfully!" << endl;
		Info << " - nb. of the nodes = " << (int)nodes.size() << endl;
	}

	if (verbose)
	{
		Info << " - registering the non-manifold nodes into a map" << endl;
	}

	//- registering manifolds and non-manifold nodes
	InsertVertices(nodes);

	if (verbose)
	{
		Info << " - calculating nb. of the rings..." << endl;
	}

	auto k = 0;
	auto nbRings = (Standard_Integer)0;
	Standard_Boolean Do = Standard_True;
	do 
	{ //- iterator continues while there is a ring

		if (verbose)
		{
			++k;
			Info << " - cycle nb. " << k << ": " << endl;
		}

		//- the detected rings will be registered and non-ring segments will be retrieved
		//- no non-ring segment is registered at the moment.
		auto[rings, segments]  = InsertEdges();

		RemoveManifols(rings);
		RemoveManifols(segments);

		if (Segments().size() > nbRings)
		{  // this means still some rings have been detected and the algorithm must be continued
			nbRings = (Standard_Integer)Segments().size();  //- save the nb. of the rings

			if (verbose)
			{
				Info << endl;
				Info << " - " << nbRings << " nb. of rings have been detected." << endl;
				Info << " - " << segments.size() << " nb. of segments have been detected." << endl;
				Info << endl;
			}

			for (const auto& x : segments)
			{
				AttachEdgesToNodes(x);
			}
		}
		else
		{ //- no more ring has been detected and the algorithm will be stopped
			Do = Standard_False;

			if (verbose)
			{
				Info << endl;
				Info << " - no more ring has been detected." << endl;
				Info << endl;
			}

			//- registering the non-ring segments at the end
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

	RetrieveManifoldRings();

	if (verbose)
	{
		Info << endl;
		Info << " - there are " << nbRings << " nb. of rings have been detected." << endl;
		Info << " - total nb. of segments: " << Segments().size();
		Info << endl;
		Info << "******* End of the Detecting non-manifold features in a plane structure ********" << endl;
		Info << endl;
	}

	Change_IsDone() = Standard_True;
}