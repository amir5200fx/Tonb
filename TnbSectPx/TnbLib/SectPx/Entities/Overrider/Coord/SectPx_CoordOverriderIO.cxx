#include <SectPx_CoordOverrider.hxx>

#include <SectPx_Coord.hxx>

DECLARE_SAVE_IMP(tnbLib::SectPx_CoordOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theCoord_;
}

DECLARE_LOAD_IMP(tnbLib::SectPx_CoordOverrider)
{
	ar & boost::serialization::base_object<SectPx_Overrider>(*this);
	ar & theCoord_;
}