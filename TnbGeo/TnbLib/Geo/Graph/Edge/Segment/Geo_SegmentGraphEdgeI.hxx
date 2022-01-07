#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class EdgeTraits>
inline void tnbLib::Geo_SegmentGraphEdge<EdgeTraits>::deAttach
(
	const std::shared_ptr<Geo_SegmentGraphEdge>& theEdge
)
{
	const auto& n0 = theEdge->Node0();
	const auto& n1 = theEdge->Node1();

	Debug_Null_Pointer(n0);
	Debug_Null_Pointer(n1);

	n0->RemoveFromEdges(theEdge->Index());
	n1->RemoveFromEdges(theEdge->Index());
}