#include "tools.hxx"

#include <Aft2d_Element.hxx>
#include <Aft2d_SegmentEdge.hxx>
#include <Aft2d_SegmentNode.hxx>
#include <Aft2d_Node.hxx>
#include <Mesh_PlnCurve.hxx>
#include <MeshBLayer2d_Offset.hxx>
#include <Geo2d_OffsetPolygon_Exterior.hxx>
#include <Global_Tools.hxx>

#ifdef Handle
#undef Handle
#endif
#include <Entity2d_PolygonTools.hxx>

#include <set>

std::vector<std::shared_ptr<tnbLib::Aft2d_Node>> 
tnbLib::tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<Aft2d_Node>& n0, const std::shared_ptr<Aft2d_Node>& n1)
	{
		return n0->Index() < n1->Index();
	};
	std::set<std::shared_ptr<Aft2d_Node>, decltype(cmp)> comp_nodes(cmp);
	for (const auto& x : theEdges)
	{
		comp_nodes.insert(x->Node0());
		comp_nodes.insert(x->Node1());
	}
	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	std::copy(comp_nodes.begin(), comp_nodes.end(), std::back_inserter(nodes));
	std::sort
	(
		nodes.begin(),
		nodes.end(),
		[](
			const std::shared_ptr<Aft2d_Node>& n0,
			const std::shared_ptr<Aft2d_Node>& n1
			) {return n0->Index() < n1->Index(); }
	);
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::SupEdge>> 
tnbLib::tools::RetrieveSupEdges
(
	const std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>& theEdges
)
{
	// retrieving the nodes
	const auto nodes = RetrieveNodes(theEdges);
	std::cout << "nb nodes= " << nodes.size() << std::endl;
	std::map<Standard_Integer, std::shared_ptr<SupNode>> sup_nodes;
	// Creating the super nodes
	for (const auto& x : nodes)
	{
		auto node = std::make_shared<SupNode>(x->Index(), x);
		Global_Tools::InsertIgnoreDup(node->Index(), node, sup_nodes);
	}
	std::vector<std::shared_ptr<SupEdge>> sup_edges;
	// Creating the super edges
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto edge = 
			std::make_shared<SupEdge>
		(
			x->Index(), 
			sup_nodes.at(n0->Index()),
			sup_nodes.at(n1->Index())
			);
		sup_nodes.at(n0->Index())->SetForward(edge);
		sup_nodes.at(n1->Index())->SetBackward(edge);
		sup_edges.emplace_back(std::move(edge));
	}
	return std::move(sup_edges);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::RetrievePolygon
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	const auto start = FirstItem(theEdges)->Node0();
	Debug_Null_Pointer(start);
	const auto nodes = TrackNodes(start);
	if (nodes.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid polygon." << endl
			<< abort(FatalError);
	}
	std::vector<Pnt2d> coords;
	coords.reserve(nodes.size() + 1);
	for (size_t i = 0; i < nodes.size(); i++)
	{
		coords.emplace_back(nodes.at(i)->Coord());
	}
	coords.emplace_back(FirstItem(nodes)->Coord());
	auto poly = std::make_shared<Entity2d_Polygon>
	(std::move(coords), 0);
	return std::move(poly);
}

std::vector<std::shared_ptr<tnbLib::SupNode>>
tnbLib::tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	const auto start = FirstItem(theEdges)->Node0();
	Debug_Null_Pointer(start);
	const auto nodes = TrackNodes(start);
	if (nodes.size() < 3)
	{
		FatalErrorIn(FunctionSIG)
			<< "Invalid polygon." << endl
			<< abort(FatalError);
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::SupNode>>
tnbLib::tools::TrackNodes
(
	const std::shared_ptr<SupNode>& theNode
)
{
	std::vector<std::shared_ptr<SupNode>> nodes;
	auto start = theNode;
	nodes.emplace_back(start);
	auto next = start->Next();
	while (next NOT_EQUAL start)
	{
		nodes.emplace_back(next);
		next = next->Next();
		if (NOT next)
		{
			break;
		}
	}
	return std::move(nodes);
}

std::map<Standard_Integer, std::shared_ptr<tnbLib::EdgeSet<tnbLib::Aft2d_SegmentEdge>>>
tnbLib::tools::RetrieveBoundaries(const std::vector<std::shared_ptr<Aft2d_SegmentEdge>>& theEdges)
{
	std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>> comp_edges;
	for (const auto& x: theEdges)
	{
		const auto curve = x->Curve().lock();
		if (NOT curve)
		{
			FatalErrorIn(FunctionSIG)
				<< "No curve has been assigned to the edge." << endl
				<< abort(FatalError);
		}
		const auto curve_id = curve->Index();
		if (auto iter = comp_edges.find(curve_id); iter IS_EQUAL comp_edges.end())
		{
			auto new_set = std::make_shared<EdgeSet<Aft2d_SegmentEdge>>();
			comp_edges.insert({ curve_id,std::move(new_set) });
		}
		comp_edges.at(curve_id)->edges.emplace_back(x);
	}
	return std::move(comp_edges);
}

std::vector<std::shared_ptr<tnbLib::WireSet<tnbLib::SupEdge>>>
tnbLib::tools::RetrieveWires
(
	const std::map<Standard_Integer, std::shared_ptr<EdgeSet<Aft2d_SegmentEdge>>>& theEdges,
	const std::set<Standard_Integer>& theIds
)
{
	std::vector<std::shared_ptr<Aft2d_SegmentEdge>> edges;
	for (const auto id:theIds)
	{
		const auto& selected = theEdges.at(id);
		for (const auto& x:selected->edges)
		{
			edges.emplace_back(x);
		}
	}
	// with the helps of the super edge concept I can be able to identify the wires
	const auto sup_edges = tools::RetrieveSupEdges(edges);
	// retrieve the wires
	const auto wires = RetrieveWires(sup_edges);
	/*
	 * Now we need to identify the inner wires
	 */
	std::vector<std::shared_ptr<WireSet<SupEdge>>> inner_wires;
	for (const auto& x:wires)
	{
		Debug_Null_Pointer(x);
		auto poly = RetrievePolygon(*x);
		if (Entity2d_PolygonTools::GetOrientation(*poly) IS_EQUAL Entity2d_PolygonOrientation::cw)
		{
			inner_wires.emplace_back(x);
		}
	}
	/*
	 * NOW, the inner wires have been identified
	 */
	return std::move(inner_wires);
}

std::vector<std::shared_ptr<tnbLib::WireSet<tnbLib::SupEdge>>>
tnbLib::tools::RetrieveWires
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	static auto cmp = [](const std::shared_ptr<SupEdge>& e0, const std::shared_ptr<SupEdge>& e1)
	{
		return e0->Index() < e1->Index();
	};
	std::set<std::shared_ptr<SupEdge>, decltype(cmp)> compare(cmp);
	for (const auto& x:theEdges)
	{
		compare.insert(x);
	}
	std::vector<std::shared_ptr<WireSet<SupEdge>>> wires;
	while (compare.size())
	{
		const auto edge = *compare.begin();
		auto start = edge->Node0();
		auto prev = start;
		auto next = start->Next();
		std::vector<std::shared_ptr<SupEdge>> sup_edges;
		Standard_Boolean is_wire = Standard_True;
		while (next NOT_EQUAL start)
		{
			sup_edges.emplace_back(prev->Forward().lock());
			if (NOT compare.erase(prev->Forward().lock()))
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "something went wrong: the item is not in the tree." << endl
					<< abort(FatalError);
			}
			prev = next;
			next = next->Next();
			if (NOT next)
			{
				is_wire = Standard_False;
				break;
			}
		}
		if (next)
		{
			sup_edges.emplace_back(prev->Forward().lock());
			if (NOT compare.erase(prev->Forward().lock()))
			{
				FatalErrorIn(FunctionSIG) << endl
					<< "something went wrong: the item is not in the tree." << endl
					<< abort(FatalError);
			}
		}
		if (is_wire)
		{
			auto wire_set_ref = WireSet<SupEdge>{ std::move(sup_edges) };
			auto wire_set = std::make_shared<WireSet<SupEdge>>(std::move(wire_set_ref));
			wires.emplace_back(std::move(wire_set));
		}
	}
	return std::move(wires);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::ClosePolygon(const Entity2d_Polygon& thePolygon)
{
	std::vector<Pnt2d> coords;
	coords.reserve(thePolygon.NbPoints() + 1);
	for (const auto& x:thePolygon.Points())
	{
		coords.emplace_back(x);
	}
	coords.emplace_back(coords.at(0));
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	return std::move(poly);
}

std::shared_ptr<tnbLib::Entity2d_Polygon>
tnbLib::tools::RetrievePolygon
(
	const WireSet<SupEdge>& theWire
)
{
	std::vector<Pnt2d> coords;
	for (const auto& x:theWire.edges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		Debug_Null_Pointer(n0);
		coords.emplace_back(n0->Coord());
	}
	auto poly = std::make_shared<Entity2d_Polygon>(std::move(coords), 0);
	return std::move(poly);
}

std::vector<std::shared_ptr<tnbLib::Entity2d_Polygon>>
tnbLib::tools::RetrieveInnerPolygons
(
	const std::vector<std::shared_ptr<WireSet<SupEdge>>>& theWires
)
{
	std::vector<std::shared_ptr<Entity2d_Polygon>> polygons;
	for (const auto& x:theWires)
	{
		Debug_Null_Pointer(x);
		auto poly = RetrievePolygon(*x);
		if (Entity2d_PolygonTools::GetOrientation(*poly) IS_EQUAL Entity2d_PolygonOrientation::cw)
		{
			polygons.emplace_back(std::move(poly));
		}
	}
	return std::move(polygons);
}

std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>
tnbLib::tools::CreateEdges(const Entity2d_Polygon& thePolygon)
{
	std::vector<std::shared_ptr<Aft2d_Node>> nodes;
	Standard_Integer nb_nodes = 0;
	const auto& coords = thePolygon.Points();
	for (size_t i = 0; i < coords.size() - 1; i++)
	{
		auto node = std::make_shared<Aft2d_SegmentNode>(++nb_nodes, coords.at(i));
		nodes.emplace_back(std::move(node));
	}
	nodes.emplace_back(FirstItem(nodes));
	Standard_Integer nb_edges = 0;
	std::vector<std::shared_ptr<Aft2d_SegmentEdge>> edges;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const auto& node0 = nodes.at(i - 1);
		const auto& node1 = nodes.at(i);
		auto segment = 
			std::make_shared<Aft2d_SegmentEdge>
		(++nb_edges, node0, node1);
		edges.emplace_back(std::move(segment));
	}
	return std::move(edges);
}


void tnbLib::tools::CheckWire
(
	const std::vector<std::shared_ptr<tnbLib::SupEdge>>& theEdges
)
{
	for (const auto& x:theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		if (NOT n0->IsManifold())
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not manifold." << endl
				<< abort(FatalError);
		}
		if (NOT n1->IsManifold())
		{
			FatalErrorIn(FunctionSIG)
				<< "the node is not manifold." << endl
				<< abort(FatalError);
		}
	}
}

Standard_Integer
tnbLib::SupNode::NbEdges() const
{
	Standard_Integer nb_edges = 0;
	if (HasBackward()) nb_edges++;
	if (HasForward()) nb_edges++;
	return nb_edges;
}

Standard_Boolean
tnbLib::SupNode::HasBackward() const
{
	return static_cast<Standard_Boolean>(theBackward_.lock());
}

Standard_Boolean
tnbLib::SupNode::HasForward() const
{
	return static_cast<Standard_Boolean>(theForward_.lock());
}

Standard_Boolean
tnbLib::SupNode::IsManifold() const
{
	return NbEdges() == 2;
}

tnbLib::Pnt2d
tnbLib::SupNode::Coord() const
{
	Debug_Null_Pointer(Node());
	return Node()->Coord();
}

std::shared_ptr<tnbLib::SupNode>
tnbLib::SupNode::Next() const
{
	if (const auto x = Forward().lock())
	{
		return x->Node1();
	}
	return nullptr;
}

std::pair
<
	std::vector<std::shared_ptr<tnbLib::Aft2d_SegmentEdge>>,
	std::shared_ptr<tnbLib::Entity2d_QuadMesh>
>
tnbLib::bndLayer::CalcBndLayer
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges,
	const Mesh_BndLayer_Info& theInfo
)
{
	// retrieving the polygon
	const auto polygon = tools::RetrievePolygon(theEdges);
	const auto nodes = tools::RetrieveNodes(theEdges);
	/*
	 * We need to reverse the polygon due to the fact that the offseting algorithm
	 * needs the polygon to be counter clockwise and we alredy know that an inner polygon is
	 * clockwise.
	 */
	polygon->Reverse(); // the polygon is reversed here.
	std::vector<std::shared_ptr<Entity2d_Polygon>> offsets;
	{
		const auto alg = 
			std::make_shared<Geo2d_OffsetPolygon_Exterior>
		(polygon, theInfo.OuterLayerThick());
		alg->Perform();
		offsets = alg->Offsets();
	}
	if (offsets.size() NOT_EQUAL 2)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "Unable to create boundary layer: Invalid type of boundary layer has been detected." << endl
			<< abort(FatalError);
	}
	/*
	 * according to the algorithm the second one should be the offset polygon.
	 */
	const auto offset = offsets.at(1);
	polygon->Reverse();
	offset->Reverse(); // We need to reverse it back.
	/*
	 * Calculating the offset nodes
	 */
	SetOffsets(nodes, *offset);
	//CalcOffsetEdges(theEdges);
	std::shared_ptr<Entity2d_QuadMesh> mesh;
	{
		const auto alg = std::make_shared<MeshBLayer2d_Offset>();
		alg->SetClusterSize(theInfo.NbLayars());
		alg->SetRate(theInfo.GrowthRate());
		alg->SetPolygon(polygon);
		alg->SetOffset(offset);
		alg->Perform();
		mesh = alg->Mesh();
	}
	return { tools::CreateEdges(*offset), mesh };
}

void tnbLib::bndLayer::SetOffsets
(
	const std::vector<std::shared_ptr<SupNode>>& theNodes, 
	const Entity2d_Polygon& thePoly
)
{
	const auto& pnts = thePoly.Points();
	for (size_t i = 0; i < theNodes.size(); i++)
	{
		const auto& x = theNodes.at(i);
		x->Node()->SetCoord(pnts.at(i));
		//auto node = std::make_shared<Aft2d_SegmentNode>(x->Index(), pnts.at(i));
		//x->SetOffset(std::move(node));
	}
}

void tnbLib::bndLayer::CalcOffsetEdges
(
	const std::vector<std::shared_ptr<SupEdge>>& theEdges
)
{
	for (const auto& x:theEdges)
	{
		Debug_Null_Pointer(x);
		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		auto seg = 
			std::make_shared<Aft2d_SegmentEdge>
		(x->Index(), n0->Offset(), n1->Offset());
		x->SetOffset(std::move(seg));
	}
}
