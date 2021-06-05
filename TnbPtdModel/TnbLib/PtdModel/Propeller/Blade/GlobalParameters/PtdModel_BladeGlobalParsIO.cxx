#include <PtdModel_BladeGlobalPars.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_BladeGlobalPars)
{
	ar & theDiameter_;
	ar & theHubRadius_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_BladeGlobalPars)
{
	ar & theDiameter_;
	ar & theHubRadius_;
}