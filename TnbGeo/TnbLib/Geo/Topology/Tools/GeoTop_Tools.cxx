#include <GeoTop_Tools.hxx>

#include <GeoTop2d_Element.hxx>
#include <GeoTop2d_Edge.hxx>
#include <GeoTop2d_Halfedge.hxx>
#include <GeoTop2d_Vertex.hxx>
#include <GeoTop2d_Point3d.hxx>
#include <Geo_AdTree.hxx>
#include <Entity3d_Triangulation.hxx>
#include <Entity3d_Box.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <set>

#include <TecPlot.hxx>
#include <Entity3d_Chain.hxx>

std::vector<std::shared_ptr<tnbLib::GeoTop2d_Vertex>> 
tnbLib::GeoTop_Tools::MakeVertices
(
	const std::vector<Pnt3d>& thePoints
)
{
	std::vector<std::shared_ptr<GeoTop2d_Vertex>> nodes;
	nodes.reserve(thePoints.size());

	Standard_Integer k = 0;
	for (const auto& x : thePoints)
	{
		auto pt = std::make_shared<GeoTop2d_Point3d>(x);
		auto node = std::make_shared<GeoTop2d_Vertex>(++k, std::move(pt));
		nodes.push_back(std::move(node));
	}
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::GeoTop2d_Element>> 
tnbLib::GeoTop_Tools::MakeElements
(
	const Entity3d_Triangulation& theTris
)
{
	const auto& points = theTris.Points();
	const auto& triangles = theTris.Connectivity();

	const auto nodes = MakeVertices(points);

	std::vector<std::shared_ptr<GeoTop2d_Element>> elements;
	elements.reserve(triangles.size());

	Standard_Integer nbDegens = 0;
	Standard_Integer k = 0;
	for (const auto& x : triangles)
	{
		auto v0 = x.Value(0) - 1;
		auto v1 = x.Value(1) - 1;
		auto v2 = x.Value(2) - 1;

		if (x.IsDegenerated())
		{
			/*FatalErrorIn(FunctionSIG)
				<< "degenerated triangle has been detected!" << endl
				<< " - v0: " << v0 << endl
				<< " - v1: " << v1 << endl
				<< " - v2: " << v2 << endl
				<< abort(FatalError);*/
			nbDegens++;
			continue;
		}

		Debug_Null_Pointer(nodes.at(v0));
		Debug_Null_Pointer(nodes.at(v1));
		Debug_Null_Pointer(nodes.at(v2));

		std::array<std::shared_ptr<GeoTop2d_Vertex>, 3> nodeList = 
		{ nodes.at(v0), nodes.at(v1), nodes.at(v2) };
		auto element = 
			std::make_shared<GeoTop2d_Element>
			(++k, std::move(nodeList));
		elements.push_back(std::move(element));
	}
	if (nbDegens)
	{
		FatalErrorIn(FunctionSIG)
			<< "degenerated triangle has been detected!" << endl
			<< " - nb of degenerated elements: " << nbDegens << endl
			<< abort(FatalError);
	}
	return std::move(elements);
}

std::vector<std::shared_ptr<tnbLib::GeoTop2d_Element>>
tnbLib::GeoTop_Tools::CalcTopology
(
	const Entity3d_Triangulation& theTris
)
{
	auto elements = MakeElements(theTris);

	ConnectNodesAndElements(elements);

	MakeEdges(elements);

	ConnectElements(elements);

	return std::move(elements);
}

namespace tnbLib
{

	static auto cmpEdges =
		[](
			const std::shared_ptr<GeoTop2d_Edge>& e0,
			const std::shared_ptr<GeoTop2d_Edge>& e1
			)
	{
		return e0->Index() < e1->Index();
	};

	std::shared_ptr<GeoTop2d_Vertex> NextNode(const std::shared_ptr<GeoTop2d_Vertex>& theVtx)
	{
		auto fwd = theVtx->ForwardBoundaryEdge();
		if (NOT fwd)
		{
			/*std::cout << "fwd = " << theVtx->ForwardBoundaryEdge() << std::endl;
			std::cout << "bwd = " << theVtx->BackwardBoundaryEdge() << std::endl;
			std::cout << "node = " << theVtx->Index() << std::endl;
			std::cout << "nb of bnd edges= " << theVtx->NbBoundaryEdges() << std::endl;
			for (const auto& x : theVtx->Edges())
			{
				auto edge = x.second.lock();
				std::cout << " - right elm: " << edge->RightElement() << std::endl;
				std::cout << " - left elm: " << edge->LeftElement() << std::endl;
				if (edge->IsOnBoundary())
				{
					std::cout << "YESSS" << std::endl;
					std::cout << "v0: " << edge->First()->Index() << " v1: " << edge->Second()->Index() << std::endl;
				}
			}*/
			FatalErrorIn(FunctionSIG)
				<< "the node is not boundary!" << endl
				<< abort(FatalError);
		}
		if (fwd->First() IS_EQUAL theVtx)
		{
			return fwd->Second();
		}
		else if (fwd->Second() IS_EQUAL theVtx)
		{
			return fwd->First();
		}
		else
		{
			FatalErrorIn(FunctionSIG)
				<< "unspecified situation has been detected." << endl
				<< abort(FatalError);
			return nullptr;
		}
		/*Debug_If_Condition(fwd->Second() IS_EQUAL theVtx);
		return fwd->Second();*/
	}

	auto TrackPolygon(std::set<std::shared_ptr<GeoTop2d_Edge>, decltype(cmpEdges)>& theEdges)
	{
		std::vector<std::shared_ptr<GeoTop2d_Vertex>> nodes;
		auto currentNode = (*theEdges.begin())->First();
		auto firstNode = currentNode;
		currentNode = NextNode(firstNode);
		nodes.push_back(firstNode);
		nodes.push_back(currentNode);
		//PAUSE;
		while (currentNode NOT_EQUAL firstNode)
		{
			//std::cout << "next... " << currentNode->Index() << std::endl;
			currentNode = NextNode(currentNode);
			nodes.push_back(currentNode);
		}
		//PAUSE;
		for (const auto& x : nodes)
		{
			auto bwd = x->BackwardBoundaryEdge();
			auto fwd = x->ForwardBoundaryEdge();
			{
				auto iter = theEdges.find(bwd);
				if (iter NOT_EQUAL theEdges.end())
				{
					theEdges.erase(iter);
				}
			}
			{
				auto iter = theEdges.find(fwd);
				if (iter NOT_EQUAL theEdges.end())
				{
					theEdges.erase(iter);
				}
			}
		}
		return std::move(nodes);
	}

	auto GetIndices(const std::vector<std::shared_ptr<GeoTop2d_Vertex>>& theNodes)
	{
		std::vector<connectivity::dual> indices;
		indices.reserve(theNodes.size());
		for (size_t i = 1; i < theNodes.size(); i++)
		{
			const auto& v0 = theNodes.at(i - 1);
			const auto& v1 = theNodes.at(i);

			connectivity::dual ids;
			ids.Value(0) = v0->Index();
			ids.Value(1) = v1->Index();
			indices.push_back(std::move(ids));
		}
		auto indicesPtr = std::make_shared<std::vector<tnbLib::connectivity::dual>>(std::move(indices));
		return std::move(indicesPtr);
	}
}

std::vector<std::shared_ptr<std::vector<tnbLib::connectivity::dual>>>
tnbLib::GeoTop_Tools::CalcBoundaries
(
	const std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements
)
{
	// retrieve boundary edges [2/19/2023 Payvand]
	std::set<std::shared_ptr<GeoTop2d_Edge>, decltype(cmpEdges)>
		edgeSet(cmpEdges);
	for (const auto& x : theElements)
	{
		const auto& edges = x->Edges();
		for (const auto& e : edges)
		{
			if (e->IsOnBoundary())
			{
				//if (e->First()->NbBoundaryEdges() NOT_EQUAL 2) continue;
				//if (e->Second()->NbBoundaryEdges() NOT_EQUAL 2) continue;
				edgeSet.insert(e);
			}
		}
	}
	/*{
		std::vector<Pnt3d> pnts;
		for (const auto& x : edgeSet)
		{
			const auto& v0 = x->First();
			const auto& v1 = x->Second();

			auto p0 = std::dynamic_pointer_cast<GeoTop2d_Point3d>(v0->Point())->Coord();
			auto p1 = std::dynamic_pointer_cast<GeoTop2d_Point3d>(v1->Point())->Coord();

			pnts.push_back(std::move(p0));
			pnts.push_back(std::move(p1));
		}
		auto ids = dualConnectivityList(edgeSet.size());

		OFstream myFile("chain.plt");
		Entity3d_Chain ch(pnts, ids);
		ch.ExportToPlt(myFile);
	}*/
	for (const auto& x : edgeSet)
	{
		if (x->First()->NbBoundaryEdges() NOT_EQUAL 2)
		{
			FatalErrorIn(FunctionSIG)
				<< "the mesh is not manifold." << endl
				<< " - index: " << x->First()->Index() << endl
				<< abort(FatalError);
		}
	}
	std::vector<std::shared_ptr<std::vector<tnbLib::connectivity::dual>>> indices;
	//std::cout << "size: " << edgeSet.size() << std::endl;
	while (edgeSet.size())
	{
		auto poly = ::tnbLib::TrackPolygon(edgeSet);
		auto ids = ::tnbLib::GetIndices(poly);
		//std::cout << "size: " << edgeSet.size() << std::endl;
		/*for (const auto& x : *ids)
		{
			std::cout << x.Value(0) << " , " << x.Value(1) << std::endl;
		}
		PAUSE;*/
		indices.push_back(std::move(ids));
	}
	return std::move(indices);
}

void tnbLib::GeoTop_Tools::MakeEdges
(
	const std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements
)
{
	Standard_Integer nbEdges = 0;
	for (const auto& e : theElements)
	{
		for (int i = 0; i < 3; i++)
		{
			auto id1 = (i + 1) % 3;
			auto id2 = (id1 + 1) % 3;

			const auto& node1 = e->Vertex(id1);
			const auto& node2 = e->Vertex(id2);

			std::shared_ptr<GeoTop2d_Edge> currentEdge;

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

				std::shared_ptr<GeoTop2d_Vertex> currentNode;
				std::shared_ptr<GeoTop2d_Vertex> otherNode;
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
				for (const auto& x : currentNode->Edges())
				{
					auto edge = x.second.lock();
					Debug_Null_Pointer(edge);

					if (edge->First() IS_EQUAL otherNode OR edge->Second() IS_EQUAL otherNode)
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
				currentEdge = std::make_shared<GeoTop2d_Edge>(++nbEdges, node1, node2);
				currentEdge->SetLeftElement(e);

				node1->InsertToEdges(currentEdge->Index(), currentEdge);
				node2->InsertToEdges(currentEdge->Index(), currentEdge);
			}
			e->EdgesRef().at(i) = currentEdge;
		}
	}
}

void tnbLib::GeoTop_Tools::ConnectNodesAndElements
(
	const std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);

		Debug_Null_Pointer(x->Vtx0());
		Debug_Null_Pointer(x->Vtx1());
		Debug_Null_Pointer(x->Vtx2());

		x->Vtx0()->InsertToElements(x->Index(), x);
		x->Vtx1()->InsertToElements(x->Index(), x);
		x->Vtx2()->InsertToElements(x->Index(), x);
	}
}

void tnbLib::GeoTop_Tools::ConnectElements
(
	const std::vector<std::shared_ptr<GeoTop2d_Element>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		auto& element = *x;

		Debug_Null_Pointer(element.Edge0());
		const auto& edge0 = element.Edge0();

		element.SetNeighbor0(edge0->LeftElement());
		if (edge0->LeftElement() IS_EQUAL x) element.SetNeighbor0(edge0->RightElement());

		Debug_Null_Pointer(element.Edge1());
		const auto& edge1 = element.Edge1();

		element.SetNeighbor1(edge1->LeftElement());
		if (edge1->LeftElement() IS_EQUAL x) element.SetNeighbor1(edge1->RightElement());

		Debug_Null_Pointer(element.Edge2());
		const auto& edge2 = element.Edge2();

		element.SetNeighbor2(edge2->LeftElement());
		if (edge2->LeftElement() IS_EQUAL x) element.SetNeighbor2(edge2->RightElement());
	}
}