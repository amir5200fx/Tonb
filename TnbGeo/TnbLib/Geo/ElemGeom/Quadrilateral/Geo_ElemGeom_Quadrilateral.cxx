#include <Geo_ElemGeom_Quadrilateral.hxx>

const char* tnbLib::Geo_ElemGeom_Quadrilateral::typeName_ = "quadrilateral";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemGeom_Quadrilateral::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}