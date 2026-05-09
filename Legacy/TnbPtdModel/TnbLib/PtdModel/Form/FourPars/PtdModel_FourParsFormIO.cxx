#include <PtdModel_FourParsForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_FourParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_FourParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_FourParsForm);