#include <Geo_ElemConn_Octuple.hxx>

const char* tnbLib::Geo_ElemConn_Octuple::typeName_ = "octuple";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Octuple::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}