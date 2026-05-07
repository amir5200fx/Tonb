#include <GeoTop2d_Halfedge.hxx>

void tnbLib::GeoTop2d_Halfedge::SetVtx0(const std::shared_ptr<GeoTop2d_Vertex>& theVtx)
{
	std::get<0>(theVertices_) = theVtx;
}

void tnbLib::GeoTop2d_Halfedge::SetVtx0(std::shared_ptr<GeoTop2d_Vertex>&& theVtx)
{
	std::get<0>(theVertices_) = std::move(theVtx);
}

void tnbLib::GeoTop2d_Halfedge::SetVtx1(const std::shared_ptr<GeoTop2d_Vertex>& theVtx)
{
	std::get<1>(theVertices_) = theVtx;
}

void tnbLib::GeoTop2d_Halfedge::SetVtx1(std::shared_ptr<GeoTop2d_Vertex>&& theVtx)
{
	std::get<1>(theVertices_) = std::move(theVtx);
}