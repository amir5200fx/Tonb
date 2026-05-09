#include <TModel_RingEdge.hxx>

#include <TModel_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_RingEdge)
{
	ar & boost::serialization::base_object<TModel_GeneratedEdge>(*this);
	ar & theVtx_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_RingEdge)
{
	ar & boost::serialization::base_object<TModel_GeneratedEdge>(*this);
	ar & theVtx_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_RingEdge);