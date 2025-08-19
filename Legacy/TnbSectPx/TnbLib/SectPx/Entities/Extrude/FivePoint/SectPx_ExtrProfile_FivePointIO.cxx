#include <SectPx_ExtrProfile_FivePoint.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_FivePoint)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	for (size_t i = 0; i < NbPoints() - 1; i++)
	{
		ar & (&theX0_)[i];
		ar & (&theValue0_)[i];
	}
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::ExtrProfile_FivePoint)
{
	ar & boost::serialization::base_object<SectPx_ExtrProfile>(*this);

	for (size_t i = 0; i < NbPoints() - 1; i++)
	{
		ar & (&theX0_)[i];
		ar & (&theValue0_)[i];
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::sectPxLib::ExtrProfile_FivePoint);