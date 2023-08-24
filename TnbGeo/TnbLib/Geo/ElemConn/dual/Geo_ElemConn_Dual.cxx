#include <Geo_ElemConn_Dual.hxx>

const char* tnbLib::Geo_ElemConn_Dual::typeName_ = "dual";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Dual::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}