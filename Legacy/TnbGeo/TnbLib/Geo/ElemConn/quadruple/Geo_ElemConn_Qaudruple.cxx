#include <Geo_ElemConn_Qaudruple.hxx>

const char* tnbLib::Geo_ElemConn_Qaudruple::typeName_ = "quadruple";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Qaudruple::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}