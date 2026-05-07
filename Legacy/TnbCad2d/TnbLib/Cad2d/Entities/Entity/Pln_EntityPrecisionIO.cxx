#include <Pln_EntityPrecision.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Pln_EntityPrecision)
{
	ar & thePrecision_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Pln_EntityPrecision)
{
	ar & thePrecision_;
}