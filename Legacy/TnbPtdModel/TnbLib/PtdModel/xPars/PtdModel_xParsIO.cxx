#include <PtdModel_xPars.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_xPars)
{
	ar & theX_;
	ar & theParameters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_xPars)
{
	ar & theX_;
	ar & theParameters_;
}