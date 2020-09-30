#include <Cad2d_Modeler.hxx>

#include <Geo_ApprxCurve_Info.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Wire.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_Subdivide.hxx>
#include <Cad2d_Modeler_Segment.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>
#include <Cad2d_Modeler_Tools.hxx>

#include <algorithm>

tnbLib::Cad2d_Modeler::Cad2d_Modeler()
{
	// empty body
}

Standard_Boolean 
tnbLib::Cad2d_Modeler::HasDuplication
(
	const std::shared_ptr<Pln_Edge>& theEdge,
	cad2dLib::Modeler_SelectList & theList
) const
{
	if (theList.IsContain(theEdge->Index()))
		return Standard_True;
	return Standard_False;
}

void tnbLib::Cad2d_Modeler::Select
(
	const std::shared_ptr<Pln_Edge>& theEdge,
	selctList & theList
) const
{
	if (IsNull(theEdge))
	{
		FatalErrorIn("void Select(const std::shared_ptr<Pln_Edge>& theEdge, cad2dLib::Modeler_SelectList& theList) const")
			<< "no edge has been selected!" << endl
			<< abort(FatalError);
	}

	theList.Import(theEdge->Index(), theEdge);
}

void tnbLib::Cad2d_Modeler::SelectAll
(
	selctList & theList
) const
{
	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x.second);
		theList.Import(x.second->Index(), x.second);
	}
}

void tnbLib::Cad2d_Modeler::deSelect
(
	const std::shared_ptr<Pln_Edge>& theEdge,
	selctList & theList
) const
{
	if (IsNull(theEdge))
	{
		FatalErrorIn("void deSelect(const std::shared_ptr<Pln_Edge>& theEdge, cad2dLib::Modeler_SelectList& theList) const")
			<< "no edge has been selected!" << endl
			<< abort(FatalError);
	}

	auto item = theList.Remove(theEdge->Index());
	if (item NOT_EQUAL theEdge)
	{
		FatalErrorIn("void deSelect(const std::shared_ptr<Pln_Edge>& theEdge, cad2dLib::Modeler_SelectList& theList) const")
			<< "contradictory data!" << endl
			<< abort(FatalError);
	}
}

void tnbLib::Cad2d_Modeler::deSelectAll
(
	selctList & theList
) const
{
	theList.Clear();
}

void tnbLib::Cad2d_Modeler::RemoveRing
(
	const std::shared_ptr<Pln_Ring>& theRing
)
{
#ifdef _DEBUG
	if (NOT IsContain(theRing))
	{
		FatalErrorIn("void RemoveRing(const std::shared_ptr<Pln_Ring>& theRing)")
			<< "the edge is not in the modeler!" << endl
			<< abort(FatalError);
	}
#endif // DEBUG

	const auto& v = theRing->Vtx0();

	v->RemoveFromEdges(theRing->Index());

	if (v->IsOrphan())
	{
		RemoveVertex(v);
	}

	const auto crn = FindCorner(v);
	if (NOT crn)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to find the corner0" << endl
			<< " - radius = " << Radius() << endl
			<< abort(FatalError);
	}

	if (NOT crn->IsContains(v))
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data: the corner doesn't contain the vertex!" << endl
			<< " - corner's index = " << crn->Index() << endl
			<< " - corner's name = " << crn->Name() << endl
			<< endl
			<< " - vertex's index = " << v->Index() << endl
			<< " - vertex's name = " << v->Name() << endl
			<< abort(FatalError);
	}

	const auto segmnt = cad2dLib::Modeler_Tools::HasRing(crn);
	if (NOT segmnt)
	{
		FatalErrorIn(FunctionSIG)
			<< "there is not segment between two corners" << endl
			<< " - corner0 = " << crn->Index() << endl
			<< " - corner1 = " << crn->Index() << endl
			<< abort(FatalError);
	}

	const auto id = theRing->Index();
	if (segmnt->RemoveFromEdges(id) NOT_EQUAL theRing)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data" << endl
			<< abort(FatalError);
	}

	if (NOT segmnt->NbEdges())
	{
		if (crn->RemoveFromSegments(segmnt->Index()).lock() NOT_EQUAL segmnt)
		{
			FatalErrorIn(FunctionSIG)
				<< "contradictory data" << endl
				<< abort(FatalError);
		}

		if (NOT crn->NbSegments())
		{
			cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine(crn);
		}

		RemoveSegment(segmnt);
	}

	auto edge = cad2dLib::Modeler_Registry::RemoveEdgeFromRegistry(theRing->Index());
	if (cad2dLib::Modeler_Registry::IsNull(edge))
	{
		FatalErrorIn("void RemoveRing(const std::shared_ptr<Pln_Ring>&)")
			<< "the edge is not in the registry: " << id << endl
			<< abort(FatalError);
	}

	EdgeCounter().ReturnToCounter(id);
}

void tnbLib::Cad2d_Modeler::RemoveEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	if (theEdge->IsRing())
	{
		auto ring = std::dynamic_pointer_cast<Pln_Ring>(theEdge);
		Debug_Null_Pointer(ring);

		RemoveRing(ring);
		return;
	}

#ifdef _DEBUG
	if (NOT IsContain(theEdge))
	{
		FatalErrorIn("void RemoveEdge(const std::shared_ptr<Pln_Edge>& theEdge)")
			<< "the edge is not in the modeler!" << endl
			<< abort(FatalError);
	}
#endif // DEBUG

	const auto& v0 = theEdge->Vtx0();
	const auto& v1 = theEdge->Vtx1();

	v0->RemoveFromEdges(theEdge->Index());
	v1->RemoveFromEdges(theEdge->Index());

	if (v0->IsOrphan())
	{
		RemoveVertex(v0);
	}

	if (v1->IsOrphan())
	{
		RemoveVertex(v1);
	}

	const auto crn0 = FindCorner(v0);
	if (NOT crn0)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to find the corner0" << endl
			<< " - radius = " << Radius() << endl
			<< abort(FatalError);
	}

	if (NOT crn0->IsContains(v0))
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data: the corner doesn't contain the vertex!" << endl
			<< " - corner's index = " << crn0->Index() << endl
			<< " - corner's name = " << crn0->Name() << endl
			<< endl
			<< " - vertex's index = " << v0->Index() << endl
			<< " - vertex's name = " << v0->Name() << endl
			<< abort(FatalError);
	}

	const auto crn1 = FindCorner(v1);
	if (NOT crn1)
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to find the corner1" << endl
			<< " - radius = " << Radius() << endl
			<< abort(FatalError);
	}

	if (NOT crn1->IsContains(v1))
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data: the corner doesn't contain the vertex!" << endl
			<< " - corner's index = " << crn1->Index() << endl
			<< " - corner's name = " << crn1->Name() << endl
			<< endl
			<< " - vertex's index = " << v1->Index() << endl
			<< " - vertex's name = " << v1->Name() << endl
			<< abort(FatalError);
	}

	const auto segmnt = cad2dLib::Modeler_Tools::IsSegment(crn0, crn1);
	if (NOT segmnt)
	{
		FatalErrorIn(FunctionSIG)
			<< "there is not segment between two corners" << endl
			<< " - corner0 = " << crn0->Index() << endl
			<< " - corner1 = " << crn1->Index() << endl
			<< abort(FatalError);
	}

	const auto id = theEdge->Index();
	if (segmnt->RemoveFromEdges(id) NOT_EQUAL theEdge)
	{
		FatalErrorIn(FunctionSIG)
			<< "contradictory data" << endl
			<< abort(FatalError);
	}

	if (NOT segmnt->NbEdges())
	{
		if (crn0 IS_EQUAL crn1)
		{
			if (crn0->RemoveFromSegments(segmnt->Index()).lock() NOT_EQUAL segmnt)
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			if (NOT crn0->NbSegments())
			{
				cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine(crn0);
			}
		}
		else
		{
			if (crn0->RemoveFromSegments(segmnt->Index()).lock() NOT_EQUAL segmnt)
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			if (crn1->RemoveFromSegments(segmnt->Index()).lock() NOT_EQUAL segmnt)
			{
				FatalErrorIn(FunctionSIG)
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			if (NOT crn0->NbSegments())
			{
				cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine(crn0);
			}

			if (NOT crn1->NbSegments())
			{
				cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine(crn1);
			}
		}
		

		RemoveSegment(segmnt);
	}

	auto edge = cad2dLib::Modeler_Registry::RemoveEdgeFromRegistry(theEdge->Index());
	if (cad2dLib::Modeler_Registry::IsNull(edge))
	{
		FatalErrorIn("void RemoveEdge(const std::shared_ptr<Pln_Edge>& theEdge)")
			<< "the edge is not in the registry: " << id << endl
			<< abort(FatalError);
	}

	EdgeCounter().ReturnToCounter(id);
}

void tnbLib::Cad2d_Modeler::RemoveVertex
(
	const std::shared_ptr<Pln_Vertex>& theVtx
)
{
	const auto& selected = cad2dLib::Modeler_SrchEng::FindCorner(theVtx);
	if (cad2dLib::Modeler_SrchEng::IsNull(selected))
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "contradictory data: found no corner!" << endl
			<< abort(FatalError);
	}
	RemoveVertex(theVtx, selected);
}

void tnbLib::Cad2d_Modeler::RemoveVertex
(
	const std::shared_ptr<Pln_Vertex>& theVtx, 
	const std::shared_ptr<corner>& theCorner
)
{
	Debug_Null_Pointer(theVtx);
	Debug_Null_Pointer(theCorner);

	if (NOT theVtx->IsOrphan())
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "unable to remove the vertex: the vertex is not orphan!" << endl
			<< abort(FatalError);
	}
	const auto id = theVtx->Index();
	const auto& vs = theCorner->Vertices();

	auto removed = theCorner->Remove(id);

	if (theVtx NOT_EQUAL removed)
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "contradictory data: the vertex is not the same with the existing one" << endl
			<< abort(FatalError);
	}

	VertexCounter().ReturnToCounter(id);

	if (NOT theCorner->NbVertices())
	{
		const auto cid = theCorner->Index();

		cad2dLib::Modeler_SrchEng::RemoveFromSrchEngine(theCorner);

		CornerCounter().ReturnToCounter(cid);
	}
}

void tnbLib::Cad2d_Modeler::RemoveSegment
(
	const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
)
{
	if (theSegmnt->NbEdges())
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to remove the segment!" << endl
			<< abort(FatalError);
	}
	const auto& crn0 = theSegmnt->Crn0();
	const auto& crn1 = theSegmnt->Crn1();

	if (crn0->IsContains(theSegmnt) OR crn1->IsContains(theSegmnt))
	{
		FatalErrorIn(FunctionSIG)
			<< "unable to remove the segment!" << endl
			<< abort(FatalError);
	}

	const auto id = theSegmnt->Index();
	if (cad2dLib::Modeler_Segments::RemoveFromSegments(id) NOT_EQUAL theSegmnt)
	{
		FatalErrorIn(FunctionSIG)
			<< "something goes wrong in removing the segment from the registry!" << endl
			<< " - index = " << theSegmnt->Index() << endl
			<< " - name = " << theSegmnt->Name() << endl
			<< abort(FatalError);
	}

	SegmntCounter().ReturnToCounter(id);
}

std::shared_ptr<tnbLib::cad2dLib::Modeler_Corner> 
tnbLib::Cad2d_Modeler::AddVertex
(
	const std::shared_ptr<Pln_Vertex>& theVtx, 
	const Standard_Integer theEdgeIndex
)
{
	theVtx->Index() = VertexCounter().RetrieveIndex();

	std::ostringstream stream;
	stream << "vertex " <<
		std::to_string(theVtx->Index()) << " edge " <<
		std::to_string(theEdgeIndex);

	auto name = word(stream.str());
	theVtx->Name() = std::move(name);

	auto crn = SelectCorner(theVtx->Coord());
	if (NOT cad2dLib::Modeler_SrchEng::IsNull(crn))
	{
		crn->InsertToCorners(theVtx->Index(), theVtx);
		//theVtx->SetPrecision(crn->Radius());
		return std::move(crn);
	}
	else
	{
		auto c = std::make_shared<corner>();
		Debug_Null_Pointer(c);

		c->Index() = CornerCounter().RetrieveIndex();
		c->Name() = "corner nb. " + std::to_string(c->Index());

		c->InsertToCorners(theVtx->Index(), theVtx);
		c->SetCoord(theVtx->Coord());

		//theVtx->SetPrecision(crn->Radius());

		InsertToSrchEngine(c);
		return std::move(c);
	}
}

Standard_Integer
tnbLib::Cad2d_Modeler::AddEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	theEdge->Index() = EdgeCounter().RetrieveIndex();
	theEdge->Name() = "edge nb. " + theEdge->Index();

	const auto crn0 = AddVertex(theEdge->Vtx0(), theEdge->Index());
	const auto crn1 = AddVertex(theEdge->Vtx1(), theEdge->Index());

	const auto& v0 = theEdge->Vtx0();
	const auto& v1 = theEdge->Vtx1();

	/*WARNING! the index of the edge should not be altered!*/
	v0->InsertToEdges(theEdge->Index(), theEdge);
	v1->InsertToEdges(theEdge->Index(), theEdge);

	cad2dLib::Modeler_Registry::RegisterToEdges(theEdge->Index(), theEdge);

	if (crn0 IS_EQUAL crn1)
	{
		auto segmnt = cad2dLib::Modeler_Tools::HasRing(crn0);
		if (NOT segmnt)
		{
			segmnt = std::make_shared<cad2dLib::Modeler_Ring>(crn0);

			const auto segId = AddSegment(segmnt);
			crn0->ImportToSegments(segId, segmnt);
		}

		segmnt->ImportToEdges(theEdge->Index(), theEdge);
	}
	else
	{
		auto segmnt = cad2dLib::Modeler_Tools::IsSegment(crn0, crn1);
		if (NOT segmnt)
		{
			segmnt = std::make_shared<cad2dLib::Modeler_Segment>(crn0, crn1);

			const auto segId = AddSegment(segmnt);
			crn0->ImportToSegments(segId, segmnt);
			crn1->ImportToSegments(segId, segmnt);
		}

		segmnt->ImportToEdges(theEdge->Index(), theEdge);
	}

	return theEdge->Index();
}

Standard_Integer 
tnbLib::Cad2d_Modeler::AddRing
(
	const std::shared_ptr<Pln_Ring>& theRing
)
{
	theRing->Index() = EdgeCounter().RetrieveIndex();
	theRing->Name() = "ring nb. " + theRing->Index();

	const auto crn = AddVertex(theRing->Vtx0(), theRing->Index());

	const auto& v = theRing->Vtx0();

	v->InsertToEdges(theRing->Index(), theRing);

	cad2dLib::Modeler_Registry::RegisterToEdges(theRing->Index(), theRing);

	auto segmnt = cad2dLib::Modeler_Tools::HasRing(crn);
	if (NOT segmnt)
	{
		segmnt = std::make_shared<cad2dLib::Modeler_Ring>(crn);

		const auto segId = AddSegment(segmnt);
		crn->ImportToSegments(segId, segmnt);
	}

	segmnt->ImportToEdges(theRing->Index(), theRing);
	return theRing->Index();
}

Standard_Integer
tnbLib::Cad2d_Modeler::AddPlane
(
	const std::shared_ptr<Cad2d_Plane>& thePlane
)
{
	thePlane->Index() = PlaneCounter().RetrieveIndex();
	thePlane->Name() = "plane nb. " + thePlane->Index();

	InsertToPlanes(thePlane->Index(), thePlane);

	return thePlane->Index();
}

Standard_Integer 
tnbLib::Cad2d_Modeler::AddSegment
(
	const std::shared_ptr<cad2dLib::Modeler_Segment>& theSegmnt
)
{
	Debug_Null_Pointer(theSegmnt);
	theSegmnt->Index() = SegmntCounter().RetrieveIndex();
	theSegmnt->Name() = "segment nb. " + theSegmnt->Index();

	InsertToSegments(theSegmnt->Index(), theSegmnt);
	return theSegmnt->Index();
}

std::vector<std::shared_ptr<tnbLib::Pln_Edge>> 
tnbLib::Cad2d_Modeler::MakeChain
(
	selctList & theList
)
{
	std::map<Standard_Integer, std::shared_ptr<corner>> vertexToCornerMap;
	for (const auto& x : theList.Items())
	{
		const auto& edge = x.second;

		Debug_Null_Pointer(edge->Vtx0());
		Debug_Null_Pointer(edge->Vtx1());

		const auto& v0 = edge->Vtx0();
		const auto& v1 = edge->Vtx1();

		const auto& corner0 = FindCorner(v0);
		const auto& corner1 = FindCorner(v1);

		if (IsNull(corner0))
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "unable to detect the corner for v0" << endl
				<< abort(FatalError);
		}

		if (IsNull(corner1))
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "unable to detect the corner for v1" << endl
				<< abort(FatalError);
		}

		auto insert0 = vertexToCornerMap.insert(std::make_pair(v0->Index(), corner0));
		if (NOT insert0.second)
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "unable to import the corner to the tree" << endl
				<< abort(FatalError);
		}

		auto insert1 = vertexToCornerMap.insert(std::make_pair(v1->Index(), corner1));
		if (NOT insert1.second)
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "unable to import the corner to the tree" << endl
				<< abort(FatalError);
		}
	}

	auto& edges = theList.ChangeItems();
	auto iter = edges.begin();

	auto item = iter->second;
	edges.erase(iter);

	std::vector<std::shared_ptr<Pln_Edge>> chain;
	chain.reserve(theList.NbItems());

	chain.push_back(item);
	while (edges.size())
	{
		const auto& vtx = item->Vtx1();
		
		auto citer = vertexToCornerMap.find(vtx->Index());
		if (citer IS_EQUAL vertexToCornerMap.end())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "unable to find corner" << endl
				<< abort(FatalError);
		}

		const auto& c = citer->second;
		Debug_Null_Pointer(c);

		std::shared_ptr<Pln_Edge> next_edge;

		Standard_Integer k = 0;
		const auto& cvertices = c->Vertices();
		for (const auto& x : cvertices)
		{
			const auto& cvtx = x.second;
			Debug_Null_Pointer(cvtx);

			const auto& cedges = cvtx->Edges();
			if (cedges.size() NOT_EQUAL 1)
			{
				FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
					<< "contradictory data" << endl
					<< abort(FatalError);
			}

			auto next = cedges.begin()->second.lock();
			Debug_Null_Pointer(next);

			auto found = edges.find(next->Index());
			if (found IS_EQUAL edges.end())
				continue;

			k++;
			next_edge = next;
		}

		if (k NOT_EQUAL 1)
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "the chain is not closed or is not defined any valid type of non-manifold object!" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(next_edge);

		auto iter = edges.find(next_edge->Index());
		if (iter IS_EQUAL edges.end())
		{
			FatalErrorIn("std::vector<std::shared_ptr<Pln_Edge>> MakeChain(const selctList& theList)")
				<< "contradictory data" << endl
				<< abort(FatalError);
		}

		edges.erase(iter);

		item = std::move(next_edge);

		chain.push_back(item);
	}
	return std::move(chain);
}

Standard_Integer
tnbLib::Cad2d_Modeler::Import
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	if (theEdge->IsRing())
	{
		auto ring = std::dynamic_pointer_cast<Pln_Ring>(theEdge);
		Debug_Null_Pointer(ring);

		return AddRing(ring);
	}
	else
	{
		return AddEdge(theEdge);
	}
}

void tnbLib::Cad2d_Modeler::Import
(
	const std::vector<std::shared_ptr<Pln_Edge>>& theEdegs
)
{
	for (const auto& x : theEdegs)
	{
		Import(x);
	}
}

namespace tnbLib
{

	typedef std::vector<std::shared_ptr<Cad2d_IntsctEntity_Segment>> entityList;
}

void tnbLib::Cad2d_Modeler::Trim
(
	const std::shared_ptr<Pln_Edge>& theEdge0, 
	const std::shared_ptr<Pln_Edge>& theEdge1
)
{
	if (NOT theEdge0)
	{
		FatalErrorIn("void Trim(const std::shared_ptr<Pln_Edge>& theEdge0, const std::shared_ptr<Pln_Edge>& theEdge1)")
			<< "the edge0 is null" << endl
			<< abort(FatalError);
	}

	if (NOT theEdge1)
	{
		FatalErrorIn("void Trim(const std::shared_ptr<Pln_Edge>& theEdge0, const std::shared_ptr<Pln_Edge>& theEdge1)")
			<< "the edge1 is null" << endl
			<< abort(FatalError);
	}

	auto intAlg = std::make_shared<Cad2d_EdgeEdgeIntersection>();
	Debug_Null_Pointer(intAlg);

	intAlg->LoadEdge0(theEdge0);
	intAlg->LoadEdge1(theEdge1);

	intAlg->Perform();
	Debug_If_Condition_Message(NOT intAlg->IsDone(), "the intersection algorithm is not performed!");

	if (NOT intAlg->NbEntities())
	{
		return;
	}

	const auto& pairList = intAlg->Entities();

	entityList entities0, entities1;
	for (const auto& x : pairList)
	{
		Debug_Null_Pointer(x);

		auto ent0 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(x->Entity0());
		Debug_Null_Pointer(ent0);

		auto ent1 = std::dynamic_pointer_cast<Cad2d_IntsctEntity_Segment>(x->Entity1());
		Debug_Null_Pointer(ent1);

		entities0.push_back(std::move(ent0));
		entities1.push_back(std::move(ent1));
	}

	Cad2d_IntsctEntity_Segment::SortEntities(entities0);
	Cad2d_IntsctEntity_Segment::SortEntities(entities1);

	auto sub0 = Cad2d_IntsctEntity_Segment::SubdivideEdge
	(
		theEdge0, entities0, 
		std::max(theEdge0->Vtx0()->Precision(), theEdge0->Vtx1()->Precision())
	);

	if (NOT theEdge0->Sense())
	{
		std::reverse(sub0.begin(), sub0.end());
	}

	auto sub1 = Cad2d_IntsctEntity_Segment::SubdivideEdge
	(
		theEdge1, entities1,
		std::max(theEdge1->Vtx0()->Precision(), theEdge1->Vtx1()->Precision())
	);

	if (NOT theEdge1->Sense())
	{
		std::reverse(sub1.begin(), sub1.end());
	}

	RemoveEdge(theEdge0);
	RemoveEdge(theEdge1);

	for (const auto& x : sub0)
	{
		Debug_Null_Pointer(x);

		auto edge = std::make_shared<Pln_Edge>();
		Debug_Null_Pointer(edge);

		Import(edge);
	}

	for (const auto& x : sub1)
	{
		Debug_Null_Pointer(x);

		auto edge = std::make_shared<Pln_Edge>();
		Debug_Null_Pointer(edge);

		Import(edge);
	}
}

//void tnbLib::Cad2d_Modeler::MakePlanes(selctList & theList)
//{
//	const auto items = theList.RetrieveItems();
//	const auto tol = Radius();
//
//	
//}

Standard_Integer 
tnbLib::Cad2d_Modeler::MakePlane
(
	selctList & theList
)
{
	const auto items = theList.RetrieveItems();
	const auto tol = Radius();

	const auto edges = cad2dLib::Modeler_Tools::MakeConsecutive(items, tol);

	auto info = std::make_shared<Geo_ApprxCurve_Info>();
	Debug_Null_Pointer(info);

	info->SetAngle(1.0);
	info->SetApprox(1.0E-3);
	info->SetMinSize(1.0E-3);
	for (const auto& x : edges)
	{
		if (NOT x->Mesh())
			x->Approx(info);
	}

	const auto wires = Pln_Tools::RetrieveWires(edges);
	if (wires.size() NOT_EQUAL 1)
	{
		FatalErrorIn("void MakePlane(selctList& theList)")
			<< "contradictory data: multiply wires detected!" << endl
			<< abort(FatalError);
	}

	const auto& wire = wires[0];

	wire->ApplyOrientation(Pln_Orientation::Pln_Orientation_CCW);

	const auto plane = Pln_Tools::MakePlane(wire, gp::XOY());
	Debug_Null_Pointer(plane);

	return AddPlane(plane);
}