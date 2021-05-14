#include <GModel_Plane.hxx>

#include <GModel_ParaWire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::GModel_Plane)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theOuter_;
	ar & theInner_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::GModel_Plane)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);

	ar & theOuter_;
	ar & theInner_;
}