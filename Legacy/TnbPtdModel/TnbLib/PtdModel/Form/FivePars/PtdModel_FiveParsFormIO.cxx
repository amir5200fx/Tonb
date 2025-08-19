#include <PtdModel_FiveParsForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_FiveParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
	ar & theX4_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_FiveParsForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);

	ar & theX0_;
	ar & theX1_;
	ar & theX2_;
	ar & theX3_;
	ar & theX4_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_FiveParsForm);