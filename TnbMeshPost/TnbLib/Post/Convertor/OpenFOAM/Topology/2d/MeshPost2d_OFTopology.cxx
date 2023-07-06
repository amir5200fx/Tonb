#include <MeshPost2d_OFTopology.hxx>

#include <MeshIO2d_FEA.hxx>
#include <Entity2d_Triangulation.hxx>

Standard_Boolean 
tnbLib::MeshPost2d_OFTopology::Compare
(
	const std::weak_ptr<Segment>& theS0, 
	const std::weak_ptr<Segment>& theS1
)
{
	auto s0 = theS0.lock();
	auto s1 = theS1.lock();
	return s0->Index() < s1->Index();
}

void tnbLib::MeshPost2d_OFTopology::Vertex::Insert
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
	const Entity2d_Triangulation& theTris,
	const std::vector<std::tuple<Standard_Integer, Standard_Integer, word>>& theBoundaries
)
{
	std::map<Standard_Integer, Standard_Integer> renumber;
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
	for (const auto& x : theTris.Connectivity())
	{
		auto i0 = Index_Of(x.Value(0));
		auto i1 = Index_Of(x.Value(1));
		auto i2 = Index_Of(x.Value(2));

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

void tnbLib::MeshPost2d_OFTopology::Perform()
{
	if (NOT MeshIO())
	{
		FatalErrorIn(FunctionSIG)
			<< "no mesh has been loaded." << endl
			<< abort(FatalError);
	}
	auto boundaries = RetrieveBoundaries(*MeshIO());
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
			auto v0 = x->Vertices().at(0)->Index();
			auto v1 = x->Vertices().at(1)->Index();

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