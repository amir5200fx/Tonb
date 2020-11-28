#include <SectPx_CoordOverrider.hxx>

#include <SectPx_Coord.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_CoordOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theCoord_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_CoordOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theCoord_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_CoordOverrider);