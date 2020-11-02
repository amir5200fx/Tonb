#include <Cad_Entity.hxx>

DECLARE_SAVE_IMP(tnbLib::Cad_Entity)
{
	ar << Index();

	std::string st = Name();
	ar << st;
}

DECLARE_LOAD_IMP(tnbLib::Cad_Entity)
{
	ar >> Index();

	std::string st;
	ar >> st;

	Name() = st;
}