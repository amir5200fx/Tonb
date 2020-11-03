#include <Marine_zSection.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_zSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Marine_zSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}