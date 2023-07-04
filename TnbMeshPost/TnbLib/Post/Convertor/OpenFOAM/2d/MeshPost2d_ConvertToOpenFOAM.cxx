#include <MeshPost2d_ConvertToOpenFOAM.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node>>
tnbLib::MeshPost2d_ConvertToOpenFOAM::TriFacet::GetNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::copy(theNodes_.begin(), theNodes_.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node>>
tnbLib::MeshPost2d_ConvertToOpenFOAM::QuadFacet::GetNodes() const
{
	std::vector<std::shared_ptr<Node>> nodes;
	std::copy(theNodes_.begin(), theNodes_.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::Vertex::Insert
(
	const std::shared_ptr<Segment>& theSeg
)
{
	auto insert = theSegments_.insert(theSeg);
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected." << endl
			<< " - id: " << theSeg->Index() << endl
			<< abort(FatalError);
	}
}

Standard_Boolean 
tnbLib::MeshPost2d_ConvertToOpenFOAM::Compare
(
	const std::weak_ptr<Segment>& theV0,
	const std::weak_ptr<Segment>& theV1
)
{
	Debug_Null_Pointer(theV0.lock());
	Debug_Null_Pointer(theV1.lock());
	return theV0.lock()->Index() < theV1.lock()->Index();
}

Standard_Boolean 
tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment::ChackSense
(
	const std::shared_ptr<Vertex>& theV0,
	const std::shared_ptr<Vertex>& theV1
) const 
{
	if (theVertices_.at(0) IS_EQUAL theV0)
	{
		if (theVertices_.at(1) IS_EQUAL theV1)
		{
			return Standard_True;
		}
	}
	else
	{
		if (theVertices_.at(1) IS_EQUAL theV0)
		{
			if (theVertices_.at(0) IS_EQUAL theV1)
			{
				return Standard_False;
			}
		}
		
	}
	FatalErrorIn(FunctionSIG)
		<< "contradictory data has been detected." << endl
		<< abort(FatalError);
	return Standard_True;
}

std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Vertex> 
tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment::Opposite
(
	const std::shared_ptr<Vertex>& theVtx
) const
{
	if (theVtx IS_EQUAL theVertices_.at(0)) return theVertices_.at(1);
	if (theVtx IS_EQUAL theVertices_.at(1)) return theVertices_.at(0);
	FatalErrorIn(FunctionSIG)
		<< "the vertex doesn't belong to the segment." << endl
		<< abort(FatalError);
	return nullptr;
}

Standard_Boolean 
tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment::IsValidToCreate
(
	const std::shared_ptr<Vertex>& theV0,
	const std::shared_ptr<Vertex>& theV1
)
{
	if (theV1->NbSegments() < theV0->NbSegments())
	{
		return IsValidToCreate(theV1, theV0);
	}
	const auto& segments = theV0->Segments();
	for (const auto& x : segments)
	{
		auto seg = x.lock();
		Debug_Null_Pointer(seg);
		auto v1 = seg->Opposite(theV0);
		if (v1 IS_EQUAL theV1)
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

Standard_Boolean 
tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment::Compare
(
	const std::shared_ptr<Segment>& theS0,
	const std::shared_ptr<Segment>& theS1
)
{
	Debug_Null_Pointer(theS0);
	Debug_Null_Pointer(theS1);
	return theS0->Index() < theS1->Index();
}

//Standard_Integer 
//tnbLib::MeshPost2d_ConvertToOpenFOAM::ExtrudedNodeIndex
//(
//	const Standard_Integer theIndex,
//	const Standard_Integer theNbPoints
//)
//{
//	return theIndex + theNbPoints;
//}

std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node>>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcNodes
(
	const std::vector<Pnt2d>& thePnts, 
	const Standard_Real theExtrusion
)
{
	std::vector<std::shared_ptr<MeshPost2d_ConvertToOpenFOAM::Node>> nodes;
	nodes.reserve(thePnts.size() * 2);
	Standard_Integer k = 0;
	for (const auto& x : thePnts)
	{
		Pnt3d pt(x.X(), x.Y(), 0);
		auto node = 
			std::make_shared<MeshPost2d_ConvertToOpenFOAM::MasterNode>
			(++k, std::move(pt));
		nodes.push_back(std::move(node));
	}
	std::vector<std::shared_ptr<MeshPost2d_ConvertToOpenFOAM::Node>> slaves;
	for (const auto& x : thePnts)
	{
		Pnt3d pt(x.X(), x.Y(), theExtrusion);
		auto node = 
			std::make_shared<MeshPost2d_ConvertToOpenFOAM::SlaveNode>
			(++k, std::move(pt));
		slaves.push_back(std::move(node));
	}
	for (size_t i = 0; i < nodes.size(); i++)
	{
		std::dynamic_pointer_cast<MeshPost2d_ConvertToOpenFOAM::MasterNode>
			(nodes.at(i))->SlaveRef() = 
			std::dynamic_pointer_cast<SlaveNode>(slaves.at(i));
	}
	for (auto& x : slaves)
	{
		nodes.push_back(std::move(x));
	}
	return std::move(nodes);
}

std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment>
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveSegment
(
	const std::shared_ptr<Vertex>& theV0,
	const std::shared_ptr<Vertex>& theV1
)
{
	if (theV1->NbSegments() < theV0->NbSegments())
	{
		return RetrieveSegment(theV1, theV0);
	}
	const auto& segments = theV0->Segments();
	for (const auto& x : segments)
	{
		auto seg = x.lock();
		Debug_Null_Pointer(seg);
		auto v1 = seg->Opposite(theV0);
		if (v1 IS_EQUAL theV1)
		{
			return std::move(seg);
		}
	}
	FatalErrorIn(FunctionSIG) << endl
		<< "no segment has been found between the two vertices." << endl
		<< abort(FatalError);
	std::shared_ptr<Segment> seg;
	return std::move(seg);
}

std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcNodes2d(const std::vector<std::shared_ptr<Node>>& theNodes)
{
	std::vector<std::shared_ptr<Node2d>> nodes;
	nodes.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		auto master = std::dynamic_pointer_cast<MasterNode>(x);
		if (master)
		{
			auto node = std::make_shared<Node2d >(x->Index(), std::move(master));
			nodes.push_back(std::move(node));
		}
	}
	return std::move(nodes);
}

std::vector<std::pair<Standard_Integer, Standard_Integer>>
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveBoundaries
(
	const std::map<word, std::pair<Standard_Integer, Standard_Integer>>& theBoundaries
)
{
	std::vector<std::pair<Standard_Integer, Standard_Integer>> segments;
	for (const auto& x : theBoundaries)
	{
		const auto paired = x.second;
		for (Standard_Integer i = paired.first + 1; i <= paired.second; i++)
		{
			auto i0 = i - 1;
			auto i1 = i;
			auto seg = std::make_pair(i0, i1);
			segments.push_back(std::move(seg));
		}
	}
	return std::move(segments);
}

std::tuple
<
	std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>, 
	std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>,
	std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>
>
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveNodes(const Element2d& theElement)
{
	const auto& edges = theElement.Edges();
	std::vector<std::shared_ptr<Node2d>> nodes;
	for (const auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Sense() ? nodes.push_back(x->Nodes().at(0)) : nodes.push_back(x->Nodes().at(1));
	}
	auto t = std::make_tuple(nodes.at(0), nodes.at(1), nodes.at(2));
	return std::move(t);
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::CreateFace(const std::shared_ptr<Edge2d>& theEdge)
{
	Debug_Null_Pointer(theEdge->Nodes().at(0));
	Debug_Null_Pointer(theEdge->Nodes().at(1));
	Debug_Null_Pointer(theEdge->Nodes().at(0)->Node3d());
	Debug_Null_Pointer(theEdge->Nodes().at(1)->Node3d());
	auto n0 = std::dynamic_pointer_cast<MasterNode>(theEdge->Nodes().at(0)->Node3d());
	auto n1 = std::dynamic_pointer_cast<MasterNode>(theEdge->Nodes().at(1)->Node3d());

	auto n2 = n1->Slave();
	auto n3 = n0->Slave();

	std::array<std::shared_ptr<Node>, QuadFacet::nbNodes> nodes = 
	{ std::move(n0),std::move(n1),std::move(n2),std::move(n3) };
	auto f = std::make_shared<QuadFacet>(theEdge->Index(), std::move(nodes));
	theEdge->ExtrudedRef() = std::move(f);
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::CreateFace
(
	const std::shared_ptr<Element2d>& theElement,
	const Standard_Integer theIndex
)
{
	auto [n0, n1, n2] = RetrieveNodes(*theElement);
	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);
	Debug_Null_Pointer(n2);
	auto n0_f0 = n0->Node3d();
	auto n1_f0 = n1->Node3d();
	auto n2_f0 = n2->Node3d();
	Debug_Null_Pointer(n0_f0);
	Debug_Null_Pointer(n1_f0);
	Debug_Null_Pointer(n2_f0);

	auto n0_f1 = n0_f0->Slave();
	auto n1_f1 = n1_f0->Slave();
	auto n2_f1 = n2_f0->Slave();
	Debug_Null_Pointer(n0_f1);
	Debug_Null_Pointer(n1_f1);
	Debug_Null_Pointer(n2_f1);
	{
		std::array<std::shared_ptr<Node>, TriFacet::nbNodes> nodes = 
		{ std::move(n0_f0), std::move(n1_f0), std::move(n2_f0) };
		auto f = std::make_shared<TriFacet>(theIndex + 1, std::move(nodes));
		theElement->FrontRef() = std::move(f);
	}
	{
		std::array<std::shared_ptr<Node>, TriFacet::nbNodes> nodes =
		{ std::move(n0_f1), std::move(n2_f1), std::move(n1_f1) };
		auto f = std::make_shared<TriFacet>(theIndex + 2, std::move(nodes));
		theElement->BackRef() = std::move(f);
	}
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcFaces
(
	const std::vector<std::shared_ptr<Edge2d>>& theEdges
)
{
	for (const auto& x : theEdges)
	{
		Debug_Null_Pointer(x);
		CreateFace(x);
	}
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcFaces
(
	const std::vector<std::shared_ptr<Element2d>>& theElements,
	const Standard_Integer theNbEdges
)
{
	auto nf = theNbEdges;
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		CreateFace(x, nf);

		nf = nf + 2;
	}
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcElements
(
	const std::vector<std::shared_ptr<Element2d>>& theElements
)
{
	for (const auto& x : theElements)
	{
		Debug_Null_Pointer(x);
		const auto& edges = x->Edges();
		auto f0 = edges.at(0)->Extruded();
		Debug_Null_Pointer(f0);
		auto f1 = edges.at(1)->Extruded();
		Debug_Null_Pointer(f1);
		auto f2 = edges.at(2)->Extruded();
		Debug_Null_Pointer(f2);

		auto f3 = x->Front();
		auto f4 = x->Back();
		Debug_Null_Pointer(f3);
		Debug_Null_Pointer(f4);

		std::array<std::shared_ptr<Facet>, Element::nbFacets>
			faces = { std::move(f0),std::move(f1),std::move(f2),std::move(f3),std::move(f4) };
		auto elm = std::make_shared<Element>(x->Index(), std::move(faces));
		x->Element3dRef() = std::move(elm);
	}
}

// retrieving the OpenFOAM files [7/1/2023 Payvand]

tnbLib::MeshPost2d_ConvertToOpenFOAM::PointList
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrievePointList
(
	const std::vector<std::shared_ptr<Node>>& theNodes
)
{
	std::vector<Pnt3d> coords;
	coords.reserve(theNodes.size());
	for (const auto& x : theNodes)
	{
		coords.push_back(x->Coord());
	}
	PointList pointList(std::move(coords));
	return std::move(pointList);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::CellList
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveCellList
(
	const std::vector<std::shared_ptr<Element2d>>& theElements
)
{
	std::vector<Cell> cells;
	cells.reserve(theElements.size());
	for (const auto& x : theElements)
	{
		auto c = RetrieveCell(*x);
		cells.push_back(std::move(c));
	}
	CellList cellList(std::move(cells));
	return std::move(cellList);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::FaceList
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveFaceList
(
	const std::vector<std::shared_ptr<Edge2d>>& theEdges
)
{
	std::vector<Face> faces;
	faces.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		auto f = RetrieveFace(*x);
		faces.push_back(std::move(f));
	}
	FaceList faceList(std::move(faces));
	return std::move(faceList);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::OwnerList
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveOwnerList
(
	const std::vector<std::shared_ptr<Edge2d>>& theEdges
)
{
	std::vector<Standard_Integer> owners;
	owners.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		auto owner = x->Owner().lock();
		Debug_Null_Pointer(owner);
		owners.push_back(owner->Index());
	}
	OwnerList ownerList(std::move(owners));
	return std::move(ownerList);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::NeighborList
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveNeighborList
(
	const std::vector<std::shared_ptr<Edge2d>>& theEdges
)
{
	std::vector<Standard_Integer> neighbors;
	neighbors.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		auto neighbor = x->Neighbor().lock();
		if (neighbor)
		{
			neighbors.push_back(neighbor->Index());
		}
	}
	return std::move(neighbors);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::Cell
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveCell(const Element2d& theElement)
{
	std::array<Standard_Integer, Cell::nbFaces> faces;
	const auto& edges = theElement.Edges();
	faces.at(0) = edges.at(0)->Index();
	faces.at(1) = edges.at(1)->Index();
	faces.at(2) = edges.at(2)->Index();
	faces.at(3) = theElement.Back()->Index();
	faces.at(4) = theElement.Front()->Index();
	Cell cell(std::move(faces));
	return std::move(cell);
}

tnbLib::MeshPost2d_ConvertToOpenFOAM::Face
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveFace(const Edge2d& theEdge)
{
	std::vector<Standard_Integer> nodes;
	Debug_Null_Pointer(theEdge.Nodes().at(0));
	Debug_Null_Pointer(theEdge.Nodes().at(1));
	Debug_Null_Pointer(theEdge.Nodes().at(0)->Node3d());
	Debug_Null_Pointer(theEdge.Nodes().at(1)->Node3d());
	auto n0 = std::dynamic_pointer_cast<MasterNode>(theEdge.Nodes().at(0)->Node3d());
	auto n1 = std::dynamic_pointer_cast<MasterNode>(theEdge.Nodes().at(1)->Node3d());

	auto n2 = n1->Slave();
	auto n3 = n0->Slave();

	nodes.push_back(n0->Index());
	nodes.push_back(n1->Index());
	nodes.push_back(n2->Index());
	nodes.push_back(n3->Index());
	Face face(std::move(nodes));
	return std::move(face);
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::Perform()
{
	if (NOT Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been found." << endl
			<< abort(FatalError);
	}
	auto nodes = CalcNodes(Mesh()->Points(), Extrusion());
	auto boundaries = RetrieveBoundaries(Boundaries());
	auto [elements_2d, edges_2d, nodes_2d] = 
		CalcMesh2d(*Mesh(), boundaries, nodes, Extrusion());

	/*auto [intEdges, bndEdges] = SeperateEdges(edges_2d);
	const auto nbInteriors = (Standard_Integer)intEdges.size();

	RenumberInteriors(intEdges);
	RenumberBoundaries(bndEdges, nbInteriors);*/

	CalcFaces(edges_2d);
	CalcFaces(elements_2d, (Standard_Integer)edges_2d.size());

	CalcElements(elements_2d);

	thePoints_ = RetrievePointList(nodes);

	theFaces_ = RetrieveFaceList(edges_2d);
	theCells_ = RetrieveCellList(elements_2d);

	theOwners_ = RetrieveOwnerList(edges_2d);
	theNeighbors_ = RetrieveNeighborList(edges_2d);

	Change_IsDone() = Standard_True;
}

