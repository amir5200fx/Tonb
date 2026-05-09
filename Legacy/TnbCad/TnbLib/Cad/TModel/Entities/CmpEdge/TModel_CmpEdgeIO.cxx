#include <TModel_CmpEdge.hxx>

#include <TModel_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_CmpEdge)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theEdges_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_CmpEdge)
{
	ar & boost::serialization::base_object<TModel_Entity>(*this);
	ar & theEdges_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_CmpEdge);