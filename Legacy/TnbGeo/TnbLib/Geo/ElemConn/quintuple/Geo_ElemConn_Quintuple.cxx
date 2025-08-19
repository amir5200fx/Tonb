#include <Geo_ElemConn_Quintuple.hxx>

const char* tnbLib::Geo_ElemConn_Quintuple::typeName_ = "quintuple";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Quintuple::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}