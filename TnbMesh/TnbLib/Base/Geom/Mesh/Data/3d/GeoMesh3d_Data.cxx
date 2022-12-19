#include <GeoMesh3d_Data.hxx>

#include <MeshBase_Tools.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Node.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_TetrahedralizationTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

//#define GeoMesh3d_Data_Construct_Debug

namespace tnbLib
{

	template<>
	void GeoMesh3d_Data::Construct(const triangulation& theTriangulation)
	{
		const auto& Points = theTriangulation.Points();
		const auto& Triangles = theTriangulation.Connectivity();

#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "nb of tris: " << Triangles.size() << std::endl;
		std::cout << "nb of points: " << Points.size() << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug
		
		std::vector<std::shared_ptr<Mesh3d_Node>> Nodes;
		Nodes.reserve(Points.size());

#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "create nodes..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

		// Creating the nodes
		Standard_Integer k = 0;
		for (const auto& x : Points)
		{
			auto node = std::make_shared<Mesh3d_Node>(++k, x);
			Nodes.push_back(std::move(node));
		}
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the nodes are created." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

		std::vector<std::shared_ptr<Mesh3d_Element>> elements;
		elements.reserve(Triangles.size());

#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "creating the elements..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

		// Creating the Elements
		k = 0;
		for (const auto& x : Triangles)
		{
			auto v0 = Index_Of(x.Value(0));
			auto v1 = Index_Of(x.Value(1));
			auto v2 = Index_Of(x.Value(2));
			auto v3 = Index_Of(x.Value(3));

			if (x.IsDegenerated())
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Triangle" << endl
					<< abort(FatalError);
			}

			Debug_Null_Pointer(Nodes.at(v0));
			Debug_Null_Pointer(Nodes.at(v1));
			Debug_Null_Pointer(Nodes.at(v2));
			Debug_Null_Pointer(Nodes.at(v3));

			auto element = std::make_shared<Mesh3d_Element>(++k, Nodes.at(v0), Nodes.at(v1), Nodes.at(v2), Nodes.at(v3));
			elements.push_back(element);

			element->Node0()->InsertToElements(element->Index(), element);
			element->Node1()->InsertToElements(element->Index(), element);
			element->Node2()->InsertToElements(element->Index(), element);
			element->Node3()->InsertToElements(element->Index(), element);
		}
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the elements are created." << std::endl;
		std::cout << "creating the edges..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

		// Create Edges
		Standard_Integer nbEdges = 0;
		for (const auto& element : elements)
		{
			forThose(I, 0, 5)
			{
				auto Id = Entity3d_TetrahedralizationTools::EdgeIndices(I);

				const auto& node1 = element->Node(Index_Of(Id.first));
				const auto& node2 = element->Node(Index_Of(Id.second));

				auto v1 = node1->Index();
				auto v2 = node2->Index();

				Standard_Boolean Created = Standard_False;
				std::shared_ptr<Mesh3d_Edge> current_edge;

				if ((NOT node1->NbEdges()) OR(NOT node2->NbEdges()))
				{
					Created = Standard_True;
				}
				else
				{
					auto size1 = node1->NbEdges();
					auto size2 = node2->NbEdges();

					std::shared_ptr<Mesh3d_Node> current;
					std::shared_ptr<Mesh3d_Node> other;

					if (size1 <= size2)
					{
						current = node1;
						other = node2;
					}
					else
					{
						current = node2;
						other = node1;
					}

					Standard_Boolean exist = Standard_False;
					for (const auto& x : current->RetrieveEdges())
					{
						auto edge = x.second.lock();
						Debug_Null_Pointer(edge);

						if (edge->Node0() IS_EQUAL other OR edge->Node1() IS_EQUAL other)
						{
							exist = Standard_True;
							current_edge = edge;

							current_edge->InsertToElements(element->Index(), element);
							break;
						}
					}

					if (NOT exist)
					{
						Created = Standard_True;
					}
				}

				if (Created)
				{
					if (current_edge)
					{
						FatalErrorIn("void AutLib::GeoMesh3d_Data::Construct()")
							<< "Contradictory Data: It's supposed to not be an edge!"
							<< abort(FatalError);
					}

					current_edge = std::make_shared<Mesh3d_Edge>(++nbEdges, node1, node2);
					current_edge->InsertToElements(element->Index(), element);

					node1->InsertToEdges(current_edge->Index(), current_edge);
					node2->InsertToEdges(current_edge->Index(), current_edge);
				}
				element->SetEdge(I, current_edge);
			}
		}
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the edges are created." << std::endl;
		std::cout << "creating the facets..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug
		// Create Facets
		Standard_Integer nbFacets = 0;
		for (const auto& element : elements)
		{
			forThose(I, 0, 3)
			{
				auto Id = Entity3d_TetrahedralizationTools::FacetIndices(I);

				const auto& node1 = element->Node(Index_Of(std::get<0>(Id)));
				const auto& node2 = element->Node(Index_Of(std::get<1>(Id)));
				const auto& node3 = element->Node(Index_Of(std::get<2>(Id)));

				std::shared_ptr<facetType> current_facet;

				auto v1 = node1->Index();
				auto v2 = node2->Index();
				auto v3 = node3->Index();

				Standard_Boolean Created = Standard_False;
				if ((NOT node1->NbFacets()) OR(NOT node2->NbFacets()) OR(NOT node3->NbFacets()))
				{
					Created = Standard_True;
				}
				else
				{
					auto size1 = node1->NbFacets();
					auto size2 = node2->NbFacets();
					auto size3 = node3->NbFacets();

					std::shared_ptr<nodeType> current;
					if (size1 <= size2 AND size1 <= size3)
					{
						current = node1;
					}
					else if (size2 <= size1 AND size2 <= size3)
					{
						current = node2;
					}
					else
					{
						current = node3;
					}

					Standard_Boolean exist = Standard_False;

					for (const auto& x : current->RetrieveFacets())
					{
						Debug_Null_Pointer(x.second.lock());
						auto facet_p = x.second.lock();
						const auto& facet = *facet_p;

						Debug_Null_Pointer(facet.Node0());
						Debug_Null_Pointer(facet.Node1());
						Debug_Null_Pointer(facet.Node2());

						if (
							Geo_Tools::IsPairedTwoTriangles
							(
								node1->Index(),
								node2->Index(),
								node3->Index(),
								facet.Node0()->Index(),
								facet.Node1()->Index(), facet.Node2()->Index()
							)
							)
						{
							exist = Standard_True;
							current_facet = facet_p;
							//std::cout << "left element is detected." << std::endl;
							current_facet->SetLeftElement(element);

							break;
						}
					}

					if (NOT exist)
						Created = Standard_True;
				}

				if (Created)
				{
					if (current_facet)
					{
						FatalErrorIn("void AutLib::GeoMesh3d_Data::Construct()")
							<< "Contradictory Data: It's supposed to not be a facet!"
							<< abort(FatalError);
					}

					current_facet = std::make_shared<Mesh3d_Facet>(++nbFacets, node1, node2, node3);
					Debug_Null_Pointer(current_facet);

					current_facet->SetRightElement(element);

					node1->InsertToFacets(current_facet->Index(), current_facet);
					node2->InsertToFacets(current_facet->Index(), current_facet);
					node3->InsertToFacets(current_facet->Index(), current_facet);

					if (auto edge1 = MeshBase_Tools::FindEdge(*node2, *node3))
					{
						current_facet->SetEdge0(edge1);
						edge1->InsertToFacets(current_facet->Index(), current_facet);
					}
					else
					{
						FatalErrorIn(FunctionSIG)
							<< "no edge has been detected." << endl
							<< abort(FatalError);
					}

					if (auto edge2 = MeshBase_Tools::FindEdge(*node3, *node1))
					{
						current_facet->SetEdge1(edge2);
						edge2->InsertToFacets(current_facet->Index(), current_facet);
					}
					else
					{
						FatalErrorIn(FunctionSIG)
							<< "no edge has been detected." << endl
							<< abort(FatalError);
					}
					
					if (auto edge3 = MeshBase_Tools::FindEdge(*node1, *node2))
					{
						current_facet->SetEdge2(edge3);
						edge3->InsertToFacets(current_facet->Index(), current_facet);
					}
					else
					{
						FatalErrorIn(FunctionSIG)
							<< "no edge has been detected." << endl
							<< abort(FatalError);
					}
				}
				element->SetFacet(I, current_facet);
			}
		}
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the facets are created." << std::endl;
		std::cout << "Identifying the neighbors..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

		// Identifying the Neighbors
		for (const auto& x : elements)
		{
			Debug_Null_Pointer(x);
			auto& element = *x;

			Debug_Null_Pointer(element.Facet0());
			const auto& face0 = element.Facet0();

			element.SetNeighbor0(face0->LeftElement());
			if (face0->LeftElement().lock() IS_EQUAL x) element.SetNeighbor0(face0->RightElement());

			Debug_Null_Pointer(element.Facet1());
			const auto& face1 = element.Facet1();

			element.SetNeighbor1(face1->LeftElement());
			if (face1->LeftElement().lock() IS_EQUAL x) element.SetNeighbor1(face1->RightElement());

			Debug_Null_Pointer(element.Facet2());
			const auto& face2 = element.Facet2();

			element.SetNeighbor2(face2->LeftElement());
			if (face2->LeftElement().lock() IS_EQUAL x) element.SetNeighbor2(face2->RightElement());

			Debug_Null_Pointer(element.Facet3());
			const auto& face3 = element.Facet3();

			element.SetNeighbor3(face3->LeftElement());
			if (face3->LeftElement().lock() IS_EQUAL x) element.SetNeighbor3(face3->RightElement());
		}
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the neighbors are created." << std::endl;
		std::cout << "checking the facets..." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug

#ifdef _DEBUG
		// check the facets [8/4/2022 Amir]
		for (const auto& x : elements)
		{
			Debug_Null_Pointer(x);
			auto[f0, f1, f2, f3] = x->Facets();
			{
				auto leftElement = f0->LeftElement().lock();
				/*if (NOT leftElement)
				{
					std::cout << " - boundary facet: " << f0->Index() << std::endl;
				}*/
				if (leftElement NOT_EQUAL x)
				{
					auto rightElement = f0->RightElement().lock();
					if (rightElement NOT_EQUAL x)
					{
						FatalErrorIn(FunctionSIG)
							<< "invalid data structure has been detected." << endl
							<< " - element: " << x->Index() << endl
							<< " - left element: " << leftElement->Index() << endl
							<< " - right element: " << rightElement->Index() << endl
							<< abort(FatalError);
					}
				}
			}
			{
				auto leftElement = f1->LeftElement().lock();
				/*if (NOT leftElement)
				{
					std::cout << " - boundary facet: " << f1->Index() << std::endl;
				}*/
				if (leftElement NOT_EQUAL x)
				{
					auto rightElement = f1->RightElement().lock();
					if (rightElement NOT_EQUAL x)
					{
						FatalErrorIn(FunctionSIG)
							<< "invalid data structure has been detected." << endl
							<< " - element: " << x->Index() << endl
							<< " - left element: " << leftElement->Index() << endl
							<< " - right element: " << rightElement->Index() << endl
							<< abort(FatalError);
					}
				}
			}
			{
				auto leftElement = f2->LeftElement().lock();
				/*if (NOT leftElement)
				{
					std::cout << " - boundary facet: " << f2->Index() << std::endl;
				}*/
				if (leftElement NOT_EQUAL x)
				{
					auto rightElement = f2->RightElement().lock();
					if (rightElement NOT_EQUAL x)
					{
						FatalErrorIn(FunctionSIG)
							<< "invalid data structure has been detected." << endl
							<< " - element: " << x->Index() << endl
							<< " - left element: " << leftElement->Index() << endl
							<< " - right element: " << rightElement->Index() << endl
							<< abort(FatalError);
					}
				}
			}
			{
				auto leftElement = f3->LeftElement().lock();
				/*if (NOT leftElement)
				{
					std::cout << " - boundary facet: " << f3->Index() << std::endl;
				}*/
				if (leftElement NOT_EQUAL x)
				{
					auto rightElement = f3->RightElement().lock();
					if (rightElement NOT_EQUAL x)
					{
						FatalErrorIn(FunctionSIG)
							<< "invalid data structure has been detected." << endl
							<< " - element: " << x->Index() << endl
							<< " - left element: " << leftElement->Index() << endl
							<< " - right element: " << rightElement->Index() << endl
							<< abort(FatalError);
					}
				}
			}
		}
#endif // _DEBUG
#ifdef GeoMesh3d_Data_Construct_Debug
		std::cout << "the facets are checked." << std::endl;
#endif // GeoMesh3d_Data_Construct_Debug


		theElements_ = std::move(elements);
	}
}

#ifdef TriLoc_Debug
template<>
std::shared_ptr<tnbLib::Mesh3d_Element>
tnbLib::GeoMesh3d_Data::TriangleLocation
(
	const std::shared_ptr<Mesh3d_Element>& theStart,
	const Pnt3d& theCoord
) const
{
	if (NOT theStart)
	{
		FatalErrorIn("element_ptr TriangleLocation(const element_ptr& theStart, const Pnt2d& theCoord) const")
			<< "Null element has been encountered!" << endl
			<< abort(FatalError);
	}

	auto neighbor = theStart;
	auto element = theStart;

	int k = 0;
	while (Standard_True)
	{
		for (auto i = 0; i <= 3; i++)
		{
			const auto& entity = *element->Facet(i);

			auto rightElement = entity.RightElement().lock();
			Debug_Null_Pointer(rightElement);

			if (rightElement == element)
			{
				if (entity.IsLeftSide(theCoord))
				{
					auto leftElement = entity.LeftElement().lock();
					neighbor = leftElement;
					if (!neighbor)
					{
						//- the point is outside the background mesh
						return nullptr;
					}
					break;
				}
			}
			else
			{
				auto leftElement = entity.LeftElement().lock();
				if (NOT leftElement)
				{
					FatalErrorIn(FunctionSIG)
						<< "the facet doesn't belong to the element." << endl
						<< abort(FatalError);
				}

				if (leftElement NOT_EQUAL element)
				{
					FatalErrorIn(FunctionSIG)
						<< "the facet doesn't belong to the element." << endl
						<< " - element's id: " << element->Index() << endl
						<< " - right element: " << rightElement->Index() << endl
						<< " - left element: " << leftElement->Index() << endl
						<< abort(FatalError);
				}

				if (entity.IsRightSide(theCoord))
				{
					neighbor = rightElement;
					break;
				}
			}

		}
		
		if (neighbor == element)
		{
			// Found the Triangle
			return neighbor;
		}

		++k;
		if (k >= /*DEFAULT_MAX_CYCLES*/15000)
		{

			std::cout << "coord = " << theCoord << std::endl;
			
			FatalErrorIn("element_ptr TriangleLocation(const element_ptr& theStart, const Pnt2d& theCoord) const;")
				<< "It's look like the algorithm tramped in an infinite loop" << endl
				<< " - Unable to find the triangle which encompassed the point" << endl
				<< abort(FatalError);
		}

		element = neighbor;
	}
	return nullptr;
}
#endif // TriLoc_Debug
