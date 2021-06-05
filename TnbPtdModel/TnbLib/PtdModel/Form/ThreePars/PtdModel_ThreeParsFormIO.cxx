#include <PtdModel_ThreeParsForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_ThreeParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_ThreeParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_ThreeParsForm);