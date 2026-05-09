#include <Marine_xSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_xSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_xSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}