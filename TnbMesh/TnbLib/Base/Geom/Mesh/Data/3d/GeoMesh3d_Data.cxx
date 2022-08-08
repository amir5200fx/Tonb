#include <GeoMesh3d_Data.hxx>

#include <Mesh3d_Element.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Node.hxx>
#include <Geo_Tools.hxx>
#include <Entity3d_TetrahedralizationTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh3d_Data::Construct(const triangulation& theTriangulation)
	{
		const auto& Points = theTriangulation.Points();
		const auto& Triangles = theTriangulation.Connectivity();
		//std::cout << "nb of tris: " << Triangles.size() << std::endl;
		//std::cout << "nb of points: " << Points.size() << std::endl;
		std::vector<std::shared_ptr<Mesh3d_Node>> Nodes;
		Nodes.reserve(Points.size());

		// Creating the nodes
		Standard_Integer k = 0;
		for (const auto& x : Points)
		{
			auto node = std::make_shared<Mesh3d_Node>(++k, x);
			Nodes.push_back(std::move(node));
		}

		std::vector<std::shared_ptr<Mesh3d_Element>> elements;
		elements.reserve(Triangles.size());
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
				}
				element->SetFacet(I, current_facet);
			}
		}

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


		theElements_ = std::move(elements);
	}
}