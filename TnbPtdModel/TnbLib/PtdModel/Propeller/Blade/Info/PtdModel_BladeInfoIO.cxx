#include <PtdModel_BladeInfo.hxx>

#include <PtdModel_Forms.hxx>
#include <PtdModel_BladeGlobalPars.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeInfo)
{
	ar & theBladeForm_;
	ar & theGlobals_;

	ar & theNbSections_;
	ar & theNbSpans_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeInfo)
{
	ar & theBladeForm_;
	ar & theGlobals_;

	ar & theNbSections_;
	ar & theNbSpans_;
}