#include <MeshPost2d_ConvertToOpenFOAM.hxx>

#include <Entity2d_Triangulation.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>
#include <token.hxx>

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os, 
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::PointList& thePoints
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << "version";
	os.indent();
	os << "2.0;" << endl;
	os.indent();
	os << "format";
	os.indent();
	os << "ascii;" << endl;
	os.indent();
	os << "class";
	os.indent();
	os << "vectorField;" << endl;
	os.indent();
	os << "object";
	os.indent();
	os << "points;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);

	os << endl
		<< endl
		<< endl;
	os << thePoints.Coords().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : thePoints.Coords())
	{
		auto [xi, yi, zi] = x.Components();
		os 
			<< token::BEGIN_LIST 
			<< xi
			<< token::SPACE 
			<< yi 
			<< token::SPACE 
			<< zi 
			<< token::END_LIST 
			<< endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os, 
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::FaceList& theFaces
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << "version";
	os.indent();
	os << "2.0;" << endl;
	os.indent();
	os << "format";
	os.indent();
	os << "ascii;" << endl;
	os.indent();
	os << "class";
	os.indent();
	os << "faceList;" << endl;
	os.indent();
	os << "object";
	os.indent();
	os << "faes;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);

	os << endl
		<< endl
		<< endl;
	os << theFaces.Faces().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : theFaces.Faces())
	{
		const auto& nodes = x.Nodes();
		os << nodes.size() << token::BEGIN_LIST << nodes.at(0);
		for (size_t ii = 1; ii < nodes.size(); ii++)
		{
			os << token::SPACE << nodes.at(ii);
		}
		os << token::END_LIST << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::CellList& theCells
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << "version";
	os.indent();
	os << "2.0;" << endl;
	os.indent();
	os << "format";
	os.indent();
	os << "ascii;" << endl;
	os.indent();
	os << "class";
	os.indent();
	os << "cellList;" << endl;
	os.indent();
	os << "object";
	os.indent();
	os << "cells;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theCells.Cells().size() << endl
		<< token::BEGIN_LIST << endl;
	for (const auto& x : theCells.Cells())
	{
		const auto& faces = x.Faces();
		os << faces.size() << token::BEGIN_LIST << faces.at(0);
		for (size_t ii = 1; ii < faces.size(); ii++)
		{
			os << token::SPACE << faces.at(ii);
		}
		os << token::END_LIST << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::OwnerList& theOwners
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << "version";
	os.indent();
	os << "2.0;" << endl;
	os.indent();
	os << "format";
	os.indent();
	os << "ascii;" << endl;
	os.indent();
	os << "class";
	os.indent();
	os << "labelList;" << endl;
	os.indent();
	os << "object";
	os.indent();
	os << "owner;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theOwners.Owners().size() << endl
		<< token::BEGIN_LIST << endl;
	for (auto i : theOwners.Owners())
	{
		os << i << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

tnbLib::Ostream&
tnbLib::operator<<
(
	tnbLib::Ostream& os, 
	const tnbLib::MeshPost2d_ConvertToOpenFOAM::NeighborList& theNeighbors
	)
{
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(os);
	os << "FoamFile" << endl
		<< token::BEGIN_BLOCK << endl;
	os.indent();
	os << "version";
	os.indent();
	os << "2.0;" << endl;
	os.indent();
	os << "format";
	os.indent();
	os << "ascii;" << endl;
	os.indent();
	os << "class";
	os.indent();
	os << "labelList;" << endl;
	os.indent();
	os << "object";
	os.indent();
	os << "neighbour;" << endl;
	os << token::END_BLOCK << endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	os << endl
		<< endl
		<< endl;

	os << theNeighbors.Neighbors().size() << endl
		<< token::BEGIN_LIST << endl;
	for (auto i : theNeighbors.Neighbors())
	{
		os << i << endl;
	}
	os << token::END_LIST << endl;
	os << endl
		<< endl
		<< endl;
	MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(os);
	return os;
}

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

void tnbLib::MeshPost2d_ConvertToOpenFOAM::Vertex::Insert(const std::shared_ptr<Segment>& theSeg)
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
		auto node = std::make_shared<MeshPost2d_ConvertToOpenFOAM::MasterNode>(++k, std::move(pt));
		nodes.push_back(std::move(node));
	}
	std::vector<std::shared_ptr<MeshPost2d_ConvertToOpenFOAM::Node>> slaves;
	for (const auto& x : thePnts)
	{
		Pnt3d pt(x.X(), x.Y(), theExtrusion);
		auto node = std::make_shared<MeshPost2d_ConvertToOpenFOAM::SlaveNode>(++k, std::move(pt));
		slaves.push_back(std::move(node));
	}
	for (size_t i = 0; i < nodes.size(); i++)
	{
		std::dynamic_pointer_cast<MeshPost2d_ConvertToOpenFOAM::MasterNode>
			(nodes.at(i))->SlaveRef() = std::dynamic_pointer_cast<SlaveNode>(slaves.at(i));
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

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Element2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Edge2d>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Node2d>>
>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcMesh2d
(
	const Entity2d_Triangulation& theTris,
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theBoundaries,
	const std::vector<std::shared_ptr<Node>>& theNodes,
	const Standard_Real theExtrusion
)
{
	auto[vertices, segments] = CalcGragh(theTris, theBoundaries);
	auto nodes2d = CalcNodes2d(theNodes);

	// calculate 2d edges [6/28/2023 Payvand]
	std::vector<std::shared_ptr<Edge2d>> edges;
	edges.resize(segments.size());
	for (const auto& x : segments)
	{
		const auto& v0 = x->Vertices().at(0);
		const auto& v1 = x->Vertices().at(1);

		auto id = x->Index();
		std::array<std::shared_ptr<Node2d>, Edge2d::nbNodes> paired =
		{ nodes2d.at(Index_Of(v0->Index())), nodes2d.at(Index_Of(v1->Index())) };

		auto edge = std::make_shared<Edge2d>(id, std::move(paired));
		edges.at(Index_Of(id)) = std::move(edge);
	}
	std::vector<std::shared_ptr<Element2d>> tris;
	tris.reserve(theTris.NbConnectivity());
	Standard_Integer k = 0;
	for (const auto& x : theTris.Connectivity())
	{
		auto v0 = Index_Of(x.Value(0));
		auto v1 = Index_Of(x.Value(1));
		auto v2 = Index_Of(x.Value(2));

		std::shared_ptr<Edge2d> edge0, edge1, edge2;
		{
			auto seg = RetrieveSegment(vertices.at(v0), vertices.at(v1));
			auto id = seg->Index();
			edge0 = edges.at(Index_Of(id));
		}
		{
			auto seg = RetrieveSegment(vertices.at(v1), vertices.at(v2));
			auto id = seg->Index();
			edge1 = edges.at(Index_Of(id));
		}
		{
			auto seg = RetrieveSegment(vertices.at(v2), vertices.at(v0));
			auto id = seg->Index();
			edge2 = edges.at(Index_Of(id));
		}

		std::array<std::shared_ptr<Edge2d>, Element2d::nbEdges> t = 
		{ std::move(edge0),std::move(edge1),std::move(edge2) };
		auto tri = std::make_shared<Element2d>(++k, std::move(t));
		tris.push_back(std::move(tri));
	}
	k = 0;
	for (const auto& x : theTris.Connectivity())
	{
		auto v0 = Index_Of(x.Value(0));
		auto v1 = Index_Of(x.Value(1));
		auto v2 = Index_Of(x.Value(2));

		const auto& tri = tris.at(k++);

		std::shared_ptr<Edge2d> edge0, edge1, edge2;
		{
			auto seg = RetrieveSegment(vertices.at(v0), vertices.at(v1));
			auto sense = seg->ChackSense(vertices.at(v0), vertices.at(v1));
			auto id = seg->Index();
			edge0 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge0);
			sense ? edge0->SetOwner(tri) : edge0->SetNeighbor(tri);
			if (NOT sense) edge0->SetSense(Standard_False);
		}
		{
			auto seg = RetrieveSegment(vertices.at(v1), vertices.at(v2));
			auto sense = seg->ChackSense(vertices.at(v1), vertices.at(v2));
			auto id = seg->Index();
			edge1 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge1);
			sense ? edge1->SetOwner(tri) : edge1->SetNeighbor(tri);
			if (NOT sense) edge1->SetSense(Standard_False);
		}
		{
			auto seg = RetrieveSegment(vertices.at(v2), vertices.at(v0));
			auto sense = seg->ChackSense(vertices.at(v2), vertices.at(v0));
			auto id = seg->Index();
			edge2 = edges.at(Index_Of(id));
			Debug_Null_Pointer(edge2);
			sense ? edge2->SetOwner(tri) : edge2->SetNeighbor(tri);
			if (NOT sense) edge2->SetSense(Standard_False);
		}
	}
	auto t = std::make_tuple(std::move(tris), std::move(edges), std::move(nodes2d));
	return std::move(t);
}

std::pair
<
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Vertex>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_ConvertToOpenFOAM::Segment>>
>
tnbLib::MeshPost2d_ConvertToOpenFOAM::CalcGragh
(
	const Entity2d_Triangulation& theTris, 
	const std::vector<std::pair<Standard_Integer, Standard_Integer>>& theBoundaries
)
{
	std::vector<std::shared_ptr<Vertex>> vertices;
	Standard_Integer k = 0;
	for (const auto& x : theTris.Points())
	{
		auto v = std::make_shared<Vertex>(++k);
		vertices.push_back(std::move(v));
	}

	std::vector<std::shared_ptr<Segment>> segments;
	k = 0;
	for (const auto& x : theBoundaries)
	{
		const auto& v0 = vertices.at(Index_Of(x.first));
		const auto& v1 = vertices.at(Index_Of(x.second));
		
		std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v0,v1 };
		auto seg = std::make_shared<Segment>(++k, std::move(paired));
		v0->Insert(seg);
		v1->Insert(seg);

		segments.push_back(std::move(seg));
	}
	for (const auto& x : theTris.Connectivity())
	{
		auto i0 = Index_Of(x.Value(0));
		auto i1 = Index_Of(x.Value(1));
		auto i2 = Index_Of(x.Value(2));

		const auto& v0 = vertices.at(i0);
		const auto& v1 = vertices.at(i1);
		const auto& v2 = vertices.at(i2);

		if (Segment::IsValidToCreate(v0, v1))
		{// segment 0 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v0,v1 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v0->Insert(seg);
			v1->Insert(seg);

			segments.push_back(std::move(seg));
		}
		if (Segment::IsValidToCreate(v1, v2))
		{// segment 1 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v1,v2 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v1->Insert(seg);
			v2->Insert(seg);

			segments.push_back(std::move(seg));
		}
		if (Segment::IsValidToCreate(v2, v0))
		{// segment 2 [6/28/2023 Payvand]
			std::array<std::shared_ptr<Vertex>, Segment::nbVertices> paired = { v2,v0 };
			auto seg = std::make_shared<Segment>(++k, std::move(paired));
			v2->Insert(seg);
			v0->Insert(seg);

			segments.push_back(std::move(seg));
		}
	}
	auto t = std::make_pair(vertices, segments);
	return std::move(t);
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
tnbLib::MeshPost2d_ConvertToOpenFOAM::RetrieveNeighborList(const std::vector<std::shared_ptr<Edge2d>>& theEdges)
{
	std::vector<Standard_Integer> neighbors;
	neighbors.reserve(theEdges.size());
	for (const auto& x : theEdges)
	{
		auto neighbor = x->Neighbor().lock();
		if (neighbor)
		{

		}
	}
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
	auto [elements_2d, edges_2d, nodes_2d] = CalcMesh2d(*Mesh(), boundaries, nodes, Extrusion());

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

void tnbLib::MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMHeader(Ostream& os)
{
	os << R"(/*--------------------------------*- C++ -*----------------------------------*\)" << endl
		<< R"(| =========                 |                                                 |)" << endl
		<< R"(| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |)" << endl
		<< R"(|  \\    /   O peration     | Version:  5.0                                   |)" << endl
		<< R"(|   \\  /    A nd           | Web:      www.OpenFOAM.org                      |)" << endl
		<< R"(|    \\/     M anipulation  |                                                 |)" << endl
		<< R"(\*---------------------------------------------------------------------------*/)" << endl;
}

void tnbLib::MeshPost2d_ConvertToOpenFOAM::WriteOpenFOAMSeperator(Ostream& os)
{
	os << R"(// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //)" << endl;
}