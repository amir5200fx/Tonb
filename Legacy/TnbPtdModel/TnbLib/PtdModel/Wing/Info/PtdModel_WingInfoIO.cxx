#include <PtdModel_WingInfo.hxx>

#include <PtdModel_Forms.hxx>
#include <PtdModel_WingGlobalPars.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_WingInfo)
{
	ar & theForms_;
	ar & theGlobals_;

	ar & theNbSections_;
	ar & theNbSpans_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_WingInfo)
{
	ar & theForms_;
	ar & theGlobals_;

	ar & theNbSections_;
	ar & theNbSpans_;
}