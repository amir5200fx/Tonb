#include <HydStatic_BonjeanGraph.hxx>

#include <Marine_CmpSection.hxx>
#include <HydStatic_BnjCurve.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_BonjeanGraph::GraphSect)
{
	ar & theSection_;
	ar & theCurves_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_BonjeanGraph::GraphSect)
{
	ar & theSection_;
	ar & theCurves_;
}

BOOST_CLASS_EXPORT_IMPLEMENT(tnbLib::HydStatic_BonjeanGraph);