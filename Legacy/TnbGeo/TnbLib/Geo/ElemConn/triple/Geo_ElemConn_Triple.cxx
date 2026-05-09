#include <Geo_ElemConn_Triple.hxx>

const char* tnbLib::Geo_ElemConn_Triple::typeName_ = "triple";

std::vector<Standard_Integer> 
tnbLib::Geo_ElemConn_Triple::IndexList() const
{
	std::vector<Standard_Integer> indices;
	std::copy(theIndices_.begin(), theIndices_.end(), std::back_inserter(indices));
	return std::move(indices);
}