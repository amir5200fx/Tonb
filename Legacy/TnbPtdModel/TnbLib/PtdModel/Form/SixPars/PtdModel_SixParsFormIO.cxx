#include <PtdModel_SixParsForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_SixParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
	ar & theX4_;
	ar & theX5_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_SixParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
	ar & theX4_;
	ar & theX5_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_SixParsForm);