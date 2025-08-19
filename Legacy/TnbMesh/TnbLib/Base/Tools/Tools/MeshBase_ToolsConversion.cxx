#include <MeshBase_Tools.hxx>

#include <Mesh2d_Element.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Node.hxx>
#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::MeshBase_Tools::IsSense
(
	const std::shared_ptr<Mesh2d_Element>& theElement, 
	const std::shared_ptr<Mesh2d_Edge>& theEdge
)
{
	const auto& n0 = theEdge->Node0();
	const auto& n1 = theEdge->Node1();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	const auto i0 = NodePos(theElement, n0);
	const auto i1 = NodePos(theElement, n1);

	return (i0 + 1) % 3 == i1;
}

Standard_Integer 
tnbLib::MeshBase_Tools::NodePos
(
	const std::shared_ptr<Mesh2d_Element>& theElement,
	const std::shared_ptr<Mesh2d_Node>& theNode
)
{
	if (theElement->Node0() IS_EQUAL theNode)
	{
		return 0;
	}
	else if (theElement->Node1() IS_EQUAL theNode)
	{
		return 1;
	}
	else if (theElement->Node2() IS_EQUAL theNode)
	{
		return 2;
	}
	else
	{
		FatalErrorIn(FunctionSIG)
			<< "the node doesn't belong to the element!" << endl
			<< abort(FatalError);
		return 0;
	}
}

//Standard_Boolean 
//tnbLib::MeshBase_Tools::IsSense
//(
//	const std::shared_ptr<Mesh3d_Facet>& theFace0,
//	const std::shared_ptr<Mesh3d_Facet>& theFace1
//)
//{
//	auto[i0, i1, i2] = Ids(*theFace0);
//	auto[j0, j1, j2] = Ids(*theFace1);
//
//	std::map<Standard_Integer, Standard_Integer> idsMap;
//	idsMap.insert(std::make_pair(i0, 1));
//	idsMap.insert(std::make_pair(i1, 2));
//	idsMap.insert(std::make_pair(i2, 3));
//
//	Standard_Integer id0, id1;
//	{
//		auto iter = idsMap.find(j0);
//		if (iter IS_EQUAL idsMap.end())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "the two triangles are not the same." << endl
//				<< abort(FatalError);
//		}
//		id0 = iter->second;
//	}
//	{
//		auto iter = idsMap.find(j1);
//		if (iter IS_EQUAL idsMap.end())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "the two triangles are not the same." << endl
//				<< abort(FatalError);
//		}
//		id1 = iter->second;
//	}
//	std::cout << std::endl;
//	std::cout << "i0 i1 i2: " << i0 << ", " << i1 << ", " << i2 << std::endl;
//	std::cout << "j0 j1 j2: " << j0 << ", " << j1 << ", " << j2 << std::endl;
//	std::cout << "id0 id1: " << id0 << ", " << id1 << std::endl;
//	std::cout << "sense: ";
//	return (id0 % 3 + 1) IS_EQUAL id1;
//}

Standard_Boolean 
tnbLib::MeshBase_Tools::IsSense
(
	const std::shared_ptr<Mesh3d_Facet>& theFacet, 
	const std::tuple
	<
	connectivity::triple, 
	connectivity::triple, 
	connectivity::triple,
	connectivity::triple
	>& theElementFaces)
{
	static auto retrieveIds = [](const connectivity::triple& t)
	{
		auto i0 = t.Value(0);
		auto i1 = t.Value(1);
		auto i2 = t.Value(2);
		auto t1 = std::make_tuple(i0, i1, i2);
		return std::move(t1);
	};

	const auto& f0 = std::get<0>(theElementFaces);
	const auto& f1 = std::get<1>(theElementFaces);
	const auto& f2 = std::get<2>(theElementFaces);
	const auto& f3 = std::get<3>(theElementFaces);

	{
		auto[i0, i1, i2] = retrieveIds(f0);
		if (IsCoincident(i0, i1, i2, *theFacet))
		{
			auto[j0, j1, j2] = Ids(*theFacet);
			std::map<Standard_Integer, Standard_Integer> idsMap;
			idsMap.insert(std::make_pair(i0, 1));
			idsMap.insert(std::make_pair(i1, 2));
			idsMap.insert(std::make_pair(i2, 3));

			Standard_Integer id0, id1;
			{
				auto iter = idsMap.find(j0);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id0 = iter->second;
			}
			{
				auto iter = idsMap.find(j1);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id1 = iter->second;
			}
			return (id0 % 3 + 1) IS_EQUAL id1;
		}
	}

	{
		auto[i0, i1, i2] = retrieveIds(f1);
		if (IsCoincident(i0, i1, i2, *theFacet))
		{
			auto[j0, j1, j2] = Ids(*theFacet);
			std::map<Standard_Integer, Standard_Integer> idsMap;
			idsMap.insert(std::make_pair(i0, 1));
			idsMap.insert(std::make_pair(i1, 2));
			idsMap.insert(std::make_pair(i2, 3));

			Standard_Integer id0, id1;
			{
				auto iter = idsMap.find(j0);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id0 = iter->second;
			}
			{
				auto iter = idsMap.find(j1);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id1 = iter->second;
			}
			return (id0 % 3 + 1) IS_EQUAL id1;
		}
	}

	{
		auto[i0, i1, i2] = retrieveIds(f2);
		if (IsCoincident(i0, i1, i2, *theFacet))
		{
			auto[j0, j1, j2] = Ids(*theFacet);
			std::map<Standard_Integer, Standard_Integer> idsMap;
			idsMap.insert(std::make_pair(i0, 1));
			idsMap.insert(std::make_pair(i1, 2));
			idsMap.insert(std::make_pair(i2, 3));

			Standard_Integer id0, id1;
			{
				auto iter = idsMap.find(j0);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id0 = iter->second;
			}
			{
				auto iter = idsMap.find(j1);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id1 = iter->second;
			}
			return (id0 % 3 + 1) IS_EQUAL id1;
		}
	}

	{
		auto[i0, i1, i2] = retrieveIds(f3);
		if (IsCoincident(i0, i1, i2, *theFacet))
		{
			auto[j0, j1, j2] = Ids(*theFacet);
			std::map<Standard_Integer, Standard_Integer> idsMap;
			idsMap.insert(std::make_pair(i0, 1));
			idsMap.insert(std::make_pair(i1, 2));
			idsMap.insert(std::make_pair(i2, 3));

			Standard_Integer id0, id1;
			{
				auto iter = idsMap.find(j0);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id0 = iter->second;
			}
			{
				auto iter = idsMap.find(j1);
				if (iter IS_EQUAL idsMap.end())
				{
					FatalErrorIn(FunctionSIG)
						<< "the two triangles are not the same." << endl
						<< abort(FatalError);
				}
				id1 = iter->second;
			}
			return (id0 % 3 + 1) IS_EQUAL id1;
		}
	}

	FatalErrorIn(FunctionSIG)
		<< "the face is not on the element." << endl
		<< abort(FatalError);
	return Standard_False;
}

Standard_Boolean 
tnbLib::MeshBase_Tools::IsSense
(
	const std::shared_ptr<Mesh3d_Element>& theElement,
	const std::shared_ptr<Mesh3d_Facet>& theFacet
)
{
	/*auto[i0, i1, i2] = Ids(*theFacet);
	auto facet = IsOnElement(i0, i1, i2, *theElement);
	if (NOT facet)
	{
		FatalErrorIn(FunctionSIG)
			<< "the facet is not on the element!" << endl
			<< abort(FatalError);
	}
	return IsSense(facet, theFacet);*/

	auto faces = FaceIds(*theElement);
	return IsSense(theFacet, faces);
}

Standard_Boolean 
tnbLib::MeshBase_Tools::IsCoincident
(
	const Standard_Integer i0,
	const Standard_Integer i1,
	const Standard_Integer i2, 
	const Mesh3d_Facet & theElement
)
{
	auto[j0, j1, j2] = Ids(theElement);
	std::set<Standard_Integer> idsSet;
	idsSet.insert(j0);
	idsSet.insert(j1);
	idsSet.insert(j2);

	{
		auto iter = idsSet.find(i0);
		if (iter IS_EQUAL idsSet.end())
		{
			return Standard_False;
		}
	}
	{
		auto iter = idsSet.find(i1);
		if (iter IS_EQUAL idsSet.end())
		{
			return Standard_False;
		}
	}
	{
		auto iter = idsSet.find(i2);
		if (iter IS_EQUAL idsSet.end())
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

std::shared_ptr<tnbLib::Mesh3d_Facet> 
tnbLib::MeshBase_Tools::IsOnElement
(
	const Standard_Integer i0, 
	const Standard_Integer i1, 
	const Standard_Integer i2,
	const Mesh3d_Element & theElement
)
{
	auto[f0, f1, f2, f3] = theElement.Facets();
	if (IsCoincident(i0, i1, i2, *f0))
	{
		return f0;
	}
	if (IsCoincident(i0, i1, i2, *f1))
	{
		return f1;
	}
	if (IsCoincident(i0, i1, i2, *f2))
	{
		return f2;
	}
	if (IsCoincident(i0, i1, i2, *f3))
	{
		return f3;
	}
	return nullptr;
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Node>> 
tnbLib::MeshBase_Tools::MakeNodes(const std::vector<Pnt2d>& thePoints)
{
	std::vector<std::shared_ptr<Mesh2d_Node>> nodes;
	nodes.reserve(thePoints.size());

	Standard_Integer k = 0;
	for (const auto& x : thePoints)
	{
		auto node = std::make_shared<Mesh2d_Node>(++k, x);
		nodes.push_back(std::move(node));
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Element>>
tnbLib::MeshBase_Tools::MakeElements
(
	const Entity2d_Triangulation & theTriangulation
)
{
	const auto& points = theTriangulation.Points();
	const auto& triangles = theTriangulation.Connectivity();

	const auto nodes = MakeNodes(points);

	std::vector<std::shared_ptr<Mesh2d_Element>> elements;
	elements.reserve(triangles.size());

	Standard_Integer k = 0;
	for (const auto& x : triangles)
	{
		auto v0 = x.Value(0) - 1;
		auto v1 = x.Value(1) - 1;
		auto v2 = x.Value(2) - 1;

		if (x.IsDegenerated())
		{
			FatalErrorIn(FunctionSIG)
				<< "degenerated triangle has been detected!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(nodes[v0]);
		Debug_Null_Pointer(nodes[v1]);
		Debug_Null_Pointer(nodes[v2]);

		auto element = std::make_shared<Mesh2d_Element>(++k, nodes[v0], nodes[v1], nodes[v2]);
		elements.push_back(std::move(element));
	}
	return std::move(elements);
}

std::vector<std::shared_ptr<tnbLib::Mesh3d_Facet>> 
tnbLib::MeshBase_Tools::RetrieveFacets
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto cmp = [](const std::shared_ptr<Mesh3d_Facet>& e0, const std::shared_ptr<Mesh3d_Facet>& e1)
	{
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		return e0->Index() < e1->Index();
	};

	std::set<std::shared_ptr<Mesh3d_Facet>, decltype(cmp)> mySet(cmp);
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto[f0, f1, f2, f3] = x->Facets();

		if (NOT mySet.insert(f0).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(f1).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(f2).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(f3).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
	std::vector<std::shared_ptr<Mesh3d_Facet>> facets;
	facets.reserve(mySet.size());
	for (const auto& x : mySet)
	{
		Debug_Null_Pointer(x);
		facets.push_back(x);
	}
	return std::move(facets);
}

std::vector<std::shared_ptr<tnbLib::Mesh3d_Edge>> 
tnbLib::MeshBase_Tools::RetrieveEdges
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto cmp = [](const std::shared_ptr<Mesh3d_Edge>& e0, const std::shared_ptr<Mesh3d_Edge>& e1)
	{
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		return e0->Index() < e1->Index();
	};

	std::set<std::shared_ptr<Mesh3d_Edge>, decltype(cmp)> mySet(cmp);
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto[e0, e1, e2, e3, e4, e5] = x->Edges();

		if (NOT mySet.insert(e0).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e1).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e2).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e3).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e4).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e5).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
	std::vector<std::shared_ptr<Mesh3d_Edge>> edges;
	edges.reserve(mySet.size());
	for (const auto& x : mySet)
	{
		Debug_Null_Pointer(x);
		edges.push_back(x);
	}
	return std::move(edges);
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Edge>>
tnbLib::MeshBase_Tools::RetrieveEdges
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	auto cmp = [](const std::shared_ptr<Mesh2d_Edge>& e0, const std::shared_ptr<Mesh2d_Edge>& e1)
	{
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		return e0->Index() < e1->Index();
	};

	std::set<std::shared_ptr<Mesh2d_Edge>, decltype(cmp)> mySet(cmp);
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto [e0, e1, e2] = x->Edges();

		if (NOT mySet.insert(e0).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e1).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT mySet.insert(e2).second)
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
	std::vector<std::shared_ptr<Mesh2d_Edge>> edges;
	edges.reserve(mySet.size());
	for (const auto& x : mySet)
	{
		Debug_Null_Pointer(x);
		edges.push_back(x);
	}
	return std::move(edges);
}

void tnbLib::MeshBase_Tools::MakeEdges
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	Standard_Integer nbEdges = 0;
	for (const auto& e : theElements)
	{
		for (int i = 0; i < (int)Mesh2d_Element::nbNodes; i++)
		{
			auto id1 = (i + 1) % 3;
			auto id2 = (id1 + 1) % 3;

			const auto& node1 = e->Node(id1);
			const auto& node2 = e->Node(id2);

			std::shared_ptr<Mesh2d_Edge> currentEdge;

			//auto v1 = node1->Index();
			//auto v2 = node2->Index();

			Standard_Boolean isCreated = Standard_False;
			if ((NOT node1->NbEdges()) OR(NOT node2->NbEdges()))
			{
				isCreated = Standard_True;
			}
			else
			{
				auto size1 = node1->NbEdges();
				auto size2 = node2->NbEdges();

				std::shared_ptr<Mesh2d_Node> currentNode;
				std::shared_ptr<Mesh2d_Node> otherNode;

				if (size1 <= size2)
				{
					currentNode = node1;
					otherNode = node2;
				}
				else
				{
					currentNode = node2;
					otherNode = node1;
				}

				Standard_Boolean isExist = Standard_False;

				for (const auto& x : currentNode->RetrieveEdges())
				{
					auto edge = x.second.lock();
					Debug_Null_Pointer(edge);

					if (edge->Node0() IS_EQUAL otherNode OR edge->Node1() IS_EQUAL otherNode)
					{
						isExist = Standard_True;
						currentEdge = edge;

						currentEdge->SetRightElement(e);
						if (NOT currentEdge->LeftElement().lock())
						{
							FatalErrorIn(FunctionSIG)
								<< "Contradictory Data" << endl
								<< abort(FatalError);
						}
						if (currentEdge->LeftElement().lock() IS_EQUAL e)
						{
							FatalErrorIn(FunctionSIG)
								<< "Contradictory Data" << endl
								<< abort(FatalError);
						}
						break;
					}
				}

				if (NOT isExist)
				{
					isCreated = Standard_True;
				}
			}

			if (isCreated)
			{
				if (currentEdge)
				{
					FatalErrorIn(FunctionSIG)
						<< "Contradictory Data: It's supposed to not be an edge!"
						<< abort(FatalError);
				}

				currentEdge = std::make_shared<Mesh2d_Edge>(++nbEdges, node1, node2);
				currentEdge->SetLeftElement(e);

				node1->InsertToEdges(currentEdge->Index(), currentEdge);
				node2->InsertToEdges(currentEdge->Index(), currentEdge);
			}

			e->Edge(i) = currentEdge;
		}
	}

	for (const auto& x : theElements)
	{
		auto [e0, e1, e2] = x->Edges();
		if (NOT e0->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid mesh" << endl
				<< abort(FatalError);
		}
		if (NOT e1->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid mesh" << endl
				<< abort(FatalError);
		}
		if (NOT e2->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "invalid mesh" << endl
				<< abort(FatalError);
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndElements
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());
		Debug_Null_Pointer(x->Node2());

		x->Node0()->InsertToElements(x->Index(), x);
		x->Node1()->InsertToElements(x->Index(), x);
		x->Node2()->InsertToElements(x->Index(), x);
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndEdges
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		const auto& e0 = x->Edge0();
		const auto& e1 = x->Edge1();
		const auto& e2 = x->Edge2();

		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		Debug_Null_Pointer(e2);

		auto e0Left = e0->LeftElement().lock();
		if (e0Left IS_EQUAL x)
		{
			e0->Node0()->InsertToEdges(e0->Index(), e0);
		}
		if (e0Left IS_EQUAL x)
		{
			e0->Node1()->InsertToEdges(e0->Index(), e0);
		}

		auto e1Left = e1->LeftElement().lock();
		if (e1Left IS_EQUAL x)
		{
			e1->Node0()->InsertToEdges(e1->Index(), e1);
		}
		if (e1Left IS_EQUAL x)
		{
			e1->Node1()->InsertToEdges(e1->Index(), e1);
		}

		auto e2Left = e2->LeftElement().lock();
		if (e2Left IS_EQUAL x)
		{
			e2->Node0()->InsertToEdges(e2->Index(), e2);
		}
		if (e2Left IS_EQUAL x)
		{
			e2->Node1()->InsertToEdges(e2->Index(), e2);
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectEdgesAndElements
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		const auto& e0 = x->Edge0();
		const auto& e1 = x->Edge1();
		const auto& e2 = x->Edge2();

		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		Debug_Null_Pointer(e2);

		if (IsSense(x, e0))
		{
			e0->SetLeftElement(x);
		}
		else
		{
			e0->SetRightElement(x);
		}

		if (IsSense(x, e1))
		{
			e1->SetLeftElement(x);
		}
		else
		{
			e1->SetRightElement(x);
		}

		if (IsSense(x, e2))
		{
			e2->SetLeftElement(x);
		}
		else
		{
			e2->SetRightElement(x);
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectElements
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto& element = *x;

		Debug_Null_Pointer(element.Edge0());
		const auto& edge0 = element.Edge0();

		element.SetNeighbor0(edge0->LeftElement());
		if (edge0->LeftElement().lock() IS_EQUAL x) element.SetNeighbor0(edge0->RightElement());

		Debug_Null_Pointer(element.Edge1());
		const auto& edge1 = element.Edge1();

		element.SetNeighbor1(edge1->LeftElement());
		if (edge1->LeftElement().lock() IS_EQUAL x) element.SetNeighbor1(edge1->RightElement());

		Debug_Null_Pointer(element.Edge2());
		const auto& edge2 = element.Edge2();

		element.SetNeighbor2(edge2->LeftElement());
		if (edge2->LeftElement().lock() IS_EQUAL x) element.SetNeighbor2(edge2->RightElement());
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndElements
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());
		Debug_Null_Pointer(x->Node2());
		Debug_Null_Pointer(x->Node3());

		if (NOT x->Node0()->InsertToElements(x->Index(), x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT x->Node1()->InsertToElements(x->Index(), x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT x->Node2()->InsertToElements(x->Index(), x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT x->Node3()->InsertToElements(x->Index(), x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndFacets
(
	const std::vector<std::shared_ptr<Mesh3d_Facet>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());
		Debug_Null_Pointer(x->Node2());

		auto id = x->Index();
		if (NOT x->Node0()->InsertToFacets(id, x))
		{
			// duplicate data; do nothing! [9/15/2022 Amir]
		}

		if (NOT x->Node1()->InsertToFacets(id, x))
		{
			// duplicate data; do nothing! [9/15/2022 Amir]
		}

		if (NOT x->Node2()->InsertToFacets(id, x))
		{
			// duplicate data; do nothing! [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndFacets
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto facets = RetrieveFacets(theElements);
	ConnectNodesAndFacets(facets);
}

void tnbLib::MeshBase_Tools::ConnectNodesAndEdges
(
	const std::vector<std::shared_ptr<Mesh3d_Edge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);

		auto id = x->Index();

		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());

		if (NOT x->Node0()->InsertToEdges(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT x->Node1()->InsertToEdges(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndEdges
(
	const std::vector<std::shared_ptr<Mesh2d_Edge>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);

		auto id = x->Index();

		Debug_Null_Pointer(x->Node0());
		Debug_Null_Pointer(x->Node1());

		if (NOT x->Node0()->InsertToEdges(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT x->Node1()->InsertToEdges(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectNodesAndEdges
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto edges = RetrieveEdges(theElements);
	ConnectNodesAndEdges(edges);
}

void tnbLib::MeshBase_Tools::ConnectEdgesAndElements
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		auto id = x->Index();

		auto[e0, e1, e2, e3, e4, e5] = x->Edges();
		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		Debug_Null_Pointer(e2);
		Debug_Null_Pointer(e3);
		Debug_Null_Pointer(e4);
		Debug_Null_Pointer(e5);

		if (NOT e0->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e1->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e2->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e3->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e4->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e5->InsertToElements(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectEdgesAndFacets
(
	const std::vector<std::shared_ptr<Mesh3d_Facet>>& theFacets
)
{
	for (const auto& x : theFacets)
	{
		Debug_Null_Pointer(x);

		auto id = x->Index();
		auto[e0, e1, e2] = x->Edges();

		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		Debug_Null_Pointer(e2);

		if (NOT e0->InsertToFacets(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e1->InsertToFacets(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
		if (NOT e2->InsertToFacets(id, x))
		{
			// duplicate data; do nothing [9/15/2022 Amir]
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectEdgesAndFacets
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto facets = RetrieveFacets(theElements);
	ConnectEdgesAndFacets(facets);
}

void tnbLib::MeshBase_Tools::ConnectFacetsAndElements
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		auto id = x->Index();

		auto[f0, f1, f2, f3] = x->Facets();
		Debug_Null_Pointer(f0);
		Debug_Null_Pointer(f1);
		Debug_Null_Pointer(f2);
		Debug_Null_Pointer(f3);

		if (IsSense(x, f0))
		{
			f0->SetLowerElement(x);
		}
		else
		{
			f0->SetUpperElement(x);
		}

		if (IsSense(x, f1))
		{
			f1->SetLowerElement(x);
		}
		else
		{
			f1->SetUpperElement(x);
		}

		if (IsSense(x, f2))
		{
			f2->SetLowerElement(x);
		}
		else
		{
			f2->SetUpperElement(x);
		}

		if (IsSense(x, f3))
		{
			f3->SetLowerElement(x);
		}
		else
		{
			f3->SetUpperElement(x);
		}
	}
}

void tnbLib::MeshBase_Tools::ConnectElements
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto& element = *x;

		Debug_Null_Pointer(element.Facet0());
		const auto& f0 = element.Facet0();

		element.SetNeighbor0(f0->UpperElement());
		if (f0->UpperElement().lock() IS_EQUAL x) element.SetNeighbor0(f0->LowerElement());

		Debug_Null_Pointer(element.Facet1());
		const auto& f1 = element.Facet1();

		element.SetNeighbor1(f1->UpperElement());
		if (f1->UpperElement().lock() IS_EQUAL x) element.SetNeighbor1(f1->LowerElement());

		Debug_Null_Pointer(element.Facet2());
		const auto& f2 = element.Facet2();

		element.SetNeighbor2(f2->UpperElement());
		if (f2->UpperElement().lock() IS_EQUAL x) element.SetNeighbor2(f2->LowerElement());

		Debug_Null_Pointer(element.Facet3());
		const auto& f3 = element.Facet3();

		element.SetNeighbor3(f3->UpperElement());
		if (f3->UpperElement().lock() IS_EQUAL x) element.SetNeighbor3(f3->LowerElement());
	}
}

void tnbLib::MeshBase_Tools::ConnectMesh
(
	const std::vector<std::shared_ptr<Mesh3d_Element>>& theElements
)
{
	auto edges = RetrieveEdges(theElements);
	auto facets = RetrieveFacets(theElements);

	ConnectNodesAndElements(theElements);
	ConnectNodesAndFacets(facets);
	ConnectNodesAndEdges(edges);

	ConnectEdgesAndElements(theElements);
	ConnectEdgesAndFacets(facets);

	ConnectFacetsAndElements(theElements);

	ConnectElements(theElements);
}

void tnbLib::MeshBase_Tools::ConnectMesh
(
	const std::vector<std::shared_ptr<Mesh2d_Element>>& theElements
)
{
	auto edges = RetrieveEdges(theElements);

	ConnectNodesAndElements(theElements);
	ConnectNodesAndEdges(edges);

	ConnectEdgesAndElements(theElements);

	ConnectElements(theElements);
}

std::vector<std::shared_ptr<tnbLib::Mesh2d_Element>> 
tnbLib::MeshBase_Tools::MakeMesh
(
	const Entity2d_Triangulation & theTri
)
{
	auto elements = MakeElements(theTri);

	ConnectNodesAndElements(elements);

	MakeEdges(elements);

	//ConnectElements(elements);

	return std::move(elements);
}