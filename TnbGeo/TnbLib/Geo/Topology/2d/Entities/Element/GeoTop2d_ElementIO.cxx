#include <GeoTop2d_Element.hxx>

#include <GeoTop2d_Vertex.hxx>
#include <GeoTop2d_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoTop2d_Element)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_ElementAdaptor>(*this);
	ar& theVertices_;
	ar& theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoTop2d_Element)
{
	ar& boost::serialization::base_object<GeoTop2d_Entity>(*this);
	ar& boost::serialization::base_object<GeoTop2d_ElementAdaptor>(*this);
	ar& theVertices_;
	ar& theEdges_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoTop2d_Element);