#include <TModel_SegmentEdge.hxx>

#include <TModel_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_SegmentEdge)
{
	ar & boost::serialization::base_object<TModel_GeneratedEdge>(*this);

	ar & theVtx0_;
	ar & theVtx1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_SegmentEdge)
{
	ar & boost::serialization::base_object<TModel_GeneratedEdge>(*this);

	ar & theVtx0_;
	ar & theVtx1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_SegmentEdge);