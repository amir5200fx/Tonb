#include <MeshPost2d_OFTopology.hxx>

#include <MeshIO2d_FEA.hxx>
#include <Entity2d_CmpMesh.hxx>
#include <Entity2d_CmpConnect_Triangle.hxx>
#include <Entity2d_CmpConnect_Quad.hxx>

Standard_Boolean 
tnbLib::MeshPost2d_OFTopology::Compare
(
	const std::weak_ptr<Segment>& theS0, 
	const std::weak_ptr<Segment>& theS1
)
{
	const auto s0 = theS0.lock();
	const auto s1 = theS1.lock();
	return s0->Index() < s1->Index();
}

void tnbLib::MeshPost2d_OFTopology::Vertex::Insert
(
	const std::shared_ptr<Segment>& theSeg
)
{
	const auto insert = theSegments_.insert(theSeg);
	if (NOT insert.second)
	{
		FatalErrorIn(FunctionSIG)
			<< "duplicate data has been detected." << endl
			<< " - id: " << theSeg->Index() << endl
			<< abort(FatalError);
	}
}

Standard_Boolean
tnbLib::MeshPost2d_OFTopology::Segment::ChackSense
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

std::shared_ptr<tnbLib::MeshPost2d_OFTopology::Vertex>
tnbLib::MeshPost2d_OFTopology::Segment::Opposite
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

std::shared_ptr<tnbLib::MeshPost2d_OFTopology::Segment>
tnbLib::MeshPost2d_OFTopology::Segment::IsValidToCreate
(
	const std::shared_ptr<Vertex>& theV0,
	const std::shared_ptr<Vertex>& theV1
)
{
	if (theV0 IS_EQUAL theV1)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "degenerated segment has been detected." << endl
			<< " v0 = " << theV0->Index() << " , v1 = " << theV1->Index() << endl
			<< abort(FatalError);
	}
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
			return std::move(seg);
		}
	}
	return nullptr;
}

Standard_Boolean
tnbLib::MeshPost2d_OFTopology::Segment::Compare
(
	const std::shared_ptr<Segment>& theS0,
	const std::shared_ptr<Segment>& theS1
)
{
	Debug_Null_Pointer(theS0);
	Debug_Null_Pointer(theS1);
	return theS0->Index() < theS1->Index();
}

std::tuple
<
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_OFTopology::Vertex>>,
	std::vector<std::shared_ptr<tnbLib::MeshPost2d_OFTopology::Segment>>,
	std::map<Standard_Integer, Standard_Integer>
> 
tnbLib::MeshPost2d_OFTopology::CalcGragh
(
	const Entity2d_CmpMesh& theMesh,
	const std::vector<std::tuple<Standard_Integer, Standard_Integer, word>>& theBoundaries
)
{
	std::map<Standard_Integer, Standard_Integer> renumber;
	std::vector<std::shared_ptr<Vertex>> vertices;
	Standard_Integer k = 0;
	for (const auto& x : theMesh.Coords())
	{
		auto v = std::make_shared<Vertex>(++k);
		vertices.push_back(std::move(v));
	}

	std::vector<std::shared_ptr<Segment>> segments;
	k = 0;
	for (const auto& x : theBoundaries)
	{
		auto [i0, i1, name] = x;
		const auto& v0 = vertices.at(Index_Of(i0));
		const auto& v1 = vertices.at(Index_Of(i1));

		std::array<std::shared_ptr<Vertex>, Segment::nbVertices> 
			paired = { v0,v1 };
		auto seg = 
			std::make_shared<Segment>(++k, std::move(paired));
		v0->Insert(seg);
		v1->Insert(seg);
		seg->SetBoundary(Standard_True);
		seg->SetPhysic(name);
		segments.push_back(std::move(seg));
		renumber.insert(std::make_pair(k, k));
	}
	const auto maxBndId = segments.size();
	Standard_Integer j = 0;
	for (const auto& x : theMesh.Indices())
	{
		if (x->IsTriangle())
		{
			auto tri = std::dynamic_pointer_cast<Entity2d_CmpConnect_Triangle>(x);
			Debug_Null_Pointer(tri);

			auto i0 = Index_Of(tri->Value(0));
			auto i1 = Index_Of(tri->Value(1));
			auto i2 = Index_Of(tri->Value(2));

			const auto& v0 = vertices.at(i0);
			const auto& v1 = vertices.at(i1);
			const auto& v2 = vertices.at(i2);

			j++;

			if (auto created = Segment::IsValidToCreate(v0, v1))
			{// segment 0 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v0,v1 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v0->Insert(seg);
				v1->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}

			if (auto created = Segment::IsValidToCreate(v1, v2))
			{// segment 1 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v1,v2 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v1->Insert(seg);
				v2->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}
			if (auto created = Segment::IsValidToCreate(v2, v0))
			{// segment 2 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v2,v0 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v2->Insert(seg);
				v0->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}
		}
		else if (x->IsQuadrilateral())
		{
			auto quad = std::dynamic_pointer_cast<Entity2d_CmpConnect_Quad>(x);
			Debug_Null_Pointer(tri);

			auto i0 = Index_Of(quad->Value(0));
			auto i1 = Index_Of(quad->Value(1));
			auto i2 = Index_Of(quad->Value(2));
			auto i3 = Index_Of(quad->Value(3));

			const auto& v0 = vertices.at(i0);
			const auto& v1 = vertices.at(i1);
			const auto& v2 = vertices.at(i2);
			const auto& v3 = vertices.at(i3);

			j++;

			if (auto created = Segment::IsValidToCreate(v0, v1))
			{// segment 0 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v0,v1 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v0->Insert(seg);
				v1->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}

			if (auto created = Segment::IsValidToCreate(v1, v2))
			{// segment 1 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v1,v2 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v1->Insert(seg);
				v2->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}
			if (auto created = Segment::IsValidToCreate(v2, v3))
			{// segment 2 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v2,v3 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v2->Insert(seg);
				v3->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}
			if (auto created = Segment::IsValidToCreate(v3, v0))
			{// segment 3 [6/28/2023 Payvand]
				created->IsBoundary() ? created->SetOwner(j) : created->SetNeighbor(j);
			}
			else
			{
				std::array<std::shared_ptr<Vertex>, Segment::nbVertices>
					paired = { v3,v0 };
				auto seg = std::make_shared<Segment>
					(++k, std::move(paired));
				v3->Insert(seg);
				v0->Insert(seg);

				seg->SetOwner(j);
				segments.push_back(std::move(seg));
				renumber.insert(std::make_pair(k, k));
			}
		}
		else
		{
			FatalErrorIn(FunctionSIG) << endl
				<< "Unspecified type of element." << endl
				<< abort(FatalError);
		}
		
	}
	const auto nbIntSegments = segments.size() - maxBndId;
	for (size_t i = 0; i < maxBndId; i++)
	{
		auto id = segments.at(i)->Index();
		segments.at(i)->Index() += (Standard_Integer)nbIntSegments;
		renumber.at(id) = segments.at(i)->Index();
	}
	k = 0;
	for (size_t i = maxBndId; i < segments.size(); i++)
	{
		auto id = segments.at(i)->Index();
		segments.at(i)->Index() = ++k;
		renumber.at(id) = segments.at(i)->Index();
	}
	auto t = std::make_tuple(std::move(vertices), std::move(segments), std::move(renumber));
	return std::move(t);
}

std::vector<std::tuple<Standard_Integer, Standard_Integer, tnbLib::word>>
tnbLib::MeshPost2d_OFTopology::RetrieveBoundaries(const MeshIO2d_FEA& theMeshIO)
{
	std::vector<std::tuple<Standard_Integer, Standard_Integer, word>> boundaries;
	for (const auto& x : theMeshIO.Boundaries())
	{
		const auto& poly = x.second;
		for (const auto& p : *poly)
		{
			auto t = std::make_tuple(p.Value(0), p.Value(1), x.first);
			boundaries.push_back(std::move(t));
		}
	}
	return std::move(boundaries);
}

std::vector<tnbLib::MeshPost2d_OFTopology::Edge>
tnbLib::MeshPost2d_OFTopology::RetrieveEdges() const
{
	auto boundaries = RetrieveBoundaries();
	std::vector<Edge> edges;
	edges.reserve(Interiors().size() + boundaries.size());
	for (const auto& x : Interiors())
	{
		edges.push_back(x);
	}
	for (const auto& x : boundaries)
	{
		edges.push_back(x);
	}
	return std::move(edges);
}

std::vector<tnbLib::MeshPost2d_OFTopology::Edge> 
tnbLib::MeshPost2d_OFTopology::RetrieveBoundaries() const
{
	std::vector<Edge> edges;
	for (const auto& x : theBoundaries_)
	{
		for (const auto& e : x.second)
		{
			edges.push_back(e);
		}
	}
	std::sort(edges.begin(), edges.end(), [](const Edge& e0, const Edge& e1) 
		{return e0.Index() < e1.Index(); });
	return std::move(edges);
}

std::map<Standard_Integer, std::vector<Standard_Integer>> 
tnbLib::MeshPost2d_OFTopology::RetrieveElementToEdgesMap() const
{
	auto boundaries = RetrieveBoundaries();
	std::map<Standard_Integer, std::vector<Standard_Integer>> elmToEdges;
	for (const auto& x : theInteriors_)
	{
		auto owner = x.Owner();
		{
			auto iter = elmToEdges.find(owner);
			if (iter IS_EQUAL elmToEdges.end())
			{
				elmToEdges.insert(std::make_pair(owner, std::vector<Standard_Integer>()));
			}
		}
		elmToEdges.at(owner).push_back(x.Index());
		auto neighbor = x.Neighbor();
		if (NOT neighbor)
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data has been detected." << endl
				<< abort(FatalError);
		}
		{
			auto iter = elmToEdges.find(neighbor);
			if (iter IS_EQUAL elmToEdges.end())
			{
				elmToEdges.insert(std::make_pair(neighbor, std::vector<Standard_Integer>()));
			}
			elmToEdges.at(neighbor).push_back(x.Index());
		}	
	}
	for (const auto& x : boundaries)
	{
		auto owner = x.Owner();
		auto iter = elmToEdges.find(owner);
		if (iter IS_EQUAL elmToEdges.end())
		{
			elmToEdges.insert(std::make_pair(owner, std::vector<Standard_Integer>()));
		}
		elmToEdges.at(owner).push_back(x.Index());
	}
	return std::move(elmToEdges);
}

void tnbLib::MeshPost2d_OFTopology::Perform()
{
	if (NOT MeshIO())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}
	const auto boundaries = RetrieveBoundaries(*MeshIO());
	if (NOT MeshIO()->Mesh())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}

	auto [vertices, segments, indices] = 
		CalcGragh(*MeshIO()->Mesh(), boundaries);

	std::vector<Edge> intSegments;
	std::map<word, std::vector<Edge>> boundaryMap;
	for (const auto& x : segments)
	{
		if (NOT x->IsBoundary())
		{
			const auto v0 = x->Vertices().at(0)->Index();
			const auto v1 = x->Vertices().at(1)->Index();

			Edge edge(v0, v1);
			edge.SetIndex(x->Index());
			edge.SetOwner(x->Owner());
			edge.SetNeighbor(x->Neighbor());
			intSegments.push_back(std::move(edge));
		}
		else
		{
			auto iter = boundaryMap.find(x->Physic());
			if (iter IS_EQUAL boundaryMap.end())
			{
				auto paired = std::make_pair(x->Physic(), std::vector<Edge>());
				boundaryMap.insert(std::move(paired));
			}
			auto v0 = x->Vertices().at(0)->Index();
			auto v1 = x->Vertices().at(1)->Index();

			Edge edge(v0, v1);
			edge.SetIndex(x->Index());
			edge.SetOwner(x->Owner());
			edge.SetNeighbor(0);

			boundaryMap.at(x->Physic()).push_back(std::move(edge));
		}
	}
	theInteriors_ = std::move(intSegments);
	theBoundaries_ = std::move(boundaryMap);
	Change_IsDone() = Standard_True;
}