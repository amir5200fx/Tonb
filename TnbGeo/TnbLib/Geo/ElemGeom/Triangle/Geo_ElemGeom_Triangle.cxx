#include <Geo_ElemGeom_Triangle.hxx>

const char* tnbLib::Geo_ElemGeom_Triangle::typeName_ = "triangle";

tnbLib::Geo_ElemGeom::dim tnbLib::Geo_ElemGeom_Triangle::Dim() const { return dim::two; }

std::vector<Standard_Integer> 
tnbLib::Geo_ElemGeom_Triangle::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}
