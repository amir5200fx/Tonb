#include <Pln_CmpEdge.hxx>

#include <Pln_Vertex.hxx>
#include <Pln_Edge.hxx>
#include <Pln_Tools.hxx>
#include <error.hxx>
#include <OSstream.hxx>

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

//std::shared_ptr<tnbLib::Pln_CmpEdge> 
//tnbLib::Pln_CmpEdge::Copy() const
//{
//	auto vertices = RetrieveVertices();
//	std::vector<std::shared_ptr<Pln_Vertex>> copy_vertices;
//	for (const auto& x : vertices)
//	{
//		Debug_Null_Pointer(x);
//		copy_vertices.push_back(x->Copy());
//	}
//}

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