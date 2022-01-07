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

	return (i0 % 3) + 1 == i1;
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

			auto v1 = node1->Index();
			auto v2 = node2->Index();

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

std::vector<std::shared_ptr<tnbLib::Mesh2d_Element>> 
tnbLib::MeshBase_Tools::MakeMesh
(
	const Entity2d_Triangulation & theTri
)
{
	auto elements = MakeElements(theTri);

	ConnectNodesAndElements(elements);

	MakeEdges(elements);

	ConnectElements(elements);

	return std::move(elements);
}