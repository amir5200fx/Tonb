#include <Geo_ElemConn_Sextuple.hxx>

const char* tnbLib::Geo_ElemConn_Sextuple::typeName_ = "sextuple";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Sextuple::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}