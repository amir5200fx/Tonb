#include <PtdModel_UniformForm.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_UniformForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theValue_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_UniformForm)
{
	ar & boost::serialization::base_object<PtdModel_Form>(*this);
	ar & theValue_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::PtdModel_UniformForm);