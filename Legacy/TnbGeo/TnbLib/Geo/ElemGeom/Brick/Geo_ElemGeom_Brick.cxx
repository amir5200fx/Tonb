#include <Geo_ElemGeom_Brick.hxx>

const char* tnbLib::Geo_ElemGeom_Brick::typeName_ = "brick";

tnbLib::Geo_ElemGeom::dim tnbLib::Geo_ElemGeom_Brick::Dim() const { return dim::three; }

std::vector<Standard_Integer> 
tnbLib::Geo_ElemGeom_Brick::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}
