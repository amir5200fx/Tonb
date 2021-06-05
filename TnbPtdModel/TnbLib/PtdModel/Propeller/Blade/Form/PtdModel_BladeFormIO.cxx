#include <PtdModel_BladeForm.hxx>

#include <PtdModel_Form.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeForm)
{
	ar & theForms_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeForm)
{
	ar & theForms_;
}