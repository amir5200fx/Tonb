#include <Pln_CmpEdge.hxx>

#include <Entity2d_Polygon.hxx>
#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Ring.hxx>
#include <Pln_Tools.hxx>
#include <Pln_Curve.hxx>
#include <error.hxx>
#include <OSstream.hxx>

#include <Adt_AvlTree.hxx>

Standard_Boolean 
tnbLib::Pln_CmpEdge::IsValidForWire
(
	const Standard_Real theTol
) const
{
	const auto& edges = Edges();
	if (edges.size() IS_EQUAL 1)
	{
		if (edges[0]->Vtx0() NOT_EQUAL edges[0]->Vtx1())
		{
			return Standard_False;
		}
	}

	auto iter = edges.begin();

	auto vtx0 = (*iter)->Vtx1();
	iter++;

	while (iter NOT_EQUAL edges.end())
	{
		auto vtx1 = (*iter)->Vtx0();

		if (vtx0 NOT_EQUAL vtx1)
			return Standard_False;

		vtx0 = (*iter)->Vtx1();

		iter++;
	}

	if (vtx0 NOT_EQUAL(*edges.begin())->Vtx0())
		return Standard_False;

	return Standard_True;
}

std::shared_ptr<tnbLib::Pln_Entity>
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

	auto cmpEdge = std::make_shared<Pln_CmpEdge>(Index(), Name());
	Debug_Null_Pointer(cmpEdge);

	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);
		const auto& v0 = vtxMap[x->Vtx0()->Index()];
		const auto& v1 = vtxMap[x->Vtx1()->Index()];

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

			auto edge = std::make_shared<Pln_Edge>(x->Index(), x->Name(), v0, v1, curve, x->Sense());
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
	Adt_AvlTree<std::shared_ptr<Pln_Vertex>> tree;
	tree.SetComparableFunction(&Pln_Vertex::IsLess);

	for (const auto& x : Edges())
	{
		Debug_Null_Pointer(x);

		tree.InsertIgnoreDup(x->Vtx0());
		tree.InsertIgnoreDup(x->Vtx1());
	}

	std::vector<std::shared_ptr<Pln_Vertex>> vertices;
	tree.RetrieveTo(vertices);

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
		x->Transform(t);
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

void tnbLib::Pln_CmpEdge::Reverse()
{
	auto& edges = theEdges_;

	for (auto& x : edges)
	{
		Debug_Null_Pointer(x);
		x->Reverse();
	}
	std::reverse(edges.begin(), edges.end());
}

//std::shared_ptr<tnbLib::Pln_Wire> 
//tnbLib::Pln_CmpEdge::MakeWire
//(
//	const std::shared_ptr<Pln_CmpEdge>& theEdge, 
//	const Standard_Real theTol
//)
//{
//	const auto& edges = theEdge->Edges();
//
//	const auto& v0 = edges[0]->Vtx0();
//	const auto& v1 = edges[edges.size() - 1]->Vtx1();
//
//	if (v0 NOT_EQUAL v1)
//	{
//		
//	}
//}