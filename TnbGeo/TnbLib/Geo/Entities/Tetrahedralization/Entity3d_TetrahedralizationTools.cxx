#include <Entity3d_TetrahedralizationTools.hxx>

#include <error.hxx>
#include <OSstream.hxx>

tnbLib::Entity3d_TetrahedralizationTools::edgeConnectivity 
tnbLib::Entity3d_TetrahedralizationTools::EdgeIndices
(
	const Standard_Integer theIndex
)
{
	static Standard_Integer Indices[12] =
	{
		2, 3, 3, 1, 1, 2, 1, 4, 2, 4, 3, 4
	};

	Debug_Bad_Index(theIndex, 0, 11);

	auto edge = 
		std::make_pair(Indices[2 * theIndex], Indices[2 * theIndex + 1]);
	return std::move(edge);
}

tnbLib::Entity3d_TetrahedralizationTools::facetConnectivity 
tnbLib::Entity3d_TetrahedralizationTools::FacetIndices
(
	const Standard_Integer theIndex
)
{
	static Standard_Integer Indices[12] =
	{
		2, 3, 4, 3, 1, 4, 4, 1, 2, 2, 1, 3
	};

	Debug_Bad_Index(theIndex, 0, 11);

	auto facet = 
		std::make_tuple(Indices[3 * theIndex], Indices[3 * theIndex + 1], Indices[3 * theIndex + 2]);
	return std::move(facet);
}