#include <TModel_ManifoldPaired.hxx>

#include <TModel_Edge.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_ManifoldPaired)
{
	ar & boost::serialization::base_object<TModel_Paired>(*this);

	ar & theEdge0_;
	ar & theEdge1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_ManifoldPaired)
{
	ar & boost::serialization::base_object<TModel_Paired>(*this);

	ar & theEdge0_;
	ar & theEdge1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::TModel_ManifoldPaired);