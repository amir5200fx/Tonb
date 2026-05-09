#include <HydStatic_CrsCurvesGraph.hxx>

#include <HydStatic_CrsCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_CrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theMaxDispv_;
	ar & theMinDispv_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_CrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);
	ar & theMaxDispv_;
	ar & theMinDispv_;
}