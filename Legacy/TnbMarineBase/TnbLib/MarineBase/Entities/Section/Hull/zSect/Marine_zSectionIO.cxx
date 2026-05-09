#include <Marine_zSection.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::Marine_zSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::Marine_zSection)
{
	ar & boost::serialization::base_object<Marine_HullSection>(*this);
}