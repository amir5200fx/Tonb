#include <Geo_ElemGeom_Pyramid.hxx>

const char* tnbLib::Geo_ElemGeom_Pyramid::typeName_ = "pyramid";

tnbLib::Geo_ElemGeom::dim tnbLib::Geo_ElemGeom_Pyramid::Dim() const { return dim::three; }

std::vector<Standard_Integer> 
tnbLib::Geo_ElemGeom_Pyramid::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}
