#include <Cad_Entity.hxx>

DECLARE_SAVE_IMP(tnbLib::Cad_Entity)
{
	ar & Index();
	ar & Name();
}

DECLARE_LOAD_IMP(tnbLib::Cad_Entity)
{
	ar & Index();
	ar & Name();
}