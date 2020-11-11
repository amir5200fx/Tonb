#include <SectPx_GeoMap_LinearInterpl.hxx>

#include <SectPx_Coord.hxx>
#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::GeoMap_LinearInterpl)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);
	ar & theQ0_;
	ar & theQ1_;

	ar & thePar_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::GeoMap_LinearInterpl)
{
	ar & boost::serialization::base_object<SectPx_GeoMap>(*this);
	ar & theQ0_;
	ar & theQ1_;

	ar & thePar_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::GeoMap_LinearInterpl);