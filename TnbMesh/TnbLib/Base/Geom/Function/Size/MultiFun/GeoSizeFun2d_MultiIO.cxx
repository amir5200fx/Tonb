#include <GeoSizeFun2d_Multi.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GeoSizeFun2d_Multi)
{
	ar& boost::serialization::base_object<Geo2d_SizeFunction>(*this);
	ar& theFunctions_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GeoSizeFun2d_Multi)
{
	ar& boost::serialization::base_object<Geo2d_SizeFunction>(*this);
	ar& theFunctions_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::GeoSizeFun2d_Multi);