#include <GeoTop2d_Element.hxx>

const std::shared_ptr<tnbLib::GeoTop2d_Vertex>& 
tnbLib::GeoTop2d_Element::Vertex(const Standard_Integer theIndex) const
{
	return Vertices().at(theIndex);
}

const std::shared_ptr<tnbLib::GeoTop2d_Edge>& 
tnbLib::GeoTop2d_Element::Edge(const Standard_Integer theIndex) const
{
	return Edges().at(theIndex);
}