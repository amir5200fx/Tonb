#include <Marine_Section_Wetted.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Section_Wetted)
{
	ar & boost::serialization::base_object<Marine_xSection>(*this);
	ar & DeepCondition();
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Section_Wetted)
{
	ar & boost::serialization::base_object<Marine_xSection>(*this);
	ar & Change_IsDeep();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Wetted>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Wetted>);