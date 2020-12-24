#include <SectPx_CurveQ.hxx>

#include <SectPx_Pole.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_CurveQ)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePole0_;
	ar & thePole1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_CurveQ)
{
	ar & boost::serialization::base_object<SectPx_RegObj>(*this);
	ar & thePole0_;
	ar & thePole1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::SectPx_CurveQ);