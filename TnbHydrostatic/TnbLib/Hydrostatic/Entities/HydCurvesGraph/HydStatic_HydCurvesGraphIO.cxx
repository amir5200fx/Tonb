#include <HydStatic_HydCurvesGraph.hxx>

#include <HydStatic_HydGphCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HydCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theCurves_;
	ar & theTmax_;
	ar & theTmin_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HydCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_Entity>(*this);
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theCurves_;
	ar & theTmax_;
	ar & theTmin_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_HydCurvesGraph);