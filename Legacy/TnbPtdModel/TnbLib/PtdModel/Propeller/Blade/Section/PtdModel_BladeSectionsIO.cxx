#include <PtdModel_BladeSections.hxx>

#include <PtdModel_BladeSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeSections)
{
	ar & theSections_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeSections)
{
	ar & theSections_;
}