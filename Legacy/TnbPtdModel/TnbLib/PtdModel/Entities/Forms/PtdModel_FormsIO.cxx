#include <PtdModel_Forms.hxx>

#include <PtdModel_Form.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Forms)
{
	ar & theForms_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Forms)
{
	ar & theForms_;
}