#include <Cad2d_Modeler.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Cad2d_Subdivide.hxx>
#include <Cad2d_EdgeEdgeIntersection.hxx>
#include <Cad2d_IntsctEntity_Segment.hxx>
#include <Cad2d_IntsctEntity_Pair.hxx>

#include <algorithm>

void tnbLib::Cad2d_Modeler::RemoveEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
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

	const auto id = theEdge->Index();
	auto edge = Cad2d_Modeler_Registry::RemoveEdgeFromRegistry(theEdge->Index());
	if (Cad2d_Modeler_Registry::IsNull(edge))
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
	const auto selected = Cad2d_Modeler_SrchEng::FindCorner(theVtx);
	if (Cad2d_Modeler_SrchEng::IsNull(selected))
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
	if (NOT theVtx->IsOrphan())
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "unable to remove the vertex: the vertex is not orphan!" << endl
			<< abort(FatalError);
	}
	const auto id = theVtx->Index();
	//auto removed = Cad2d_Modeler_Registry::RemoveVertexFromRegistry(id);

	/*if (&theVtx NOT_EQUAL &removed)
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "contradictory data: the vertex is not the same with the existing one" << endl
			<< abort(FatalError);
	}*/

	auto removed = theCorner->Remove(id);
	if (&theVtx NOT_EQUAL &removed)
	{
		FatalErrorIn("void RemoveVertex(const std::shared_ptr<Pln_Vertex>& theVtx)")
			<< "contradictory data: the vertex is not the same with the existing one" << endl
			<< abort(FatalError);
	}

	VertexCounter().ReturnToCounter(id);

	if (NOT theCorner->NbVertices())
	{
		const auto cid = theCorner->Index();

		Cad2d_Modeler_SrchEng::RemoveFromSrchEngine(theCorner);

		CornerCounter().ReturnToCounter(cid);
	}
}

void tnbLib::Cad2d_Modeler::AddVertex
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

	const auto& crn = SelectCorner(theVtx->Coord());
	if (NOT Cad2d_Modeler_SrchEng::IsNull(crn))
	{
		crn->InsertToCorners(theVtx->Index(), theVtx);
		theVtx->SetPrecision(crn->Radius());
	}
	else
	{
		auto crn = std::make_shared<corner>();
		Debug_Null_Pointer(crn);

		crn->Index() = CornerCounter().RetrieveIndex();
		crn->Name() = "corner nb. " + std::to_string(crn->Index());

		crn->InsertToCorners(theVtx->Index(), theVtx);
		theVtx->SetPrecision(crn->Radius());

		InsertToSrchEngine(crn);
	}

	//Cad2d_Modeler_Registry::RegisterToVertices(theVtx->Index(), theVtx);
}

void tnbLib::Cad2d_Modeler::AddEdge
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	theEdge->Index() = EdgeCounter().RetrieveIndex();
	theEdge->Name() = "edge nb. " + theEdge->Index();

	AddVertex(theEdge->Vtx0(), theEdge->Index());
	AddVertex(theEdge->Vtx1(), theEdge->Index());

	Cad2d_Modeler_Registry::RegisterToEdges(theEdge->Index(), theEdge);
}

void tnbLib::Cad2d_Modeler::Import
(
	const std::shared_ptr<Pln_Edge>& theEdge
)
{
	AddEdge(theEdge);
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