#include <HydStatic_OffsetCrsCurvesGraph.hxx>

#include <HydStatic_CrsCurveQ.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_OffsetCrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_CrsCurvesGraph>(*this);

	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_OffsetCrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_CrsCurvesGraph>(*this);

	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_OffsetCrsCurvesGraph);