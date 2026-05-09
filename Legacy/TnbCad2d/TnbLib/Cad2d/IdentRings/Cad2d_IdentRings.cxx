#include <Cad2d_IdentRings.hxx>

#include <Cad2d_IdentRings_Ring.hxx>
#include <Cad2d_IdentRings_Segment.hxx>
#include <Cad2d_IdentRings_Petal.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>

Standard_Boolean 
tnbLib::Cad2d_IdentRingsCache::ContainsNode
(
	const Standard_Integer theIndex
) const
{
	auto iter = theNodesCache_.find(theIndex);
	if (iter IS_EQUAL theNodesCache_.end())
	{
		return Standard_False;
	}
	return Standard_True;
}

std::shared_ptr<tnbLib::cad2dLib::IdentRings_Node> 
tnbLib::Cad2d_IdentRingsCache::FindNode
(
	const Standard_Integer theIndex
) const
{
	auto iter = theNodesCache_.find(theIndex);
	if (iter IS_EQUAL theNodesCache_.end())
	{
		return nullptr;
	}
	return iter->second;
}

void tnbLib::Cad2d_IdentRingsCache::ImportToNodes
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode
)
{
	auto node = theNode;
	ImportToNodes(std::move(node));
}

void tnbLib::Cad2d_IdentRingsCache::ImportToNodes
(
	std::shared_ptr<cad2dLib::IdentRings_Node>&& theNode
)
{
	auto paired = std::make_pair(theNode->Index(), std::move(theNode));
	auto insert = theNodesCache_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_IdentRingsCache::ImportToLinks
(
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
)
{
	auto link = theLink;
	ImportToLinks(std::move(link));
}

void tnbLib::Cad2d_IdentRingsCache::ImportToLinks
(
	std::shared_ptr<cad2dLib::IdentRings_Link>&& theLink
)
{
	auto paired = std::make_pair(theLink->Index(), std::move(theLink));
	auto insert = theLinksCache_.insert(std::move(paired));
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< " duplicate data has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_IdentRingsCache::RemoveNode
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);
	auto iter = theNodesCache_.find(theNode->Index());
	if (iter IS_EQUAL theNodesCache_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index: " << theNode->Index() << endl
			<< abort(FatalError);
	}
	theNodesCache_.erase(iter);
}

void tnbLib::Cad2d_IdentRingsCache::RemoveLink
(
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
)
{
	Debug_Null_Pointer(theLink);
	auto iter = theLinksCache_.find(theLink->Index());
	if (iter IS_EQUAL theLinksCache_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< "the item is not in the tree!" << endl
			<< " - index: " << theLink->Index() << endl
			<< abort(FatalError);
	}
	theLinksCache_.erase(iter);
}

//std::shared_ptr<tnbLib::cad2dLib::IdentRings_Node> 
//tnbLib::Cad2d_IdentRings::SearchFirstNode() const
//{
//	for (const auto& x : CacheData()->Nodes())
//	{
//		Debug_Null_Pointer(x.second);
//		const auto& node = x.second;
//
//		if (node->HasPetal())
//		{
//			return node;
//		}
//	}
//	return nullptr;
//}

std::shared_ptr<tnbLib::cad2dLib::IdentRings_Link>
tnbLib::Cad2d_IdentRings::CreateLink
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode,
	const std::shared_ptr<Pln_Edge>& theEdge
) const
{
	auto v0 = theNode->Vtx();
	Debug_Null_Pointer(v0);

	auto nextEdge = theEdge;
	auto nextVtx = Pln_Tools::NextNode(v0, nextEdge);

	std::vector<std::shared_ptr<Pln_Edge>> edges;
	edges.push_back(nextEdge);
	while (NOT CacheData()->ContainsNode(nextVtx->Index()))
	{
		nextEdge = Pln_Tools::NextEdge(nextEdge, nextVtx);
		edges.push_back(nextEdge);

		nextVtx = Pln_Tools::NextNode(nextVtx, nextEdge);
	}

	auto v1 = nextVtx;

	if (v0 IS_EQUAL v1)
	{
		auto node = theNode;
		auto link = std::make_shared<cad2dLib::IdentRings_Ring>(0, std::move(node), std::move(edges));
		return std::move(link);
	}
	else
	{
		auto node0 = theNode;
		auto node1 = CacheData()->FindNode(v1->Index());

		auto link = std::make_shared<cad2dLib::IdentRings_Segment>
			(0, std::move(node0), std::move(node1), std::move(edges));
		return std::move(link);
	}
}

std::vector<std::shared_ptr<tnbLib::cad2dLib::IdentRings_Link>> 
tnbLib::Cad2d_IdentRings::CreateLinks() const
{
	const auto& nodes = CacheData()->Nodes();
	
	std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>> links;
	Standard_Integer k = 0;
	for (const auto& x : nodes)
	{
		Debug_Null_Pointer(x.second);
		const auto& node = x.second;

		while (NOT node->IsOrphan())
		{
			auto dir = RetrieveDir(node);
			auto link = CreateLink(node, dir);

			link->SetIndex(++k);

			Detach(link);

			links.push_back(std::move(link));
		}
	}

	for (const auto& x : links)
	{
		reAttach(x);
	}

	Attach(links);

	return std::move(links);
}

std::shared_ptr<tnbLib::cad2dLib::IdentRings_Petal> 
tnbLib::Cad2d_IdentRings::FindAPetal()
{
	for (const auto& x : CacheData()->Nodes())
	{
		Debug_Null_Pointer(x.second);
		const auto& node = x.second;

		if (auto path = FindPetal(node))
		{
			return std::move(path);
		}
	}
	return nullptr;
}

void tnbLib::Cad2d_IdentRings::InsertVerticesToCache
(
	const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
)
{
	for (const auto& x : theVertices)
	{
		Debug_Null_Pointer(x);
		if (NOT x->IsManifold())
		{
			auto node = std::make_shared<cad2dLib::IdentRings_Node>(x->Index(), x);
			Debug_Null_Pointer(node);

			CacheData()->ImportToNodes(std::move(node));
		}
	}
}

void tnbLib::Cad2d_IdentRings::InsertLinksToCache
(
	const std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>>& theLinks
)
{
	for (const auto& x : theLinks)
	{
		Debug_Null_Pointer(x);

		CacheData()->ImportToLinks(x);
	}
}

void tnbLib::Cad2d_IdentRings::RemoveLink
(
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
)
{
	Debug_Null_Pointer(theLink);
	theLink->Detach();

	CacheData()->RemoveLink(theLink);
}

void tnbLib::Cad2d_IdentRings::RemoveDangles()
{
	auto& segmentsRef = SegmentsRef();
	std::vector<std::shared_ptr<cad2dLib::IdentRings_Node>> removes;
	for (const auto& x : CacheData()->Nodes())
	{
		Debug_Null_Pointer(x.second);
		const auto& node = x.second;

		if (node->IsDangle())
		{
			const auto& links = node->Links();
			Debug_If_Condition(links.size() NOT_EQUAL 1);

			auto link = links.begin()->second.lock();
			RemoveLink(link);

			if (link->IsRing())
			{
				FatalErrorIn(FunctionSIG)
					<< "a ring cannot be a dangle" << endl
					<< abort(FatalError);
			}

			auto seg = std::dynamic_pointer_cast<cad2dLib::IdentRings_Segment>(link);
			Debug_Null_Pointer(seg);

			segmentsRef.push_back(std::move(seg));

			removes.push_back(node);
		}
	}

	for (const auto& x : removes)
	{
		Debug_Null_Pointer(x);
		CacheData()->RemoveNode(x);
	}
}

std::shared_ptr<tnbLib::Pln_Edge> 
tnbLib::Cad2d_IdentRings::RetrieveDir
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);

	const auto& vtx = theNode->Vtx();
	Debug_Null_Pointer(vtx);

	const auto& edges = vtx->Edges();
	auto edge = edges.begin()->second.lock();
	return std::move(edge);
}

namespace tnbLib
{

	std::shared_ptr<cad2dLib::IdentRings_Node> 
		NextNode
		(
			const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode,
			const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
		)
	{
		Debug_Null_Pointer(theLink);
		if (theLink->IsRing())
		{
			return theNode;
		}

		Debug_Null_Pointer(theNode);

		auto seg = std::dynamic_pointer_cast<cad2dLib::IdentRings_Segment>(theLink);
		Debug_Null_Pointer(seg);

		const auto& v0 = seg->Node0();
		const auto& v1 = seg->Node1();

		Debug_Null_Pointer(v0);
		Debug_Null_Pointer(v1);

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

	std::shared_ptr<cad2dLib::IdentRings_Link> 
		NextEdge
		(
			const std::shared_ptr<cad2dLib::IdentRings_Link>& theEdge, 
			const std::shared_ptr<cad2dLib::IdentRings_Node>& theVtx
		)
	{
		const auto edges = theVtx->RetrieveLinks();
		if (edges.size() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "the vertex is not manifold" << endl
				<< abort(FatalError);
		}

		if (edges[0] IS_EQUAL theEdge)
		{
			return edges[1];
		}
		if (edges[1] IS_EQUAL theEdge)
		{
			return edges[0];
		}

		FatalErrorIn(FunctionSIG)
			<< "Unable to find the next edge" << endl
			<< abort(FatalError);
		return nullptr;
	}
}

std::shared_ptr<tnbLib::cad2dLib::IdentRings_Petal> 
tnbLib::Cad2d_IdentRings::FindPetal
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theNode
)
{
	Debug_Null_Pointer(theNode);

	const auto& links = theNode->Links();
	Debug_If_Condition(links.empty());

	for (const auto& x : links)
	{
		auto edge = x.second.lock();
		Debug_Null_Pointer(edge);

		auto[path, node0, node1] = MarchOnLinks(theNode, edge);
		if (node0 IS_EQUAL node1)
		{
			auto petal = std::make_shared<cad2dLib::IdentRings_Petal>(0, std::move(path), std::move(node0));
			return std::move(petal);
		}
	}
	return nullptr;
}

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::cad2dLib::IdentRings_Link>>, 
	std::shared_ptr<tnbLib::cad2dLib::IdentRings_Node>,
	std::shared_ptr<tnbLib::cad2dLib::IdentRings_Node>
>
tnbLib::Cad2d_IdentRings::MarchOnLinks
(
	const std::shared_ptr<cad2dLib::IdentRings_Node>& theVtx, 
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theEdge
)
{
	auto v0 = theVtx;
	auto nextEdge = theEdge;

	std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>> edges;
	edges.push_back(nextEdge);

	auto nextVtx = ::tnbLib::NextNode(theVtx, nextEdge);
	while (nextVtx->IsManifold())
	{
		nextEdge = ::tnbLib::NextEdge(nextEdge, nextVtx);
		edges.push_back(nextEdge);

		nextVtx = ::tnbLib::NextNode(nextVtx, nextEdge);
	}

	auto v1 = nextVtx;
	auto t = std::make_tuple(std::move(edges), std::move(v0), std::move(v1));
	return std::move(t);
}

void tnbLib::Cad2d_IdentRings::Detach
(
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
)
{
	if (theLink->IsRing())
	{
		auto x = std::dynamic_pointer_cast<cad2dLib::IdentRings_Ring>(theLink);
		Debug_Null_Pointer(x);

		const auto& node = x->Node();
		Debug_Null_Pointer(node);

		const auto& vtx = node->Vtx();
		Debug_Null_Pointer(vtx);

		{// detach the first edge [1/25/2022 Amir]
			const auto& edge = FirstItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->RemoveFromEdges(edge->Index());
		}

		{// detach the last edge [1/25/2022 Amir]
			const auto& edge = LastItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->RemoveFromEdges(edge->Index());
		}
	}
	else if (theLink->IsSegment())
	{
		auto x = std::dynamic_pointer_cast<cad2dLib::IdentRings_Segment>(theLink);
		Debug_Null_Pointer(x);

		{// detach the link from the node0 [1/25/2022 Amir]
			const auto& node = x->Node0();
			Debug_Null_Pointer(node);

			const auto& vtx = node->Vtx();
			Debug_Null_Pointer(vtx);

			const auto& edge = FirstItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->RemoveFromEdges(edge->Index());
		}

		{// detach the link from the node1 [1/25/2022 Amir]
			const auto& node = x->Node1();
			Debug_Null_Pointer(node);

			const auto& vtx = node->Vtx();
			Debug_Null_Pointer(vtx);

			const auto& edge = LastItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->RemoveFromEdges(edge->Index());
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of link has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_IdentRings::reAttach
(
	const std::shared_ptr<cad2dLib::IdentRings_Link>& theLink
)
{
	if (theLink->IsRing())
	{
		auto x = std::dynamic_pointer_cast<cad2dLib::IdentRings_Ring>(theLink);
		Debug_Null_Pointer(x);

		const auto& node = x->Node();
		Debug_Null_Pointer(node);

		const auto& vtx = node->Vtx();
		Debug_Null_Pointer(vtx);

		{// detach the first edge [1/25/2022 Amir]
			const auto& edge = FirstItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->InsertToEdges(edge->Index(), edge);
		}

		{// detach the last edge [1/25/2022 Amir]
			const auto& edge = LastItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->InsertToEdges(edge->Index(), edge);
		}
	}
	else if (theLink->IsSegment())
	{
		auto x = std::dynamic_pointer_cast<cad2dLib::IdentRings_Segment>(theLink);
		Debug_Null_Pointer(x);

		{// detach the link from the node0 [1/25/2022 Amir]
			const auto& node = x->Node0();
			Debug_Null_Pointer(node);

			const auto& vtx = node->Vtx();
			Debug_Null_Pointer(vtx);

			const auto& edge = FirstItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->InsertToEdges(edge->Index(), edge);
		}

		{// detach the link from the node1 [1/25/2022 Amir]
			const auto& node = x->Node1();
			Debug_Null_Pointer(node);

			const auto& vtx = node->Vtx();
			Debug_Null_Pointer(vtx);

			const auto& edge = LastItem(x->Edges());
			Debug_Null_Pointer(edge);

			vtx->InsertToEdges(edge->Index(), edge);
		}
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "invalid type of link has been detected!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_IdentRings::Attach
(
	const std::vector<std::shared_ptr<cad2dLib::IdentRings_Link>>& theLinks
)
{
	for (const auto& x : theLinks)
	{
		Debug_Null_Pointer(x);
		x->Attach();
	}
}

tnbLib::Cad2d_IdentRings::Cad2d_IdentRings
( 
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdges 
)
	: theEdges_(theEdges)
{
	theCache_ = std::make_shared<Cad2d_IdentRingsCache>();
}

void tnbLib::Cad2d_IdentRings::Perform()
{

	// retrieve the nodes from the edges [1/25/2022 Amir]
	const auto vertices = Pln_Tools::RetrieveVertices(Edges());

	InsertVerticesToCache(vertices);

	const auto links = CreateLinks();

	InsertLinksToCache(links);

	RemoveDangles();

	auto& petals = PetalsRef();
	while (CacheData()->NbNodes())
	{
		auto petal = FindAPetal();

		if (NOT petal)
		{
			FatalErrorIn(FunctionSIG)
				<< "Invalid topology of structure has been found!" << endl
				<< abort(FatalError);
		}

		petals.push_back(std::move(petal));
	}

	Change_IsDone() = Standard_True;
}