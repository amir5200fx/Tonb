#include <SectPx_ExtrProfile.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::SectPx_ExtrProfile)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);

	ar & theStart_;
	ar & theEnd_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::SectPx_ExtrProfile)
{
	ar & boost::serialization::base_object<SectPx_Parent>(*this);

	ar & theStart_;
	ar & theEnd_;
}