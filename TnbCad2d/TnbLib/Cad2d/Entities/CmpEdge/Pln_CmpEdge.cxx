#include <Pln_CmpEdge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <Adt_AvlTree.hxx>

//void tnbLib::Pln_CmpEdge::Insert
//(
//	const std::shared_ptr<Pln_Edge>& theEdge
//)
//{
//	if (theEdges_.empty())
//	{
//		theEdges_.push_back(theEdge);
//		return;
//	}
//
//	const auto& edge0 = theEdges_[theEdges_.size() - 1];
//	const auto v = Pln_Tools::Intersection(edge0, theEdge);
//	if (NOT v)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the edges are not consecutive!" << endl
//			<< abort(FatalError);
//	}
//
//	if (theEdge->Vtx1() IS_EQUAL v)
//	{
//		theEdge->Reverse();
//	}
//
//	theEdges_.push_back(theEdge);
//}
//
//void tnbLib::Pln_CmpEdge::Insert
//(
//	std::shared_ptr<Pln_Edge>&& theEdge
//)
//{
//	if (theEdges_.empty())
//	{
//		theEdges_.push_back(std::move(theEdge));
//		return;
//	}
//
//	const auto& edge0 = theEdges_[theEdges_.size() - 1];
//	const auto v = Pln_Tools::Intersection(edge0, theEdge);
//	if (NOT v)
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "the edges are not consecutive!" << endl
//			<< abort(FatalError);
//	}
//
//	if (theEdge->Vtx1() IS_EQUAL v)
//	{
//		theEdge->Reverse();
//	}
//
//	theEdges_.push_back(std::move(theEdge));
//}

Standard_Boolean 
tnbLib::Pln_CmpEdge::IsValidForWire
(
	const Standard_Real theTol
) const
{
	const auto& edges = Edges();
	if (edges.size() IS_EQUAL 1)
	{
		if (NOT edges[0]->IsRing())
		{
			return Standard_False;
		}
	}

	auto iter = edges.begin();

	auto vtx0 = (*iter)->Vertex(Pln_Edge::edgePoint::last);
	iter++;

	while (iter NOT_EQUAL edges.end())
	{
		auto vtx1 = (*iter)->Vertex(Pln_Edge::edgePoint::first);

		if (vtx0 NOT_EQUAL vtx1)
			return Standard_False;

		vtx0 = (*iter)->Vertex(Pln_Edge::edgePoint::last);

		iter++;
	}

	if (vtx0 NOT_EQUAL(*edges.begin())->Vertex(Pln_Edge::edgePoint::first))
		return Standard_False;

	return Standard_True;
}

std::shared_ptr<tnbLib::Pln_CmpEdge>
tnbLib::Pln_CmpEdge::Copy() const
{
	auto vertices = RetrieveVertices();

	std::map<Standard_Integer, std::shared_ptr<Pln_Vertex>>
		vtxMap;
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		auto insert = vtxMap.insert(std::make_pair(x->Index(), std::dynamic_pointer_cast<Pln_Vertex>(x->Copy())));
		if (NOT insert.second)
		{
			FatalErrorIn("std::shared_ptr<tnbLib::Pln_Entity> Pln_CmpEdge::Copy() const")
				<< "Unable to copy the entity" << endl
				<< abort(FatalError);
		}
	}

	auto cmpEdge = std::make_shared<Pln_CmpEdge>();
	Debug_Null_Pointer(cmpEdge);

	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		const auto& v0 = vtxMap[x->FirstVtx()->Index()];
		const auto& v1 = vtxMap[x->LastVtx()->Index()];

		if (v0 IS_EQUAL v1)
		{
			auto curve = std::dynamic_pointer_cast<Pln_Curve>(x->Curve()->Copy());
			Debug_Null_Pointer(curve);

			auto edge = std::make_shared<Pln_Ring>(x->Index(), x->Name(), v0, curve, x->Sense());
			Debug_Null_Pointer(edge);

			v0->InsertToEdges(edge->Index(), edge);

			if (x->Mesh())
			{
				edge->Mesh() = std::make_shared<Entity2d_Polygon>();
				*edge->Mesh() = *x->Mesh();
			}

			cmpEdge->Insert(edge);
		}
		else
		{
			auto curve = std::dynamic_pointer_cast<Pln_Curve>(x->Curve()->Copy());
			Debug_Null_Pointer(curve);

			auto edge = std::make_shared<Pln_Segment>(x->Index(), x->Name(), v0, v1, curve, x->Sense());
			Debug_Null_Pointer(edge);

			if (x->Mesh())
			{
				edge->Mesh() = std::make_shared<Entity2d_Polygon>();
				*edge->Mesh() = *x->Mesh();
			}

			v0->InsertToEdges(edge->Index(), edge);
			v1->InsertToEdges(edge->Index(), edge);

			cmpEdge->Insert(edge);
		}
	}
	return std::move(cmpEdge);
}

std::vector<std::shared_ptr<tnbLib::Pln_Vertex>> 
tnbLib::Pln_CmpEdge::RetrieveVertices() const
{
	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	RetrieveVerticesTo(vertices);

	return std::move(vertices);
}

void tnbLib::Pln_CmpEdge::Transform
(
	const gp_Trsf2d & t
)
{
	auto vertices = RetrieveVertices();
	for (const auto& x : vertices)
	{
		Debug_Null_Pointer(x);
		auto& coord = x->Coord();
		coord.Transform(t);
	}

	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		Debug_Null_Pointer(x->Curve());

		x->Curve()->Transform(t);

		if (x->Mesh())
		{
			x->Mesh()->Transform(t);
		}
	}
}

void tnbLib::Pln_CmpEdge::RetrieveVerticesTo
(
	std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
) const
{
	theVertices = Pln_Tools::RetrieveVertices(theEdges_);
}

void tnbLib::Pln_CmpEdge::Reverse()
{
	auto& edges = theEdges_;

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Reverse(Standard_True);
	}
	std::reverse(edges.begin(), edges.end());
}
