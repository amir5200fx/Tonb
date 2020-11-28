#include <SectPx_Datum_Compnt.hxx>

#include <SectPx_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::sectPxLib::Datum_Compnt)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theX_;
	ar & theY_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::sectPxLib::Datum_Compnt)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theX_;
	ar & theY_;
}