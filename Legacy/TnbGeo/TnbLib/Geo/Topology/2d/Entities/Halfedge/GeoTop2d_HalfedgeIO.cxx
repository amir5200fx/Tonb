#include <GeoTop2d_Halfedge.hxx>

#include <GeoTop2d_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoTop2d_Halfedge)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& theVertices_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoTop2d_Halfedge)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& theVertices_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoTop2d_Halfedge);