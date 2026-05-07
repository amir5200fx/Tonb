#pragma once
#include <Geo_Tools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMeshNodes
(
	const std::shared_ptr<elementType>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	if (element.Node0()->InsertToElements(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node1()->InsertToElements(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node2()->InsertToElements(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node3()->InsertToElements(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMeshNodes
(
	const std::shared_ptr<frontType>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	if (element.Node0()->InsertToFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node1()->InsertToFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node2()->InsertToFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMeshNodes
(
	const std::shared_ptr<edgeType>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	if (edge.Node0()->InsertToEdges(theEdge->Index(), theEdge))
	{
		FatalErrorIn("void AttachToMeshNodes(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to register the edge to the mesh" << endl
			<< abort(FatalError);
	}
	if (edge.Node1()->InsertToEdges(theEdge->Index(), theEdge))
	{
		FatalErrorIn("void AttachToMeshNodes(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to register the edge to the mesh" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMeshEdges
(
	const std::shared_ptr<frontType>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	if (facet.Edge0()->InsertToFacets(facet.Index(), theFacet))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the facet to the mesh" << endl
			<< abort(FatalError);
	}
	if (facet.Edge1()->InsertToFacets(facet.Index(), theFacet))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the facet to the mesh" << endl
			<< abort(FatalError);
	}
	if (facet.Edge2()->InsertToFacets(facet.Index(), theFacet))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the facet to the mesh" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMeshEdges
(
	const std::shared_ptr<elementType>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	if (element.Edge0()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
	if (element.Edge1()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
	if (element.Edge2()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
	if (element.Edge3()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
	if (element.Edge4()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
	if (element.Edge5()->InsertToElements(element.Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMesh
(
	const std::shared_ptr<frontType>& theFacet
)
{
	AttachToMeshEdges(theFacet);
	AttachToMeshNodes(theFacet);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToMesh
(
	const std::shared_ptr<elementType>& theElement
)
{
	AttachToMeshEdges(theElement);
	AttachToMeshNodes(theElement);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToFrontNodes
(
	const std::shared_ptr<frontType>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	if (element.Node0()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node1()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Node2()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToFrontNodes
(
	const std::shared_ptr<edgeType>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	if (edge.Node0()->InsertToFrontEdges(theEdge->Index(), theEdge))
	{
		FatalErrorIn("void AttachToFrontNodes(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to register the edge to the front" << endl
			<< abort(FatalError);
	}
	if (edge.Node1()->InsertToFrontEdges(theEdge->Index(), theEdge))
	{
		FatalErrorIn("void AttachToFrontNodes(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to register the edge to the front" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToFrontEdges
(
	const std::shared_ptr<frontType>& theElement
)
{
	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	Debug_Null_Pointer(theElement);
	auto& element = *theElement;

	if (element.Edge0()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Edge1()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
	if (element.Edge2()->InsertToFrontFacets(theElement->Index(), theElement))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to register the element to the mesh." << endl
			<< " - duplicate element: index = " << theElement->Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::AttachToFronts
(
	const std::shared_ptr<frontType>& theFront
)
{
	AttachToFrontEdges(theFront);
	AttachToFrontNodes(theFront);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromMesh
(
	const std::shared_ptr<frontType>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	if (NOT facet.IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< " Trying to delete a non-orphan facet!"
			<< abort(FatalError);
	}

	deAttachFromMeshEdges(theFacet);
	deAttachFromMeshNodes(theFacet);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromMesh
(
	const std::shared_ptr<edgeType>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	if (!edge.IsOrphan())
	{
		FatalErrorIn(FunctionSIG)
			<< " Trying to delete a non-orphan edge!"
			<< abort(FatalError);
	}

	if (edge.Node0()->RemoveFromEdges(theEdge->Index()))
	{
		FatalErrorIn("void deAttachFromMesh(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to remove the edge from the mesh" << endl
			<< abort(FatalError);
	}
	if (edge.Node1()->RemoveFromEdges(theEdge->Index()))
	{
		FatalErrorIn("void deAttachFromMesh(const std::shared_ptr<frontType>& theEdge)")
			<< "Failed to remove the edge from the mesh" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromMeshNodes
(
	const std::shared_ptr<frontType>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	if (facet.Node0()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
	if (facet.Node1()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
	if (facet.Node2()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromMeshEdges
(
	const std::shared_ptr<frontType>& theFacet
)
{
	Debug_Null_Pointer(theFacet);
	auto& facet = *theFacet;

	if (facet.Edge0()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
	if (facet.Edge1()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
	if (facet.Edge2()->RemoveFromFacets(facet.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << facet.Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromFronts
(
	const std::shared_ptr<frontType>& theFront
)
{
	deAttachFromFrontEdges(theFront);
	deAttachFromFrontNodes(theFront);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromFronts
(
	const std::shared_ptr<edgeType>& theEdge
)
{
	Debug_Null_Pointer(theEdge);
	auto& edge = *theEdge;

	if (edge.Node0()->RemoveFromFrontEdges(theEdge->Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the edge from the front" << endl
			<< abort(FatalError);
	}
	if (edge.Node1()->RemoveFromFrontEdges(theEdge->Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the edge from the front" << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromFrontNodes
(
	const std::shared_ptr<frontType>& theFront
)
{
	Debug_Null_Pointer(theFront);
	auto& front = *theFront;

	if (front.Node0()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
	if (front.Node1()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
	if (front.Node2()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::deAttachFromFrontEdges
(
	const std::shared_ptr<frontType>& theFront
)
{
	Debug_Null_Pointer(theFront);
	auto& front = *theFront;

	if (front.Edge0()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
	if (front.Edge1()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
	if (front.Edge2()->RemoveFromFrontFacets(front.Index()))
	{
		FatalErrorIn(FunctionSIG)
			<< "Failed to remove the facet from the map." << endl
			<< " - index: " << front.Index() << endl
			<< abort(FatalError);
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::SetPairedEdges()
{
	frontInfo::SetPairedEdge3(nullptr);
	frontInfo::SetPairedEdge4(nullptr);
	frontInfo::SetPairedEdge5(nullptr);

	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	Debug_Null_Pointer(current.Node0());
	Debug_Null_Pointer(current.Node1());
	Debug_Null_Pointer(current.Node2());

	const auto v0 = current.Node0()->Index();
	const auto v1 = current.Node1()->Index();
	const auto v2 = current.Node2()->Index();

	Debug_Null_Pointer(frontInfo::ValidNode());
	const auto& valid = *frontInfo::ValidNode();

	const auto vn = valid.Index();
	for (const auto& x : valid.RetrieveFrontEdges())
	{
		Debug_Null_Pointer(x.second.lock());
		const auto edge_ptr = x.second.lock();
		const auto edge = *edge_ptr;

		const auto e0 = edge.Node0()->Index();
		const auto e1 = edge.Node1()->Index();

		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v0, vn))
		{
			frontInfo::SetPairedEdge3(edge_ptr);
		}
		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v1, vn))
		{
			frontInfo::SetPairedEdge4(edge_ptr);
		}
		if (Geo_Tools::IsPairedTwoSegments(e0, e1, v2, vn))
		{
			frontInfo::SetPairedEdge5(edge_ptr);
		}
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::SetPairedFacets()
{
	frontInfo::SetPairedFacet0(nullptr);
	frontInfo::SetPairedFacet1(nullptr);
	frontInfo::SetPairedFacet2(nullptr);

	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	const auto v0 = current.Node0()->Index();
	const auto v1 = current.Node1()->Index();
	const auto v2 = current.Node2()->Index();

	Debug_Null_Pointer(current.Edge0());
	Debug_Null_Pointer(current.Edge1());
	Debug_Null_Pointer(current.Edge2());

	const auto& facets0 = current.Edge0()->RetrieveFrontFacets();
	const auto& facets1 = current.Edge1()->RetrieveFrontFacets();
	const auto& facets2 = current.Edge2()->RetrieveFrontFacets();

	const auto& valid = *frontInfo::ValidNode();
	const auto vn = valid.Index();

	for (const auto& x : facets0)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v1, v2, vn, q0, q1, q2))
		{
			frontInfo::SetPairedFacet0(facetPtr);
			break;
		}
	}
	for (const auto& x : facets1)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v2, v0, vn, q0, q1, q2))
		{
			frontInfo::SetPairedFacet1(facetPtr);
			break;
		}
	}
	for (const auto& x : facets2)
	{
		Debug_Null_Pointer(x.second.lock());
		auto facetPtr = x.second.lock();
		const auto& facet = *facetPtr;

		auto q0 = facet.Node0()->Index();
		auto q1 = facet.Node1()->Index();
		auto q2 = facet.Node2()->Index();

		if (Geo_Tools::IsPairedTwoTriangles(v0, v1, vn, q0, q1, q2))
		{
			frontInfo::SetPairedFacet2(facetPtr);
			break;
		}
	}
}

template<class FrontTraits, class FrontAdaptor>
template<class SizeMap>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::UpdateEdges
(
	const std::shared_ptr<SizeMap>& theSizeMap
)
{
	Debug_Null_Pointer(theSizeMap);
	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	if (frontInfo::PairedEdge3())
	{
		frontInfo::SetCreatedEdge3(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(frontInfo::PairedEdge3());
	}
	else
	{
		EdgeCounter()++;

		auto edge = std::make_shared<Aft3d_Edge>(EdgeCounter());
		Debug_Null_Pointer(edge);

		edge->SetNode0(current.Node0());
		edge->SetNode1(frontInfo::ValidNode());

		frontInfo::SetCreatedEdge3(edge);

		CalcGeometries(theSizeMap, edge);

		Debug_If_Condition(frontInfo::ValidNode() == current.Node0());

		AttachToFrontNodes(frontInfo::CreatedEdge3());
		AttachToMeshNodes(frontInfo::CreatedEdge3());
	}

	if (frontInfo::PairedEdge4())
	{
		frontInfo::SetCreatedEdge4(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(frontInfo::PairedEdge4());
	}
	else
	{
		EdgeCounter()++;

		auto edge = std::make_shared<Aft3d_Edge>(EdgeCounter());
		Debug_Null_Pointer(edge);

		edge->SetNode0(current.Node1());
		edge->SetNode1(frontInfo::ValidNode());

		frontInfo::SetCreatedEdge4(edge);

		CalcGeometries(theSizeMap, edge);

		Debug_If_Condition(frontInfo::ValidNode() == current.Node1());

		AttachToFrontNodes(frontInfo::CreatedEdge4());
		AttachToMeshNodes(frontInfo::CreatedEdge4());
	}

	if (frontInfo::PairedEdge5())
	{
		frontInfo::SetCreatedEdge5(nullptr);

		// remove the old coincident face from the GF
		deAttachFromFronts(frontInfo::PairedEdge5());
	}
	else
	{
		EdgeCounter()++;

		auto edge = std::make_shared<Aft3d_Edge>(EdgeCounter());
		Debug_Null_Pointer(edge);

		edge->SetNode0(current.Node2());
		edge->SetNode1(frontInfo::ValidNode());

		frontInfo::SetCreatedEdge5(edge);
		
		CalcGeometries(theSizeMap, edge);

		Debug_If_Condition(frontInfo::ValidNode() == current.Node2());

		AttachToFrontNodes(frontInfo::CreatedEdge5());
		AttachToMeshNodes(frontInfo::CreatedEdge5());
	}
}

template<class FrontTraits, class FrontAdaptor>
template<class SizeMap>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::UpdateFacets
(
	const std::shared_ptr<SizeMap>& theSizeMap
)
{
	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	const auto e0 = current.Edge0();
	const auto e1 = current.Edge1();
	const auto e2 = current.Edge2();

	std::shared_ptr<edgeType> e3, e4, e5;

	if (frontInfo::CreatedEdge3()) e3 = frontInfo::CreatedEdge3();
	else e3 = frontInfo::PairedEdge3();

	if (frontInfo::CreatedEdge4()) e4 = frontInfo::CreatedEdge4();
	else e4 = frontInfo::PairedEdge4();

	if (frontInfo::CreatedEdge5()) e5 = frontInfo::CreatedEdge5();
	else e5 = frontInfo::PairedEdge5();

	Debug_Null_Pointer(e0);
	Debug_Null_Pointer(e1);
	Debug_Null_Pointer(e2);
	Debug_Null_Pointer(e3);
	Debug_Null_Pointer(e4);

	{
		auto facet = frontInfo::PairedFacet0();
		if (facet)
		{
			frontInfo::SetCreatedFacet0(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsOnCavity())
			{
				facet->RemoveEntityAsCavity();
			}
		}
		else
		{
			FacetCounter()++;

			auto newFacet = 
				std::make_shared<frontType>
				(
					FacetCounter(),
					current.Node1(),
					current.Node2(),
					frontInfo::ValidNode()
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e5);
			newFacet->SetEdge1(e4);
			newFacet->SetEdge2(e0);

			frontInfo::SetCreatedFacet0(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(theSizeMap, newFacet);
		}
	}

	{
		auto facet = frontInfo::PairedFacet1();
		if (facet)
		{
			frontInfo::SetCreatedFacet1(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsOnCavity())
			{
				facet->RemoveEntityAsCavity();
			}
		}
		else
		{
			FacetCounter()++;

			auto newFacet = 
				std::make_shared<frontType>
				(
					FacetCounter(),
					current.Node2(),
					current.Node0(),
					frontInfo::ValidNode()
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e3);
			newFacet->SetEdge1(e5);
			newFacet->SetEdge2(e1);

			frontInfo::SetCreatedFacet1(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(theSizeMap, newFacet);
		}
	}

	{
		auto facet = frontInfo::PairedFacet2();
		if (facet)
		{
			frontInfo::SetCreatedFacet2(nullptr);

			// remove the old coincident face from the GF
			deAttachFromFronts(facet);

			// remove cavity face
			if (facet->IsOnCavity())
			{
				facet->RemoveEntityAsCavity();
			}
		}
		else
		{
			FacetCounter()++;

			auto newFacet = 
				std::make_shared<frontType>
				(
					FacetCounter(),
					current.Node0(),
					current.Node1(),
					frontInfo::ValidNode()
					);
			Debug_Null_Pointer(newFacet);

			newFacet->SetEdge0(e4);
			newFacet->SetEdge1(e3);
			newFacet->SetEdge2(e2);

			frontInfo::SetCreatedFacet2(newFacet);

			AttachToFronts(newFacet);
			AttachToMesh(newFacet);

			CalcGeometries(theSizeMap, newFacet);
		}
	}
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::SetPairs()
{
	SetPairedEdges();
	SetPairedFacets();
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::CreateElement()
{
	ElementCounter()++;

	Debug_Null_Pointer(frontInfo::CurrentFront());
	const auto& current = *frontInfo::CurrentFront();

	auto element_p =
		std::make_shared<elementType>(ElementCounter());
	Debug_Null_Pointer(element_p);

	auto& element = *element_p;

	element.SetNode0(current.Node0());
	element.SetNode1(current.Node1());
	element.SetNode2(current.Node2());

	element.SetEdge0(current.Edge0());
	element.SetEdge1(current.Edge1());
	element.SetEdge2(current.Edge2());

	Debug_Null_Pointer(frontInfo::ValidNode());
	element.SetNode3(frontInfo::ValidNode());

	if (frontInfo::CreatedFacet0())
	{
		element.SetFacet0(frontInfo::CreatedFacet0());
	}
	else
	{
		element.SetFacet0(frontInfo::PairedFacet0());
	}

	if (frontInfo::CreatedFacet1())
	{
		element.SetFacet1(frontInfo::CreatedFacet1());
	}
	else
	{
		element.SetFacet1(frontInfo::PairedFacet1());
	}

	if (frontInfo::CreatedFacet2())
	{
		element.SetFacet2(frontInfo::CreatedFacet2());
	}
	else
	{
		element.SetFacet2(frontInfo::PairedFacet2());
	}

	if (frontInfo::CreatedEdge3())
	{
		element.SetEdge3(frontInfo::CreatedEdge3());
	}
	else
	{
		element.SetEdge3(frontInfo::PairedEdge3());
	}

	if (frontInfo::CreatedEdge4())
	{
		element.SetEdge4(frontInfo::CreatedEdge4());
	}
	else
	{
		element.SetEdge4(frontInfo::PairedEdge4());
	}

	if (frontInfo::CreatedEdge5())
	{
		element.SetEdge5(frontInfo::CreatedEdge5());
	}
	else
	{
		element.SetEdge5(frontInfo::PairedEdge5());
	}

	element.SetFacet3(frontInfo::CurrentFront());

	frontInfo::SetElement(element_p);
}

template<class FrontTraits, class FrontAdaptor>
inline void tnbLib::Aft3d_FrontInfoTemplate<FrontTraits, FrontAdaptor>::UpdateElement()
{
	const auto& element = frontInfo::Element();
	Debug_Null_Pointer(element);

	AttachToMesh(element);

	/*Attaching the element to the facets*/

	const auto& current = frontInfo::CurrentFront();
	Debug_Null_Pointer(current);

	// update right/ left side element pointer of the faces
	// update the adjacent elements
	current->SetLeftElement(element);
	element->SetNeighbor3(current->RightElement());

	auto rightElement = current->RightElement().lock();
	if (rightElement)
	{
		rightElement->Neighbor(rightElement->OppositeVertexIndex(current)) = element;
	}

	if (frontInfo::CreatedFacet0())
	{
		frontInfo::CreatedFacet0()->SetRightElement(element);
		element->SetNeighbor(0, nullptr);
	}
	else
	{
		auto facet = frontInfo::PairedFacet0();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->RightElement().lock();
		element->SetNeighbor(0, neighbor);

		if (facet->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetLeftElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}

	if (frontInfo::CreatedFacet1())
	{
		frontInfo::CreatedFacet1()->SetRightElement(element);
		element->SetNeighbor(1, nullptr);
	}
	else
	{
		auto facet = frontInfo::PairedFacet1();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->RightElement().lock();
		element->SetNeighbor(1, neighbor);

		if (facet->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetLeftElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}

	if (frontInfo::CreatedFacet2())
	{
		frontInfo::CreatedFacet2()->SetRightElement(element);
		element->SetNeighbor(2, nullptr);
	}
	else
	{
		auto facet = frontInfo::PairedFacet2();
		Debug_Null_Pointer(facet);

		auto neighbor = facet->RightElement().lock();
		element->SetNeighbor(2, neighbor);

		if (facet->LeftElement().lock())
		{
			FatalErrorIn(FunctionSIG)
				<< "contradiction data has been detected." << endl
				<< abort(FatalError);
		}

		facet->SetLeftElement(element);
		if (neighbor)
		{
			neighbor->SetNeighbor(neighbor->OppositeVertexIndex(facet), element);
		}
	}
}