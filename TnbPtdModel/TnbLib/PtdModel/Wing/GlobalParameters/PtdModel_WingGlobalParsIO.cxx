#include <PtdModel_WingGlobalPars.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_WingGlobalPars)
{
	ar & theSpan_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_WingGlobalPars)
{
	ar & theSpan_;
}