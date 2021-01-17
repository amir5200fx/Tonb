#include <HydStatic_HeelSpacing.hxx>

#include <HydStatic_Spacing.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HeelSpacing)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theSpacing_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HeelSpacing)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theSpacing_;
}