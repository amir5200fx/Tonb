#include <Aft3d_Tools.hxx>

#include <Aft3d_Facet.hxx>
#include <Aft3d_Edge.hxx>
#include <Aft3d_Node.hxx>
#include <Aft3d_Comparison.hxx>
#include <Geo_Tools.hxx>
#include <Pnt3d.hxx>
#include <Dir3d.hxx>

#include <Standard_Failure.hxx>

tnbLib::Vec3d 
tnbLib::legLib::Aft3d_Tools::CalcNormal
(
	const Aft3d_Facet& theFacet
)
{
	auto [p0, p1, p2] = theFacet.RetrieveCoords();
	auto n = Geo_Tools::CalcNormal(p0, p1, p2);
	return std::move(n);
}

Standard_Boolean 
tnbLib::legLib::Aft3d_Tools::IsForwardEdge
(
	const std::shared_ptr<Aft3d_Edge>& theEdge, 
	const std::shared_ptr<Aft3d_Facet>& theFace
)
{
	std::shared_ptr<Aft3d_Edge> e;
	for (const auto& x : theFace->GetEdges())
	{
		if (theEdge IS_EQUAL x)
		{
			e = x;
			break;
		}
	}
	if (NOT e)
	{
		FatalErrorIn(FunctionSIG)
			<< "the edge doesn't belong to the face." << endl
			<< abort(FatalError);
	}

}

Standard_Real 
tnbLib::legLib::Aft3d_Tools::CalcCommonEdgeAngle
(
	const Aft3d_Facet& theFace0, 
	const Aft3d_Facet& theFace1
)
{
	auto n0 = CalcNormal(theFace0).Normalized();
	auto n1 = CalcNormal(theFace1).Normalized();

	auto edge = CommonEdge(theFace0, theFace1);
	Debug_Null_Pointer(edge);


}

tnbLib::Pnt3d 
tnbLib::legLib::Aft3d_Tools::CalcTetrahedronVertex
(
	const Standard_Real theSize,
	const Aft3d_Facet& theFacet
)
{
	try
	{
		const auto c = theFacet.CalcCentre();
		const auto normal = CalcNormal(theFacet).Normalized();

		auto pt = c + theSize * normal;
		return std::move(pt);
	}
	catch (const Standard_Failure& x)
	{
		FatalErrorIn(FunctionSIG)
			<< x.GetMessageString() << endl
			<< abort(FatalError);
		return Pnt3d::null;
	}
}

std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Node>>
tnbLib::legLib::Aft3d_Tools::RetrieveNodes
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFacets
)
{
	std::set<std::shared_ptr<Aft3d_Node>, decltype(cmp_node)> compact(cmp_node);
	for (const auto& x : theFacets)
	{
		Debug_Null_Pointer(x);

		const auto& n0 = x->Node0();
		const auto& n1 = x->Node1();
		const auto& n2 = x->Node2();

		Debug_Null_Pointer(n0);
		Debug_Null_Pointer(n1);
		Debug_Null_Pointer(n2);

		compact.insert(n0);
		compact.insert(n1);
		compact.insert(n2);
	}
	std::vector<std::shared_ptr<Aft3d_Node>> nodes;
	std::copy(compact.begin(), compact.end(), std::back_inserter(nodes));
	return std::move(nodes);
}

std::vector<std::shared_ptr<tnbLib::legLib::Aft3d_Edge>>
tnbLib::legLib::Aft3d_Tools::RetrieveEdges
(
	const std::vector<std::shared_ptr<Aft3d_Facet>>& theFacets
)
{
	std::set<std::shared_ptr<Aft3d_Edge>, decltype(cmp_edge)> compact(cmp_edge);
	for (const auto& x : theFacets)
	{
		Debug_Null_Pointer(x);

		const auto& e0 = x->Edge0();
		const auto& e1 = x->Edge1();
		const auto& e2 = x->Edge2();

		Debug_Null_Pointer(e0);
		Debug_Null_Pointer(e1);
		Debug_Null_Pointer(e2);

		compact.insert(e0);
		compact.insert(e1);
		compact.insert(e2);
	}
	std::vector<std::shared_ptr<Aft3d_Edge>> edges;
	std::copy(compact.begin(), compact.end(), std::back_inserter(edges));
	return std::move(edges);
}