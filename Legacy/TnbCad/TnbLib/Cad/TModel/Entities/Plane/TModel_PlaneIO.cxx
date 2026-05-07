#include <TModel_Plane.hxx>

#include <TModel_ParaWire.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::TModel_Plane)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theOuter_;
	ar & theInner_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::TModel_Plane)
{
	ar & boost::serialization::base_object<Global_Indexed>(*this);
	ar & boost::serialization::base_object<Global_Named>(*this);
	ar & theOuter_;
	ar & theInner_;
}
