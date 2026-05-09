#include <PtdModel_LinearForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_LinearForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theX0_;
	ar & theX1_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_LinearForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theX0_;
	ar & theX1_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_LinearForm);