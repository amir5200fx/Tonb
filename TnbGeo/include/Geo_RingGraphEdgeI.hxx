#pragma once
#include <TnbError.hxx>
#include <OSstream.hxx>
template<class EdgeTraits>
inline void tnbLib::Geo_RingGraphEdge<EdgeTraits>::deAttach
(
	const std::shared_ptr<Geo_RingGraphEdge>& theEdge
)
{
	const auto& n = theEdge->Node();
	Debug_Null_Pointer(n);

	n->RemoveFromEdges(theEdge->Index());
}