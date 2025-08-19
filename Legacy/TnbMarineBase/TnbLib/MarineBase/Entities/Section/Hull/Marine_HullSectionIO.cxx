#include <Marine_HullSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_HullSection)
{
	ar & boost::serialization::base_object<Marine_Section>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_HullSection)
{
	ar & boost::serialization::base_object<Marine_Section>(*this);
}