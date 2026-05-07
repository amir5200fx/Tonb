#include <SectPx_ExtrProfile_Uniform.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_Uniform)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theValue_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_Uniform)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theValue_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::ExtrProfile_Uniform);