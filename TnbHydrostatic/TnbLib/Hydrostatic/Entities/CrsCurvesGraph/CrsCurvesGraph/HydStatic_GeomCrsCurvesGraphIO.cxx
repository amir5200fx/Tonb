#include <HydStatic_GeomCrsCurvesGraph.hxx>

#include <HydStatic_CrsCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_GeomCrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_CrsCurvesGraph>(*this);
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_GeomCrsCurvesGraph)
{
	ar & boost::serialization::base_object<HydStatic_CrsCurvesGraph>(*this);
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_GeomCrsCurvesGraph);