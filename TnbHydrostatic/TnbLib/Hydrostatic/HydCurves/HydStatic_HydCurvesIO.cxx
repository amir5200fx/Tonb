#include <HydStatic_HydCurves.hxx>

#include <Marine_Domain.hxx>
#include <Marine_Bodies.hxx>
#include <Marine_MultLevWaterDomain.hxx>
#include <HydStatic_HydCurvesGraph.hxx>

TNB_SAVE_IMPLEMENTATION(tnbLib::HydStatic_HydCurves)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWaters_;

	ar & RudderAxis_;
	ar & theRudderAxisLoc_;
	ar & theDisplFactor_;

	ar & theGraph_;
}

TNB_LOAD_IMPLEMENTATION(tnbLib::HydStatic_HydCurves)
{
	ar & boost::serialization::base_object<Global_Done>(*this);

	ar & theWaters_;

	ar & RudderAxis_;
	ar & theRudderAxisLoc_;
	ar & theDisplFactor_;

	ar & theGraph_;
}