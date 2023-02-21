#include <GeoTop2d_Edge.hxx>

tnbLib::GeoTop2d_Edge::GeoTop2d_Edge
(
	const Standard_Integer theIndex,
	const std::shared_ptr<GeoTop2d_Vertex>& theVtx0,
	const std::shared_ptr<GeoTop2d_Vertex>& theVtx1
)
	: GeoTop2d_Entity(theIndex)
{
	thePair_ = { theVtx0,theVtx1 };
}

