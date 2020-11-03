#include <Marine_xSection.hxx>

DECLARE_SAVE_IMP(tnbLib::Marine_xSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}

DECLARE_LOAD_IMP(tnbLib::Marine_xSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}