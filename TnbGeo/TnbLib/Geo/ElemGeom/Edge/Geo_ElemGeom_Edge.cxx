#include <Geo_ElemGeom_Edge.hxx>

const char* tnbLib::Geo_ElemGeom_Edge::typeName_ = "edge";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemGeom_Edge::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}