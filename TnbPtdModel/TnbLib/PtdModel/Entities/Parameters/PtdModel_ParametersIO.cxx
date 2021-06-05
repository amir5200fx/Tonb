#include <PtdModel_Parameters.hxx>

#include <PtdModel_Par.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::PtdModel_Parameters)
{
	ar & theParameters_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::PtdModel_Parameters)
{
	ar & theParameters_;
}