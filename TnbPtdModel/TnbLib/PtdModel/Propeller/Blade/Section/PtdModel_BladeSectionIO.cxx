#include <PtdModel_BladeSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeSection)
{
	ar & theBack_;
	ar & theFace_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeSection)
{
	ar & theBack_;
	ar & theFace_;
}