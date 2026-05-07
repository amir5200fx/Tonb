#include <Geo2d_NurbsPx.hxx>

#include <Geo_ProfileFun.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Geo2d_NurbsPx)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theProfile_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Geo2d_NurbsPx)
{
	ar& boost::serialization::base_object<Global_Done>(*this);
	ar& theProfile_;
}