#include <Marine_Section_WaterLine.hxx>

DECLARE_SAVE_IMP(tnbLib::marineLib::Section_WaterLine)
{
	ar & boost::serialization::base_object<Marine_zSection>(*this);
}

DECLARE_LOAD_IMP(tnbLib::marineLib::Section_WaterLine)
{
	ar & boost::serialization::base_object<Marine_zSection>(*this);
}