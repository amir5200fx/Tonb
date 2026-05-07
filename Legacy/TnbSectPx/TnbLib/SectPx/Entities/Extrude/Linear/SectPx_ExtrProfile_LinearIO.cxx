#include <SectPx_ExtrProfile_Linear.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_Linear)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	ar & theX0_;
	ar & theX1_;

	ar & theValue0_;
	ar & theValue1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_Linear)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	ar & theX0_;
	ar & theX1_;

	ar & theValue0_;
	ar & theValue1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::ExtrProfile_Linear);