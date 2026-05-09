#include <GeoTop2d_Vertex.hxx>

#include <GeoTop2d_Point.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoTop2d_Vertex)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_VertexAdaptor>(*this);

	ar& thePoint_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoTop2d_Vertex)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_VertexAdaptor>(*this);

	ar& thePoint_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoTop2d_Vertex);