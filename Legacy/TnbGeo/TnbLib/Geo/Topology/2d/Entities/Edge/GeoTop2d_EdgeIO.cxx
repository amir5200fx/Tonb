#include <GeoTop2d_Edge.hxx>

#include <GeoTop2d_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoTop2d_Edge)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_EdgeAdaptor>(*this);
	ar& thePair_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoTop2d_Edge)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_EdgeAdaptor>(*this);
	ar& thePair_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoTop2d_Edge);