#include <Pln_EntityPrecision.hxx>

DECLARE_SAVE_IMP(tnbLib::Pln_EntityPrecision)
{
	ar & Precision();
}

DECLARE_LOAD_IMP(tnbLib::Pln_EntityPrecision)
{
	ar& Precision();
}