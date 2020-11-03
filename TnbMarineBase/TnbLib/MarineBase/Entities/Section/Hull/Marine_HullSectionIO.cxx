#include <Marine_HullSection.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_HullSection)
{
	ar & boost::serialization::base_object<Marine_Section>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Marine_HullSection)
{
	ar & boost::serialization::base_object<Marine_Section>(*this);
}