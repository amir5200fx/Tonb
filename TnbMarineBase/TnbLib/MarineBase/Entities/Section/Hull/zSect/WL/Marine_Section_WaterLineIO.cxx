#include <Marine_Section_WaterLine.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::marineLib::Section_WaterLine)
{
	ar & boost::serialization::base_object<Marine_zSection>(*this);
}

TNB_LOAD_IMPLEMENTATION(tnbLib::marineLib::Section_WaterLine)
{
	ar & boost::serialization::base_object<Marine_zSection>(*this);
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::InnerSection<tnbLib::marineLib::Section_WaterLine>);
BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::marineLib::OuterSection<tnbLib::marineLib::Section_WaterLine>);