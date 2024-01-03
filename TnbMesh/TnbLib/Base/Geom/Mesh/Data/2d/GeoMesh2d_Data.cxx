#include <GeoMesh2d_Data.hxx>

#include <Entity2d_Triangulation.hxx>
#include <MeshBase_Tools.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh2d_Data::Construct(const triangulation& theTriangulation)
	{
		theElements_ = MeshBase_Tools::MakeMesh(theTriangulation);
		MeshBase_Tools::ConnectEdgesAndElements(theElements_);
		//const auto& Points = theTriangulation.Points();
		//const auto& Triangles = theTriangulation.Connectivity();

		//std::vector<std::shared_ptr<nodeType>> Nodes;
		//Nodes.reserve(Points.size());

		//// Creating the nodes
		//Standard_Integer k = 0;
		//for (const auto& x : Points)
		//{
		//	Nodes.push_back(std::make_shared<nodeType>(++k, x));
		//}

		//theElements_.reserve(Triangles.size());
		//// Creating the Elements
		//k = 0;
		//for (const auto& x : Triangles)
		//{
		//	auto v0 = x.Value(0) - 1;
		//	auto v1 = x.Value(1) - 1;
		//	auto v2 = x.Value(2) - 1;

		//	if (x.IsDegenerated())
		//	{
		//		FatalErrorIn("void AutLib::GeoMesh2d_Data::Construct()")
		//			<< "Invalid Triangle" << endl
		//			<< abort(FatalError);
		//	}

		//	Debug_Null_Pointer(Nodes[v0]);
		//	Debug_Null_Pointer(Nodes[v1]);
		//	Debug_Null_Pointer(Nodes[v2]);

		//	auto element = std::make_shared<elementType>(++k, Nodes[v0], Nodes[v1], Nodes[v2]);
		//	theElements_.push_back(element);

		//	element->Node0()->InsertToElements(element->Index(), element);
		//	element->Node1()->InsertToElements(element->Index(), element);
		//	element->Node2()->InsertToElements(element->Index(), element);
		//}

		//Standard_Integer nbEdges = 0;
		//for (auto& element : theElements_)
		//{
		//	for (Standard_Integer i = 0; i < 3; i++)
		//	{
		//		auto id1 = (i + 1) % 3;
		//		auto id2 = (id1 + 1) % 3;

		//		const auto& node1 = element->Node(id1);
		//		const auto& node2 = element->Node(id2);

		//		std::shared_ptr<edgeType> current_edge;

		//		auto v1 = node1->Index();
		//		auto v2 = node2->Index();

		//		Standard_Boolean Created = Standard_False;

		//		if ((NOT node1->NbEdges()) OR(NOT node2->NbEdges()))
		//		{
		//			Created = Standard_True;
		//		}
		//		else
		//		{
		//			auto size1 = node1->NbEdges();
		//			auto size2 = node2->NbEdges();

		//			std::shared_ptr<nodeType> current;
		//			std::shared_ptr<nodeType> other;

		//			if (size1 <= size2)
		//			{
		//				current = node1;
		//				other = node2;
		//			}
		//			else
		//			{
		//				current = node2;
		//				other = node1;
		//			}

		//			Standard_Boolean exist = Standard_False;

		//			for (const auto& x : current->RetrieveEdges())
		//			{
		//				auto edge = x.second.lock();
		//				Debug_Null_Pointer(edge);

		//				if (edge->Node0() IS_EQUAL other OR edge->Node1() IS_EQUAL other)
		//				{
		//					exist = Standard_True;
		//					current_edge = edge;

		//					current_edge->SetRightElement(element);
		//					break;
		//				}
		//			}

		//			if (NOT exist)
		//			{
		//				Created = Standard_True;
		//			}
		//		}

		//		if (Created)
		//		{
		//			if (current_edge)
		//			{
		//				FatalErrorIn("void AutLib::GeoMesh2d_Data::Construct()")
		//					<< "Contradictory Data: It's supposed to not be an edge!"
		//					<< abort(FatalError);
		//			}

		//			current_edge = std::make_shared<edgeType>(++nbEdges, node1, node2);
		//			current_edge->SetLeftElement(element);

		//			node1->InsertToEdges(current_edge->Index(), current_edge);
		//			node2->InsertToEdges(current_edge->Index(), current_edge);
		//		}

		//		element->Edge(i) = current_edge;
		//	}
		//}

		//// Identifying the Neighbors
		//for (auto& x : theElements_)
		//{
		//	Debug_Null_Pointer(x);
		//	auto& element = *x;

		//	Debug_Null_Pointer(element.Edge0());
		//	const auto& edge0 = element.Edge0();

		//	element.SetNeighbor0(edge0->LeftElement());
		//	if (edge0->LeftElement().lock() IS_EQUAL x) element.SetNeighbor0(edge0->RightElement());

		//	Debug_Null_Pointer(element.Edge1());
		//	const auto& edge1 = element.Edge1();

		//	element.SetNeighbor1(edge1->LeftElement());
		//	if (edge1->LeftElement().lock() IS_EQUAL x) element.SetNeighbor1(edge1->RightElement());

		//	Debug_Null_Pointer(element.Edge2());
		//	const auto& edge2 = element.Edge2();

		//	element.SetNeighbor2(edge2->LeftElement());
		//	if (edge2->LeftElement().lock() IS_EQUAL x) element.SetNeighbor2(edge2->RightElement());
		//}
	}

	template<>
	std::shared_ptr<Mesh2d_Element> 
		GeoMesh2d_Data::TriangleLocation
		(
			const std::shared_ptr<Mesh2d_Element>& theStart,
			const Point& theCoord
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
#if TriLoc_Debug
		int k = 0;
#endif
		while (Standard_True)
		{
			for (auto i = 0; i <= elementType::rank; i++)
			{
				Debug_Null_Pointer(element->Edge(i));
				const auto& entity = *element->Edge(i);

				auto rightElement = entity.RightElement().lock();
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
#ifdef TriLoc_Debug
					auto leftElement = entity.LeftElement().lock();
					if (NOT leftElement)
					{
						FatalErrorIn(FunctionSIG)
							<< "the edge doesn't belong to the element." << endl
							<< abort(FatalError);
					}

					if (leftElement NOT_EQUAL element)
					{
						FatalErrorIn(FunctionSIG)
							<< "the edge doesn't belong to the element." << endl
							<< " - element's id: " << element->Index() << endl
							<< " - right element: " << rightElement->Index() << endl
							<< " - left element: " << leftElement->Index() << endl
							<< abort(FatalError);
					}
#endif // TriLoc_Debug

					if (entity.IsRightSide(theCoord))
					{
						neighbor = rightElement;
						break;
					}
				}

				//auto leftElement = entity.LeftElement().lock();
				//if (leftElement == element)
				//{
				//	if (entity.IsRightSide(theCoord))
				//	{
				//		neighbor = entity.RightElement().lock();
				//		if (!neighbor)
				//		{
				//			FatalErrorIn(FunctionSIG)
				//				<< "invalid data has been detected." << endl
				//				<< abort(FatalError);
				//			//- the point is outside the background mesh
				//			//return nullptr;
				//		}
				//		break;
				//	}
				//}
				//else
				//{
				//	if (entity.IsLeftSide(theCoord))
				//	{
				//		neighbor = leftElement;
				//		if (!neighbor)
				//		{
				//			//- the point is outside the background mesh
				//			return nullptr;
				//		}
				//		break;
				//	}
				//}


			}

			if (neighbor == element)
			{
				// Found the Triangle
				return neighbor;
			}

#if TriLoc_Debug
			++k;
			if (k >= DEFAULT_MAX_CYCLES)
			{
				FatalErrorIn("element_ptr TriangleLocation(const element_ptr& theStart, const Pnt2d& theCoord) const;")
					<< "It looks like the algorithm trapped in an infinite loop" << endl
					<< " - Unable to find the triangle which encompassed the point" << endl
					<< abort(FatalError);
			}
#endif	

			element = neighbor;
		}
		return nullptr;
	}
}