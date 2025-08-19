#include <Marine_Section.hxx>

#include <Pln_Wire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_Section)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & Wire();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_Section)
{
	ar & boost::serialization::base_object<Marine_CoordinatedEntity>(*this);
	ar & ChangeWire();
}