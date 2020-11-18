#include <Marine_Section_Wetted.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Section_Wetted)
{
	ar & boost::serialization::base_object<Marine_xSection>(*this);
	ar & DeepCondition();
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Section_Wetted)
{
	ar & boost::serialization::base_object<Marine_xSection>(*this);
	ar & Change_IsDeep();
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_Wetted>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_Wetted>);