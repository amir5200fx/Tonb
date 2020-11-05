#include <SectPx_Datum_Compnt.hxx>

#include <SectPx_Par.hxx>

DECLARE_SAVE_IMP(tnbLib::sectPxLib::Datum_Compnt)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theX_;
	ar & theY_;
}

DECLARE_LOAD_IMP(tnbLib::sectPxLib::Datum_Compnt)
{
	ar & boost::serialization::base_object<SectPx_Datum>(*this);
	ar & theX_;
	ar & theY_;
}