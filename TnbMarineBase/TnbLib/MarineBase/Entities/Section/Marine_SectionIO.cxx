#include <Marine_Section.hxx>

#include <Pln_Wire.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_Section)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Wire();
}

DECLARE_LOAD_IMP(tnbLib::Marine_Section)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeWire();
}