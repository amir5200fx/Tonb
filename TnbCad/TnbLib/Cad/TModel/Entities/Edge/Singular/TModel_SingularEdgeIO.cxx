#include <TModel_SingularEdge.hxx>

#include <TModel_Vertex.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_SingularEdge)
{
	ar & boost::serialization::base_object<TModel_Edge>(*this);
	ar & theVtx_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_SingularEdge)
{
	ar & boost::serialization::base_object<TModel_Edge>(*this);
	ar & theVtx_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_SingularEdge);